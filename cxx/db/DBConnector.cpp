/**
 * @file DBConnector.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "DBConnector.h"
#include <utility>

namespace db {

DBConnector::DBConnector() {
}

void DBConnector::getDBs(sql::Connection* connection, std::vector<std::string>& databases) {

	// Exclude all databases which are from the system (mysql)
	std::map<const std::string, bool> excludedDBs = std::map<const std::string, bool>();
	excludedDBs.insert(std::make_pair<std::string, bool>("information_schema", true));
	excludedDBs.insert(std::make_pair<std::string, bool>("mysql", true));
	excludedDBs.insert(std::make_pair<std::string, bool>("performance_schema", true));
	excludedDBs.insert(std::make_pair<std::string, bool>("sys", true));

	std::auto_ptr<sql::Statement> statement;
	std::auto_ptr<sql::ResultSet> resultSet;

	databases = std::vector<std::string>();

	statement.reset(connection->createStatement());
	resultSet.reset(statement->executeQuery("SHOW DATABASES"));
	while (resultSet->next()) {
		// Get the unique column (offset starts in 1 - not in 0 as C++
		const std::string dbString = resultSet->getString(1);
		if (excludedDBs.find(dbString) == excludedDBs.end())
			databases.push_back(dbString);
	}
}

void DBConnector::getTables(sql::Connection* connection, const std::string db, std::vector<std::string>& tables) {
	std::auto_ptr<sql::Statement> statement;
	std::auto_ptr<sql::ResultSet> resultSet;

	tables = std::vector<std::string>();
	connection->setSchema(db);

	statement.reset(connection->createStatement());
	resultSet.reset(statement->executeQuery("SHOW TABLES from " + db));
	while (resultSet->next()) {
		// Get the unique column (offset starts in 1 - not in 0 as C++
		const std::string dbString = resultSet->getString(1);
		tables.push_back(dbString);
	}
}

} /* namespace account */
