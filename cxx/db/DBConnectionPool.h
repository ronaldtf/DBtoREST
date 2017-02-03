/**
 * @file ConnectionPool.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_DBCONNECTIONPOOL_H_
#define CXX_DB_DBCONNECTIONPOOL_H_

#include <mysql_connection.h>
#include <cppconn/driver.h>

#include <condition_variable>
#include <deque>
#include <exception>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

namespace db {

class MaxNoConnectionsException : public std::exception {
private:
	std::string _message;
public:
	MaxNoConnectionsException(const std::string& message) : _message(message) {
	};

	const char* what() const throw() {
		return _message.c_str();
	};

	virtual ~MaxNoConnectionsException() throw() {};
};

class ConnectionPool {
private:
	sql::Driver* _driver;
	std::map<std::string, std::string> _properties;
	std::deque<std::shared_ptr<sql::Connection> > _pool;

	static std::shared_ptr<ConnectionPool> _instance;
	static std::mutex _creationMutex; // This mutex is used to prevent multiple instances being created
	std::mutex _pushMutex;
	std::mutex _popMutex;
	std::condition_variable _cv;

	ConnectionPool();
public:
	static unsigned int MAX_CONNECTIONS;

	virtual ~ConnectionPool();
	static std::shared_ptr<ConnectionPool> getInstance();

	std::shared_ptr<sql::Connection> popConnection();
	void pushConnection(std::shared_ptr<sql::Connection> connection);
};

} /* namespace account */

#endif /* CXX_DB_DBCONNECTIONPOOL_H_ */
