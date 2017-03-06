/**
 * @file DBConnectionPool.h
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

/**
 * This class defines a pool of database connections
 * It implements the Object Pool design pattern (and the Singleton design pattern)
 * @see DBConnection.hpp
 */
class DBConnectionPool {
private:
	/**
	 * Properties contained in the properties file
	 */
	std::map<std::string, std::string> _properties;
	/**
	 * Queue of connections
	 */
	std::deque<std::shared_ptr<db::DBConnection> > _pool;
	/**
	 * Connection pool instance, used to implement the Singleton
	 */
	static std::shared_ptr<DBConnectionPool> _instance;
	/**
	 * Mutex used to prevent multiple instances being created
	 */
	static std::mutex _creationMutex;
	/**
	 * Mutex used when pushing connection in the pool
	 */
	std::mutex _pushMutex;
	/**
	 * Mutex used when popping a connection from the pool
	 */
	std::mutex _popMutex;
	/**
	 * This condition variable is used to wait for available
	 * connections (or a slot available to insert a new connection, but this
	 * should never happen)
	 */
	std::condition_variable _cv;

	/**
	 * Class constructor
	 */
	DBConnectionPool();
public:
	/**
	 * Size of the connection pool
	 */
	static unsigned int MAX_CONNECTIONS;

	/**
	 * Class destructor
	 */
	virtual ~DBConnectionPool();

	/**
	 * Get a DBConnectionPool instance. It is used to implement the  Singleton design pattern.
	 * @return	An instance to the DBConnectionPool
	 */
	static std::shared_ptr<DBConnectionPool> getInstance();

	/**
	 * Get a connection from the pool
	 * @return A connection to the database
	 * @see DBConnection.hpp
	 */
	std::shared_ptr<db::DBConnection> popConnection();

	/**
	 * This method allows returning a database connection to the pool
	 * @param[in] connection	Connection to be returned to the pool
	 */
	void pushConnection(std::shared_ptr<db::DBConnection> connection);
};

} /* namespace account */

#endif /* CXX_DB_DBCONNECTIONPOOL_H_ */
