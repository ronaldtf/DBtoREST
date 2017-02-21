/**
 * @file DBConnection.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_CONNECTION_DBCONNECTION_HPP_
#define CXX_DB_CONNECTION_DBCONNECTION_HPP_

#include <memory>
#include <string>
#include "../table/Column.h"

namespace db {

class DBConnection {
protected:
	std::string host;
	std::string user;
	std::string pass;
	DBConnection(std::string host, std::string user, std::string pass) : host(host), user(user), pass(pass) {};
public:
	virtual void getTable(const std::string db, const std::string tableName, std::shared_ptr<db::table::Column>& output) = 0;
	virtual void getList(const std::string query, std::vector<std::string>& result, const std::string db="") = 0;
	virtual ~DBConnection() {};
};

} /* namespace db */

#endif /* CXX_DB_CONNECTION_DBCONNECTION_HPP_ */
