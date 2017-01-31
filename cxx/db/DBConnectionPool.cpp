/**
 * @file ConnectionPool.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "DBConnectionPool.h"

#include "../utils/Utils.h"
#include <exception>
#include <functional>

namespace db {


const std::string ConnectionPool::DB_CONF = "conf/db.properties";
unsigned int ConnectionPool::MAX_CONNECTIONS = 10;
std::shared_ptr<ConnectionPool> ConnectionPool::_instance = nullptr;
std::mutex ConnectionPool::_creationMutex;

ConnectionPool::ConnectionPool() : _properties(), _pool() {
	utils::Utils::parseFile(DB_CONF, _properties);

	std::string hostIp = utils::Utils::getIpAddress(_properties.at("dbhost"));
	if (hostIp.empty()) {
		std::cerr << "WARN: Could not get ip from host <" << hostIp << ">. Set to <localhost> (127.0.0.1)" << std::endl;
		hostIp = "127.0.0.1";
	}
	driver = get_driver_instance();
	std::string host = std::string("tcp://" + hostIp + ":" + _properties.at("dbport"));
	std::string user = _properties.at("username");
	std::string pass = _properties.at("password");
	int max_conn = utils::Utils::str2int(_properties.at("max_connections"));
	std::cout << "Connecting to " << host << " with username <" << user << ">, pass <" << pass << ">" << std::endl;

	if (max_conn == -1) {
		std::cerr << "WARN: Maximum connections has not been (correctly) defined. Use the default (10)" << std::endl;
	} else {
		MAX_CONNECTIONS = max_conn;
		std::cout << "[INFO] " << "Using a pool of " << MAX_CONNECTIONS << " connections..." << std::endl;
	}

	try {
		for (unsigned int i=0; i<MAX_CONNECTIONS; ++i)
			_pool.push_back(std::shared_ptr<sql::Connection>(driver->connect(host.c_str(), user.c_str(), pass.c_str())));
	} catch (sql::SQLException& e) {
		if ( e.getErrorCode() == 2026 ) // Max No. of connections exceeded
			throw db::MaxNoConnectionsException("Max number of connections exceeded");
	}
}

ConnectionPool::~ConnectionPool() {
	_properties.clear();
	_pool.clear();
}

std::shared_ptr<ConnectionPool> ConnectionPool::getInstance() {
	// This lock prevents creating multiple instances when concurrency is present
	std::unique_lock<std::mutex> locker(_creationMutex);
	if (_instance == nullptr) {
		_instance = std::shared_ptr<ConnectionPool>(new ConnectionPool());
	}
	return _instance;
}

std::shared_ptr<sql::Connection> ConnectionPool::popConnection() {
	std::unique_lock<std::mutex> locker(_popMutex);
	if (_pool.empty()) {
		_cv.wait(locker, [&](){return _pool.empty();});
	}
	std::shared_ptr<sql::Connection> element = _pool.front();
	_pool.pop_front();
	return element;
}

void ConnectionPool::pushConnection(std::shared_ptr<sql::Connection> connection) {
	std::unique_lock<std::mutex> locker(_pushMutex);
	// This should never happen. However, we must find a solution to prevent this
	if (_pool.size() == MAX_CONNECTIONS) {
		_cv.wait(locker, [&](){return _pool.size() < MAX_CONNECTIONS;});
	}
	_pool.push_back(connection);
	_cv.notify_one();
}



} /* namespace account */
