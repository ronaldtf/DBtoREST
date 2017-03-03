package main.java.db.connection;

import java.util.Vector;

import db.table.Column;

/**
 * This class is used in order to extract information from the database. Its methods simply
 * get a connection from the connection pool and then delegate to the DBConnection implementation
 * class.
 * @see DBConnection.java
 * @see DBConnectionAdapter.java
 */
public class DBExecutor {
	/**
	 * Class constructor
	 */
	private DBExecutor() {
	}
	
	/**
	 * This method retrieves the list of database names, excluding the system databases
	 * @param[out] databases	List of database names
	 */
	public static void getDBs(Vector<String> databases) {
		
	}

	/**
	 * This method retrieves the list of tables which are in a specific database name
	 * @param[in] db		Database name
	 * @param[out] tables	Table names in the database
	 */
	public static void getTables(final String db, Vector<String> tables) {
		
	}

	/**
	 * This method retrieves the content of a table from a database
	 * @param[in] db		Database name
	 * @param[in] tableName	Name of the table
	 * @param[out] table	Table content retrieved from the database
	 */
	public static void getTableInfo(final String db, final String tableName, Column table) {
		
	}
}

