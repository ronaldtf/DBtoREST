package main.java.db.pool;

import java.util.Deque;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

import db.connection.DBConnection;

/**
 * This class defines a pool of database connections
 * It implements the Object Pool design pattern (and the Singleton design pattern)
 * @see DBConnection.java
 */
public class DBConnectionPool {
	/**
	 * Properties contained in the properties file
	 */
	private Map<String, String> _properties;
	/**
	 * Queue of connections
	 */
	private Deque<DBConnection> _pool;
	/**
	 * Connection pool instance, used to implement the Singleton
	 */
	private static DBConnectionPool _instance = null;
	/**
	 * Mutex used to prevent multiple instances being created
	 */
	private static Lock _creationMutex;
	/**
	 * Mutex used when pushing connection in the pool
	 */
	private Lock _pushMutex;
	/**
	 * Mutex used when popping a connetion from the pool
	 */
	private Lock _popMutex;
	/**
	 * This condition variable is used to wait for available
	 * connections (or space to push a connection in the pool, but this
	 * should never happen)
	 */
	private Condition _cv;

	/**
	 * Class constructor
	 */
	private DBConnectionPool() {
		
	}

	/**
	 * Size of the connection pool
	 */
	public static int MAX_CONNECTIONS = 10;

	/**
	 * Get a ConnectionPool instance. It is used to implement the  Singleton design pattern.
	 * @return	An instance to the ConnectionPool
	 */
	public static DBConnectionPool getInstance() {
		return null;
	}

	/**
	 * Get a connection from the pool
	 * @return A connection to the database
	 * @see DBConnection.hpp
	 */
	public DBConnection popConnection() {
		return null;
	}

	/**
	 * This method allows returning a database connection to the pool
	 * @param[in] connection	Connection to be returned to the pool
	 */
	public void pushConnection(DBConnection connection) {
		
	}
};