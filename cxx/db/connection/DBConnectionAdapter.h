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

class DBConnectionAdapter: public DBConnection {
private:
	static sql::Driver* _driver;
	sql::Connection* _connection;
public:
	DBConnectionAdapter(std::string host, std::string user, std::string pass);
	void getTable(const std::string db, const std::string tableName, std::shared_ptr<db::table::Column>& output) const;
	void getList(const std::string query, std::vector<std::string>& result, const std::string db="") const;
	void getSystemDBs(std::map<std::string, bool>& systemDBs) const;
	virtual ~DBConnectionAdapter();
};

} /* namespace db */

#endif /* CXX_DB_CONNECTION_DBCONNECTIONADAPTER_H_ */
