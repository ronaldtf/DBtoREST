/**
 * @file DBConnectionAdapter.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "DBConnectionAdapter.h"
#include "../../exception/DBException.hpp"

namespace db {

// Get the driver instance from the MySQL connector
sql::Driver* DBConnectionAdapter::_driver = get_driver_instance();

DBConnectionAdapter::DBConnectionAdapter(std::string address, std::string user, std::string pass) : DBConnection(address, user, pass) {
	try {
		// Get the connection
		_connection = _driver->connect(address, user, pass);
	} catch (sql::SQLException& e) {
		// When the maximum number of connections is exceeded, an exception with error code 2026
		// is thrown
		if ( e.getErrorCode() == 2026 ) {
			std::cerr << "Maximum number of connections exceeded (" << e.what() << ")" << std::endl;
			throw exception::DBException("Max number of connections exceeded", e.getErrorCode());
		} else {
			std::cerr << e.what() << std::endl;
			// A different problem has occurred
			throw exception::DBException(e.what());
		}
	}
}

void DBConnectionAdapter::getList(const std::string query, std::vector<std::string>& result, const std::string db) const {
	std::auto_ptr<sql::Statement> statement;
	std::auto_ptr<sql::ResultSet> resultSet;
	try {
		// If the database has been defined, we set it
		if (!db.empty())
		_connection->setSchema(db);

		// Create the statement and run the query
		statement.reset(_connection->createStatement());
		resultSet.reset(statement->executeQuery(query));

		// Retrieve the results
		while (resultSet->next()) {
			// Get the unique column (offset starts in 1 - not in 0 as C++)
			const std::string tableName = resultSet->getString(1);
			result.push_back(tableName);
		}
	} catch (sql::SQLException& e) {
		std::cerr << e.what() << std::endl;
		throw exception::DBException(e.what(), e.getErrorCode());
	}
}

void DBConnectionAdapter::getTable(const std::string db, const std::string tableName, std::shared_ptr<db::table::Column>& output) const {
	std::auto_ptr<sql::Statement> statement;
	std::auto_ptr<sql::ResultSet> resultSet;

	try {
		// If the database has been defined, we set it
		if (!db.empty())
			_connection->setSchema(db);

		// First, we need to get the structure of the table
		// We request to the database how is the structure of the database and initialize
		// the output.
		statement.reset(_connection->createStatement());
		resultSet.reset(statement->executeQuery("DESC " + tableName));

		output = nullptr;
		db::table::Column* neighbor = nullptr;

		size_t numColumns = 0;
		while (resultSet->next()) {
			if (numColumns == 0) {
				output = std::shared_ptr<db::table::Column>(new db::table::Column(resultSet->getString(1)));
				neighbor = output.get();
			} else {
				std::shared_ptr<db::table::Column> next = std::shared_ptr<db::table::Column>(new db::table::Column(resultSet->getString(1)));
				neighbor->setNeighbor(next);
				neighbor = next.get();
			}
			++numColumns;
		}

		// Then, we fill the output structure with the table contents
		statement.reset(_connection->createStatement());
		resultSet.reset(statement->executeQuery("SELECT * FROM " + tableName));
		while (resultSet->next()) {
			neighbor = output.get();
			for (size_t i = 1; i <= numColumns; ++i) {
				neighbor->addValue(resultSet->getString(i));
				neighbor = neighbor->getNeighbor().get();
			}
		}
	} catch (sql::SQLException& e) {
		std::cerr << e.what() << std::endl;
		throw exception::DBException(e.what(), e.getErrorCode());
	}
}

void DBConnectionAdapter::getSystemDBs(std::map<std::string, bool>& systemDBs) const {
	// We exclude those databases which are from the system
	systemDBs = {{"information_schema", true},
			     {"mysql", true},
				 {"performance_schema", true},
				 {"sys", true}};
}

DBConnectionAdapter::~DBConnectionAdapter() {
}

} /* namespace db */
