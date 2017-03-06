/**
 * @file DBConnectionPool.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "DBConnectionPool.h"

#include <exception>
#include <functional>

#include "../connection/DBConnectionAdapter.h"
#include "../../exception/DBException.hpp"
#include "../../utils/Utils.h"

namespace db {

unsigned int DBConnectionPool::MAX_CONNECTIONS = 10;
std::shared_ptr<DBConnectionPool> DBConnectionPool::_instance = nullptr;
std::mutex DBConnectionPool::_creationMutex;

DBConnectionPool::DBConnectionPool() : _properties(), _pool(), _pushMutex(), _popMutex() {

	try {
		// Get properties from the properties file
		utils::Utils::getDBProperties(_properties);
	} catch (std::exception& e) {
		std::cerr << "[ERROR] A problem has occurred when parsing the DB properties: " << e.what() << std::endl;
		throw e;
	}

	// Initialize class attributes regarding the properties extracted from the properties file
	std::string hostIp = utils::Utils::getIpAddress(_properties.at("dbhost"));
	if (hostIp.empty()) {
		std::cerr << "[WARN] Could not get ip from host <" << hostIp << ">. Set to <localhost> (127.0.0.1)" << std::endl;
		hostIp = "127.0.0.1";
	}
	std::string host = std::string("tcp://" + hostIp + ":" + _properties.at("dbport"));
	std::string user = _properties.at("username");
	std::string pass = _properties.at("password");
	int max_conn = utils::Utils::str2int(_properties.at("max_connections"));
	std::cout << "Connecting to " << host << " with username <" << user << ">, pass <" << pass << ">" << std::endl;

	// Set the maximum number of connections / pool size
	if (max_conn == -1) {
		std::cerr << "[WARN] Maximum connections has not been (correctly) defined. Use the default (10)" << std::endl;
	} else {
		MAX_CONNECTIONS = max_conn;
		std::cout << "[INFO] " << "Using a pool of " << MAX_CONNECTIONS << " connections..." << std::endl;
	}

	// Initialize the pool
	try {
		for (unsigned int i=0; i<MAX_CONNECTIONS; ++i)
			_pool.push_back(std::shared_ptr<db::DBConnection>(new db::DBConnectionAdapter(host.c_str(), user.c_str(), pass.c_str())));
	} catch (exception::DBException& e) {
		// Max No. of connections exceeded
		std::cerr << e.getMessage() << std::endl;
		throw e;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
	}
}

DBConnectionPool::~DBConnectionPool() {
	_properties.clear();
	_pool.clear();
}

std::shared_ptr<DBConnectionPool> DBConnectionPool::getInstance() {
	// This lock prevents creating multiple instances when concurrency is present
	std::unique_lock<std::mutex> locker(_creationMutex);
	if (_instance == nullptr) {
		_instance = std::shared_ptr<DBConnectionPool>(new DBConnectionPool());
	}
	return _instance;
}

std::shared_ptr<db::DBConnection> DBConnectionPool::popConnection() {
	std::unique_lock<std::mutex> locker(_popMutex);

	// Wait for an available connection if there are no connection in the pool
	if (_pool.empty()) {
		_cv.wait(locker, [&](){return _pool.empty();});
	}

	std::shared_ptr<db::DBConnection> element = _pool.front();
	_pool.pop_front();
	return element;
}

void DBConnectionPool::pushConnection(std::shared_ptr<db::DBConnection> connection) {
	std::unique_lock<std::mutex> locker(_pushMutex);

	// This should never happen. However, we must find a solution to prevent this
	if (_pool.size() == MAX_CONNECTIONS) {
		_cv.wait(locker, [&](){return _pool.size() < MAX_CONNECTIONS;});
	}

	_pool.push_back(connection);
	_cv.notify_one();
}

} /* namespace account */
