/**
 * @file DBConnectionAdapter.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_CONNECTION_DBCONNECTIONADAPTER_H_
#define CXX_DB_CONNECTION_DBCONNECTIONADAPTER_H_

#include <map>
#include <memory>
#include <vector>

#include <mysql_connection.h>
#include <cppconn/driver.h>

#include "DBConnection.hpp"

namespace db {

/**
 * This class implements the methods defined in the DBConnection interface.
 * These methods are implemented for working with a MySQL database.
 * The class is part of the Adapter design pattern.
 * @see DBConnection.h
 */
class DBConnectionAdapter: public DBConnection {
private:
	/**
	 * MySQL database driver
	 */
	static sql::Driver* _driver;
	/**
	 * MySQL database connection
	 */
	sql::Connection* _connection;
public:
	/**
	 * Class constructor
	 * @param[in] host		Host where the database service is running
	 * @param[in] port		Port where the database serviceis running
	 * @param[in] user		User login used to get connected to the database
	 * @param[in] pass		Password used to authenticate the user
	 */
	DBConnectionAdapter(std::string host, std::string port, std::string user, std::string pass);

	/**
	 * This method allows retrieving the information contained in a table from the database
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection
	 * @param[in] db		Name of the database
	 * @param[in] tableName	Name of the table whose information is going to be retrieved
	 * @param[out] output	Table content retrieved from the database
	 */
	void getTable(const std::string db, const std::string tableName, std::shared_ptr<db::table::Column>& output) const;

	/**
	 * This method allows getting the information contained in a table or as a result of a query. The
	 * only constraint for this method is that the result can have one single column (otherwise, only
	 * the first column will be retrieved).
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection
	 * @param[in] query		Query used to get the table with a single column
	 * @param[out] result	Information retrieved after running the query
	 * @param[in] db		Database used to run the query
	 * @exception DBException Throws an exception in case a problem with the DB has occurred
	 */
	void getList(const std::string query, std::vector<std::string>& result, const std::string db="") const;

	/**
	 * This method allows retrieving the database names that belong to the database manager.
	 * The method derives from the base class <code>DBConnection</code>
	 * @see DBConnection
	 * @param[out] systemDBs This map has the database names as the index and "true" as the value.
	 */
	void getSystemDBs(std::map<std::string, bool>& systemDBs) const;

	/**
	 * Class destructor
	 */
	virtual ~DBConnectionAdapter();
};

} /* namespace db */

#endif /* CXX_DB_CONNECTION_DBCONNECTIONADAPTER_H_ */
