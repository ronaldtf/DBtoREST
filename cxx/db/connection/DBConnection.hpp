/**
 * @file DBConnection.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_CONNECTION_DBCONNECTION_HPP_
#define CXX_DB_CONNECTION_DBCONNECTION_HPP_

#include <map>
#include <memory>
#include <string>
#include "../table/Column.h"

namespace db {

/**
 * This class is used as an interface which defines the operations to be done in the database.
 * It is defined as part of the Adapter design pattern.
 */
class DBConnection {
protected:
	/**
	 * Host where the database service is running. It has the format host:port
	 */
	std::string host;
	/**
	 * Port where the database service is running. It has the format host:port
	 */
	std::string port;
	/**
	 * User login used to get connected to the database.
	 */
	std::string user;
	/**
	 * User password used to authenticate the given user.
	 */
	std::string pass;

	/**
	 * Class constructor. The constructor is simply defined in order to initialize the attributes.
	 * Because the class is abstract, it will be never called directly except in the derived classes.
	 * @param[in] host		Host where the database service is running
	 * @param[in] port		Port where the database service is running
	 * @param[in] user		User login in order to get connected to the database
	 * @param[in] pass		User password used to authenticate the given user
	 */
	DBConnection(std::string host, std::string port, std::string user, std::string pass) : host(host), port(port), user(user), pass(pass) {};
public:
	/**
	 * This method allows getting the information contain in a table
	 * @param[in] db 		Database where the table is placed
	 * @param[in] tableName	Name of the table whose information is being requested
	 * @param[out] output	Table content retrieved from the database
	 */
	virtual void getTable(const std::string db, const std::string tableName, std::shared_ptr<db::table::Column>& output) const = 0;

	/**
	 * This method allows getting the information contained in a table or as a result of a query. The
	 * only constraint for this method is that the result can have one single column (otherwise, only
	 * the first column will be retrieved).
	 * @param[in] query		Query used to get the table with a single column
	 * @param[out] result	Information retrieved after running the query
	 * @param[in] db		Database used to run the query
	 */
	virtual void getList(const std::string query, std::vector<std::string>& result, const std::string db="") const = 0;

	/**
	 * This method allows retrieving the database names that belong to the database manager.
	 * @param[out] systemDBs This map has the database names as the index and "true" as the value.
	 */
	virtual void getSystemDBs(std::map<std::string, bool>& systemDBs) const = 0;

	/**
	 * Class destructor
	 */
	virtual ~DBConnection() {};
};

} /* namespace db */

#endif /* CXX_DB_CONNECTION_DBCONNECTION_HPP_ */
