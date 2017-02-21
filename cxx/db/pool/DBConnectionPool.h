/**
 * @file ConnectionPool.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_DBCONNECTIONPOOL_H_
#define CXX_DB_DBCONNECTIONPOOL_H_

#include <condition_variable>
#include <deque>
#include <exception>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

#include "../connection/DBConnection.hpp"

namespace db {

class ConnectionPool {
private:
	std::map<std::string, std::string> _properties;
	std::deque<std::shared_ptr<db::DBConnection> > _pool;

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

	std::shared_ptr<db::DBConnection> popConnection();
	void pushConnection(std::shared_ptr<db::DBConnection> connection);
};

} /* namespace account */

#endif /* CXX_DB_DBCONNECTIONPOOL_H_ */
