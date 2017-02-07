/**
 * @file Server.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <restbed>

#include "../db/DBConnectionPool.h"
#include "../db/DBConnector.h"
#include "../utils/Utils.h"
#include "JsonGenerator.h"
#include "../db/table/Column.h"

std::string getHost(std::map<std::string, std::string>& properties) {
	std::string hostIp = "";
	try {
		hostIp = utils::Utils::getIpAddress(properties.at("host"));
	} catch (...) {
	}
	if (hostIp.empty()) {
		std::cerr << "WARN: Could not get ip from host <" << hostIp << ">. Set to <localhost> (127.0.0.1)" << std::endl;
		hostIp = "127.0.0.1";
	}
	return hostIp;
}

short getPort(std::map<std::string, std::string>& properties) {
	int port = -1;
	try {
		port = atoi(properties.at("port").c_str());
	} catch (...) {
	}
	if (port == -1) {
		std::cerr << "WARN: Could not get port from properties (empty value). Set to <port> (8000)" << std::endl;
		port = 8000;
	}
	return port;
}

void errorHandler( const int, const std::exception&, const std::shared_ptr<restbed::Session> session) {
	throw restbed::SERVICE_UNAVAILABLE;
}

void getDBs(std::vector<std::string>& v) {
    std::vector<std::string> dbs;
    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<sql::Connection> connection = connectionPool->popConnection();
    db::DBConnector::getDBs(connection.get(), v);
    connectionPool->pushConnection(connection);
}


void getTables(const std::string dbName, std::vector<std::string>& tables) {
    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<sql::Connection> connection = connectionPool->popConnection();
    db::DBConnector::getTables(connection.get(), dbName, tables);
    connectionPool->pushConnection(connection);
}

void getSingleTable(const std::string dbName, const std::string tableName, std::shared_ptr<db::table::Column>& table) {
    std::shared_ptr<db::ConnectionPool> connectionPool = db::ConnectionPool::getInstance();
    std::shared_ptr<sql::Connection> connection = connectionPool->popConnection();
    db::DBConnector::getTableInfo(connection.get(), dbName, tableName, table);
    connectionPool->pushConnection(connection);
}

void datbaseHandler(const std::shared_ptr<restbed::Session> session) {
	if (session->is_open()) {
	    std::vector<std::string> databases;
	    getDBs(databases);
	    std::string body;
	    rest::JsonGenerator::getJson("databases", databases, body);

	    session->close(restbed::OK, body, { { "Connection", "close" } } );
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

void tablesHandler(const std::shared_ptr<restbed::Session> session) {
	if (session->is_open()) {
		std::string db;
		const std::shared_ptr<const restbed::Request> request = session->get_request();
		db = request->get_path_parameter("dbname", "/");

		std::vector<std::string> tables;
		getTables(db, tables);
	    std::string body;

	    rest::JsonGenerator::getJson("tables", tables, body);

	    session->close(restbed::OK, body, { { "Connection", "close" } } );
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

void singleTableHandler(const std::shared_ptr<restbed::Session> session) {
	if (session->is_open()) {
		const std::shared_ptr<const restbed::Request> request = session->get_request();
		const std::string dbName = request->get_path_parameter("dbname", "/");
		const std::string tableName = request->get_path_parameter("tablename", "/");

		std::shared_ptr<db::table::Column> table;
		getSingleTable(dbName, tableName, table);

	    std::string body;
		rest::JsonGenerator::getJson(tableName, table, body);

	    session->close(restbed::OK, body, { { "Connection", "close" } } );
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

int main() {

	std::map<std::string, std::string> properties;
	utils::Utils::getRESTProperties(properties);
	std::string host = getHost(properties);
	const short port = getPort(properties);

	restbed::Service service;

	std::shared_ptr<restbed::Settings> settings = std::shared_ptr<restbed::Settings>(new restbed::Settings());
	settings->set_port(port);
	settings->set_root("/");

	// Service to show databases
	std::shared_ptr<restbed::Resource> dbsRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	dbsRequest->set_paths(std::set<std::string>{"/"});
	dbsRequest->set_error_handler(&errorHandler);
	dbsRequest->set_method_handler("GET", datbaseHandler);
	service.publish(dbsRequest);

	std::vector<std::string> dbs;
	getDBs(dbs);
	for (const std::string db : dbs) {

		// Service to show tables in a database
		std::shared_ptr<restbed::Resource> tablesRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
		tablesRequest->set_path("/{dbname:" + db + "}");
		tablesRequest->set_error_handler(&errorHandler);
		tablesRequest->set_method_handler("GET", tablesHandler);
		service.publish(tablesRequest);

		std::vector<std::string> tables;
		getTables(db, tables);
		for (const std::string table : tables) {
			// Service to show table
			std::shared_ptr<restbed::Resource> tableRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
			tableRequest->set_path("/{dbname:" + db + "}/{tablename:" + table + "}");
			tableRequest->set_error_handler(&errorHandler);
			tableRequest->set_method_handler("GET", singleTableHandler);
			service.publish(tableRequest);
		}
	}

	service.set_error_handler(&errorHandler);

	service.start( settings );

	return EXIT_SUCCESS;
}
