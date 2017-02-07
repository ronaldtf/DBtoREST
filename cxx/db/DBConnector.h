/**
 * @file DBConnector.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_DBCONNECTOR_H_
#define CXX_DB_DBCONNECTOR_H_

#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <vector>

#include "table/Column.h"

namespace db {

class DBConnector {
private:
	DBConnector();
public:
	static void getDBs(sql::Connection* connection, std::vector<std::string>& databases);
	static void getTables(sql::Connection* connection, const std::string& db, std::vector<std::string>& tables);
	static void getTableInfo(sql::Connection* connection, const std::string& db, const std::string& tableName, std::shared_ptr<db::table::Column> table);
};

} /* namespace account */

#endif /* CXX_DB_DBCONNECTOR_H_ */
