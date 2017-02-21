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

sql::Driver* DBConnectionAdapter::_driver = get_driver_instance();

DBConnectionAdapter::DBConnectionAdapter(std::string host, std::string user, std::string pass) : DBConnection(host, user, pass) {
	try {
		_connection = _driver->connect(host, user, pass);
	} catch (sql::SQLException& e) {
		if ( e.getErrorCode() == 2026 ) // Max No. of connections exceeded
			throw exception::DBException("Max number of connections exceeded", e.getErrorCode());
		else
			throw std::exception();

	}
}

void DBConnectionAdapter::getList(const std::string query, std::vector<std::string>& result, const std::string db) const {
	std::auto_ptr<sql::Statement> statement;
	std::auto_ptr<sql::ResultSet> resultSet;
	try {
		if (!db.empty())
		_connection->setSchema(db);

		statement.reset(_connection->createStatement());
		resultSet.reset(statement->executeQuery(query));
		while (resultSet->next()) {
			// Get the unique column (offset starts in 1 - not in 0 as C++
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
		if (!db.empty())
			_connection->setSchema(db);

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

		statement.reset(_connection->createStatement());
		resultSet.reset(statement->executeQuery("SELECT * FROM " + tableName));

		while (resultSet->next()) {
			neighbor = output.get();
			for (size_t i = 1; i<=numColumns; ++i) {
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
	systemDBs = std::map<std::string, bool>();
	systemDBs.insert(std::make_pair<std::string, bool>("information_schema", true));
	systemDBs.insert(std::make_pair<std::string, bool>("mysql", true));
	systemDBs.insert(std::make_pair<std::string, bool>("performance_schema", true));
	systemDBs.insert(std::make_pair<std::string, bool>("sys", true));
}

DBConnectionAdapter::~DBConnectionAdapter() {
}

} /* namespace db */
