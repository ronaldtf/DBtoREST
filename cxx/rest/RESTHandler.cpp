/**
 * @file RESTHandler.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../db/pool/DBConnectionPool.h"
#include "../db/connection/DBConnection.hpp"
#include "../db/connection/DBExecutor.h"
#include "../db/table/Column.h"
#include "../utils/Utils.h"

#include "JsonGenerator.h"
#include "JsonToXml.h"
#include "RESTHandler.h"

namespace rest {

void RESTHandler::getResponse(const int responseCode, const std::string& body, restbed::Response& response) {
	// Set response headers
	response.add_header("Access-Control-Allow-Origin", "*");
	response.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, DELETE");
	response.add_header("Access-Control-Max-Age", "3600");
	response.add_header("Access-Control-Allow-Headers", "x-requested-with");
	// Set response code
	response.set_status_code(responseCode);
	// Set body
	response.set_body(body);

	response.add_header("Connection", "close");
}

void RESTHandler::databaseHandlerJson(const std::shared_ptr<restbed::Session> session) {
	databaseHandler(session, JSON);
}

void RESTHandler::databaseHandlerXml(const std::shared_ptr<restbed::Session> session) {
	databaseHandler(session, XML);
}

void RESTHandler::databaseHandler(const std::shared_ptr<restbed::Session> session, const formatType format) {
	if (session->is_open()) {
		try {
			std::vector<std::string> databases;
			db::DBExecutor::getDBs(databases);
			std::string body;
			rest::JsonGenerator::getJson("database", databases, body);

			restbed::Response response;
			if (format == JSON)
				getResponse(restbed::OK, body, response);
			else
				getResponse(restbed::OK, rest::JsonToXml::json2xml(body, "databases"), response);
			session->close(response);
		} catch (...) {
			std::cerr << "Internal server error" << std::endl;
			session->close(400, "Internal server error");
		}
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

void RESTHandler::tablesHandlerJson(const std::shared_ptr<restbed::Session> session) {
	tablesHandler(session, JSON);
}

void RESTHandler::tablesHandlerXml(const std::shared_ptr<restbed::Session> session) {
	tablesHandler(session, XML);
}

void RESTHandler::tablesHandler(const std::shared_ptr<restbed::Session> session, const formatType format) {
	if (session->is_open()) {
		try {
			std::string db;
			const std::shared_ptr<const restbed::Request> request = session->get_request();
			db = request->get_path_parameter("dbname", "/");

			std::vector<std::string> tables;
			db::DBExecutor::getTables(db, tables);
			std::string body;

			rest::JsonGenerator::getJson("table", tables, body);

			restbed::Response response;
			if (format == JSON)
				getResponse(restbed::OK, body, response);
			else
				getResponse(restbed::OK, rest::JsonToXml::json2xml(body, "tables"), response);
			session->close(response);
		} catch (...) {
			std::cerr << "Internal server error" << std::endl;
			session->close(400, "Internal server error");
		}
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

void RESTHandler::singleTableHandlerJson(const std::shared_ptr<restbed::Session> session) {
	singleTableHandler(session, JSON);
}

void RESTHandler::singleTableHandlerXml(const std::shared_ptr<restbed::Session> session) {
	singleTableHandler(session, XML);
}

void RESTHandler::singleTableHandler(const std::shared_ptr<restbed::Session> session, const formatType format) {
	if (session->is_open()) {
		try {
			const std::shared_ptr<const restbed::Request> request = session->get_request();
			const std::string dbName = request->get_path_parameter("dbname", "/");
			const std::string tableName = request->get_path_parameter("tablename", "/");

			std::shared_ptr<db::table::Column> table;
			db::DBExecutor::getTableInfo(dbName, tableName, table);

			std::string body;
			rest::JsonGenerator::getJson(tableName, table, body);

			restbed::Response response;
			if (format == JSON)
				getResponse(restbed::OK, body, response);
			else
				getResponse(restbed::OK, rest::JsonToXml::json2xml(body, "table"), response);
			session->close(response);
		} catch (...) {
			std::cerr << "Internal server error" << std::endl;
			session->close(400, "Internal server error");
		}
	} else {
		std::cerr << "Internal server error" << std::endl;
		session->close(400, "Internal server error");
	}
}

void RESTHandler::errorHandler( const int, const std::exception&, const std::shared_ptr<restbed::Session> session) {
	throw restbed::SERVICE_UNAVAILABLE;
}

void RESTHandler::swaggerJson(const std::shared_ptr<restbed::Session> session) {
	std::string body;
	std::string tmpStr;

	std::ifstream ifstr = std::ifstream(std::string("../swagger/swagger.json").c_str());
	while (std::getline(ifstr, tmpStr)) {
		utils::Utils::trim(tmpStr);
		body += tmpStr + " ";
	}
	ifstr.close();
	session->set_headers({{"Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT"},{"Access-Control-Allow-Origin", "*"}});
	session->close(restbed::OK, body, { {"Connection", "close"} });
}

} /* namespace rest */
