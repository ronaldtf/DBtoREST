/**
 * @file DBExecutor.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "DBExecutor.h"

#include "../pool/DBConnectionPool.h"
#include "../../utils/Utils.h"

namespace db {

DBExecutor::DBExecutor() {
}

void DBExecutor::getDBs(std::vector<std::string>& databases) {

    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<db::DBConnection> connection = connectionPool->popConnection();

	// Exclude all databases which are from the system
	std::map<std::string, bool> excludedDBs;
	connection->getSystemDBs(excludedDBs);

    connection->getList("SHOW DATABASES", databases);

    for (std::vector<std::string>::const_iterator it = databases.begin(); it != databases.end(); ) {
    	if (excludedDBs.find(*it) != excludedDBs.end())
    		it = databases.erase(it);
    	else
    		++it;
    }

	connectionPool->pushConnection(connection);

}

void DBExecutor::getTables(const std::string& db, std::vector<std::string>& tables) {
    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<db::DBConnection> connection = connectionPool->popConnection();

    connection->getList("SHOW TABLES from " + db, tables, db);

	connectionPool->pushConnection(connection);
}

void DBExecutor::getTableInfo(const std::string& db, const std::string& tableName, std::shared_ptr<db::table::Column>& table) {

    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<db::DBConnection> connection = connectionPool->popConnection();

    connection->getTable(db, tableName, table);

	connectionPool->pushConnection(connection);
}

} /* namespace account */
