/**
 * @file Server.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <iostream>

#include "../db/table/Column.h"
#include "../utils/Utils.h"
#include "RESTHandler.h"

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

int main() {

	std::map<std::string, std::string> properties;
	utils::Utils::getRESTProperties(properties);
	std::string host = getHost(properties);
	const short port = getPort(properties);

	restbed::Service service;

	std::shared_ptr<restbed::Settings> settings = std::shared_ptr<restbed::Settings>(new restbed::Settings());
	settings->set_port(port);
	settings->set_root("/");

	std::shared_ptr<restbed::Resource> swaggerJsonService = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	swaggerJsonService->set_path("/swagger.json");
	swaggerJsonService->set_method_handler("GET", &rest::RESTHandler::swaggerJson);
	service.publish(swaggerJsonService);

	// Service to show databases
	std::shared_ptr<restbed::Resource> dbsRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	dbsRequest->set_paths(std::set<std::string>{"/"});
	dbsRequest->set_error_handler(&rest::RESTHandler::errorHandler);
	dbsRequest->set_method_handler("GET", {{"Accept", "application/json"}, {"Content-Type", "application/json"}}, &rest::RESTHandler::databaseHandler);
	service.publish(dbsRequest);

	std::shared_ptr<restbed::Resource> tablesRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	tablesRequest->set_path("/alltables/{dbname:.*}");
	tablesRequest->set_error_handler(&rest::RESTHandler::errorHandler);
	tablesRequest->set_method_handler("GET", {{"Accept", "application/json"}, {"Content-Type", "application/json"}}, &rest::RESTHandler::tablesHandler);
	service.publish(tablesRequest);

	// Service to show table
	std::shared_ptr<restbed::Resource> tableRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	tableRequest->set_path("/table/{dbname:.*}/{tablename:.*}");
	tableRequest->set_error_handler(&rest::RESTHandler::errorHandler);
	tableRequest->set_method_handler("GET", {{"Accept", "application/json"}, {"Content-Type", "application/json"}}, &rest::RESTHandler::singleTableHandler);
	service.publish(tableRequest);

	service.set_error_handler(&rest::RESTHandler::errorHandler);

	service.start( settings );

	return EXIT_SUCCESS;
}
