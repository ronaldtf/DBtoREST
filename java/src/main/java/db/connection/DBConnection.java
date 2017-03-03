package main.java.db.connection;

import java.util.Map;
import java.util.Vector;

import db.table.Column;

/**
 * This class is used as an interface which defines the operations to be done in the database.
 * It is defined as part of the Adapter design pattern.
 */
public abstract class DBConnection {

	/**
	 * Address where the database service is running. It has the format host:port
	 */
	protected String address;
	/**
	 * User login used to get connected to the database.
	 */
	protected String user;
	/**
	 * User password used to authenticate the given user.
	 */
	protected String pass;
	
	/**
	 * Class constructor. The constructor is simply defined in order to initialize the attributes.
	 * Because the class is abstract, it will be never called directly except in the derived classes.
	 * @param[in] address	Address where the database service is running
	 * @param[in] user		User login in order to get connected to the database
	 * @param[in] pass		User password used to authenticate the given user
	 */
	protected DBConnection(final String address, final String user, final String pass) {
		this.address = address;
		this.user = user;
		this.pass = pass;
	}
	
	/**
	 * This method allows getting the information contain in a table
	 * @param[in] db 		Database where the table is placed
	 * @param[in] tableName	Name of the table whose information is being requested
	 * @param[out] output	Table content retrieved from the database
	 */
	public abstract void getTable(final String db, final String tableName, Column output);
	
	/**
	 * This method allows getting the information contained in a table or as a result of a query. The
	 * only constraint for this method is that the result can have one single column (otherwise, only
	 * the first column will be retrieved).
	 * @param[in] query		Query used to get the table with a single column
	 * @param[out] result	Information retrieved after running the query
	 * @param[in] db		Database used to run the query
	 */
	public abstract void getList(final String query, Vector<String> result, final String db);

	/**
	 * This method allows getting the information contained in a table or as a result of a query. The
	 * only constraint for this method is that the result can have one single column (otherwise, only
	 * the first column will be retrieved).
	 * @param[in] query		Query used to get the table with a single column
	 * @param[out] result	Information retrieved after running the query
	 */
	public abstract void getList(final String query, Vector<String> result);
	
	/**
	 * This method allows retrieving the database names that belong to the database manager.
	 * @param[out] systemDBs This map has the database names as the index and "true" as the value.
	 */
	public abstract void getSystemDBs(Map<String, Boolean> systemDBs);

	
}
