package db.connection;

import java.sql.Connection;
import java.sql.Driver;
import java.util.Map;
import java.util.Vector;

import db.table.Column;

/**
 * This class implements the methods defined in the DBConnection interface.
 * These methods are implemented for working with a MySQL database.
 * The class is part of the Adapter design pattern.
 * @see DBConnection.java
 */
public class DBConnectionAdapter extends DBConnection {

	/**
	 * MySQL database driver
	 */
	private Driver _driver;
	/**
	 * MySQL database connection
	 */
	private Connection _connection;
	
	/**
	 * Class constructor
	 * @param[in] address	Address where the database service is running. It has the format host:port
	 * @param[in] user		User login used to get connected to the database
	 * @param[in] pass		Password used to authenticate the user
	 */
	public DBConnectionAdapter(String address, String user, String pass) {
		super(address, user, pass);
	}

	/**
	 * This method allows retrieving the information contained in a table from the database
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection.java
	 * @param[in] db		Name of the database
	 * @param[in] tableName	Name of the table whose information is going to be retrieved
	 * @param[out] output	Table content retrieved from the database
	 */
	@Override
	public void getTable(String db, String tableName, Column output) {
		
	}

	/**
	 * This method allows retrieving the information contained in a table from the database
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection.java
	 * @param[in] db		Name of the database
	 * @param[in] tableName	Name of the table whose information is going to be retrieved
	 * @param[out] output	Table content retrieved from the database
	 */
	@Override
	public void getList(String query, Vector<String> result, String db) {
		
	}

	/**
	 * This method allows getting the information contained in a table or as a result of a query. The
	 * only constraint for this method is that the result can have one single column (otherwise, only
	 * the first column will be retrieved).
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection.java
	 * @param[in] query		Query used to get the table with a single column
	 * @param[out] result	Information retrieved after running the query
	 * @param[in] db		Database used to run the query
	 */
	@Override
	public void getList(String query, Vector<String> result) {
		
	}

	/**
	 * This method allows retrieving the database names that belong to the database manager.
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection.java
	 * @param[out] systemDBs This map has the database names as the index and "true" as the value.
	 */
	@Override
	public void getSystemDBs(Map<String, Boolean> systemDBs) {
		
	}

}
