package main.java.db.pool;

import java.util.Deque;
import java.util.Map;
import java.util.Properties;
import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import main.java.db.connection.DBConnection;
import main.java.db.connection.DBConnectionAdapter;
import main.java.exception.DBException;
import utils.Utils;

/**
 * This class defines a pool of database connections
 * It implements the Object Pool design pattern (and the Singleton design pattern)
 * @see DBConnection
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
	 * Mutex used when pushing connection in the pool
	 */
	private Lock _pushMutex;
	/**
	 * Mutex used when popping a connection from the pool
	 */
	private Lock _popMutex;
	/**
	 * This condition variable is used to wait for available
	 * connections
	 */
	private Condition _cvEmpty;
	/**
	 * This condition variable is used to wait until there is a slot in the 
	 * pool to place a new connection (but this should never happen).
	 */
	private Condition _cvFull;

	/**
	 * Class constructor
	 * @exception Exception Throws an exception in case an inialization problem has occurred.
	 */
	private DBConnectionPool() throws Exception {
		_pushMutex = new ReentrantLock();
		_popMutex = new ReentrantLock();
		
		Properties properties = null;
		try {
			properties = Utils.getRESTProperties();
			
			String host = properties.getProperty("dbhost");
			String port = properties.getProperty("dbport");
			String user = properties.getProperty("username");
			String pass = properties.getProperty("password");
			String max  = properties.getProperty("max_connections");
			
			int max_conn = -1;
			try {
				max_conn = Integer.parseInt(max);
			} catch (NumberFormatException nfe) {
			}

			System.out.println("Connecting to " + host + ":" + port + " with username <" + user + ">, pass <" + pass + ">");

			if (max_conn == -1) {
				System.err.println("[WARN] Maximum connections has not been (correctly) defined. Use the default (10)");
			} else {
				MAX_CONNECTIONS = max_conn;
				System.out.println("[INFO] Using a pool of " + String.valueOf(MAX_CONNECTIONS) + " connections...");
			}

			try {
				for (int i=0; i<MAX_CONNECTIONS; ++i) {
					_pool.push(new DBConnectionAdapter(host, port, user, pass));
				}
			} catch (DBException dbe) {
				// Max No. of connections exceeded
				System.err.println(dbe.getMessage());
			}
			
		} catch (Exception e) {
			throw e;
		}
	}

	/**
	 * Size of the connection pool
	 */
	public static int MAX_CONNECTIONS = 10;

	/**
	 * Get a ConnectionPool instance. It is used to implement the  Singleton design pattern.
	 * @return	An instance to the ConnectionPool
	 */
	public static DBConnectionPool getInstance() throws Exception{
		synchronized(_instance) {
			if (_instance == null)
				_instance = new DBConnectionPool();
			return _instance;
		}
	}

	/**
	 * Get a connection from the pool
	 * @return A connection to the database
	 * @see DBConnection
	 */
	public DBConnection popConnection() throws DBException {
		DBConnection connection = null;
		try {
			_popMutex.lock();
			while (_pool.isEmpty())
				_cvEmpty.await();
			connection = _pool.pollLast();
			_cvFull.signal();
		} catch (InterruptedException ie) {
			System.err.println("[ERROR] A problem in DBConnectionPool has occurred: " + ie.getMessage());
			throw new DBException(ie.getMessage());
		} finally {
			_popMutex.unlock();
		}
		return connection;
	}

	/**
	 * This method allows returning a database connection to the pool
	 * @param connection	Connection to be returned to the pool
	 */
	public void pushConnection(DBConnection connection) throws DBException {
		try {
			_pushMutex.lock();			
			while (_pool.size() == MAX_CONNECTIONS)
				_cvFull.await();
			_pool.push(connection);
			_cvEmpty.signal();
		} catch (InterruptedException ie) {
			System.err.println("[ERROR] A problem in DBConnectionPool has occurred: " + ie.getMessage());
			throw new DBException(ie.getMessage());
		} finally {
			_pushMutex.unlock();
		}
	}
};