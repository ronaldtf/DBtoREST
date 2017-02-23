/**
 * @file DBExecutor.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_DBEXECUTOR_H_
#define CXX_DB_DBEXECUTOR_H_
#include <memory>
#include <vector>

#include "../table/Column.h"

namespace db {

/**
 * This class is used in order to extract information from the database. Its methods simply
 * get a connection from the connection pool and then delegate to the DBConnection implementation
 * class.
 * @see DBConnection.hpp
 * @see DBConnectionAdapter.h
 */
class DBExecutor {
private:
	/**
	 * Class constructor
	 */
	DBExecutor();
public:
	/**
	 * This method retrieves the list of database names, excluding the system databases
	 * @param[out] databases	List of database names
	 */
	static void getDBs(std::vector<std::string>& databases);

	/**
	 * This method retrieves the list of tables which are in a specific database name
	 * @param[in] db		Database name
	 * @param[out] tables	Table names in the database
	 */
	static void getTables(const std::string& db, std::vector<std::string>& tables);

	/**
	 * This method retrieves the content of a table from a database
	 * @param[in] db		Database name
	 * @param[in] tableName	Name of the table
	 * @param[out] table	Table content retrieved from the database
	 */
	static void getTableInfo(const std::string& db, const std::string& tableName, std::shared_ptr<db::table::Column>& table);
};

} /* namespace account */

#endif /* CXX_DB_DBEXECUTOR_H_ */
