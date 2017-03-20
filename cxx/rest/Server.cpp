/**
 * @file Server.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <iostream>

#include "../db/table/Column.h"
#include "../utils/Utils.h"

#include "RESTHandler.h"

/**
 * Get the host IP from the properties file
 * @param[in] properties	Map of properties
 * @return					Host IP or loopback address in case the host property is not found
 */
std::string getHost(std::map<std::string, std::string>& properties) {
	std::string hostIp = "";
	try {
		hostIp = utils::Utils::getIpAddress(properties.at("host"));
	} catch (...) {
	}
	if (hostIp.empty()) {
		std::cerr << "WARN: Could not get ip from host <" << hostIp <<
				">. Set to <localhost> (127.0.0.1)" << std::endl;
		hostIp = "127.0.0.1";
	}
	return hostIp;
}

/**
 * Get the port from the properties file
 * @param[in] properties	Map of properties
 * @return					Port or a default value (8080) in case the port property is not found
 */
short getPort(std::map<std::string, std::string>& properties) {
	int port = -1;
	try {
		port = atoi(properties.at("port").c_str());
	} catch (...) {
	}
	if (port == -1) {
		std::cerr << "WARN: Could not get port from properties (empty value). Set to <port> (8080)" << std::endl;
		port = 8080;
	}
	return port;
}

/**
 * Server implementation of the REST service. It defines the service and set
 * the handler for the accepted requests.
 * @see RestHandler.h
 */
int main() {

	// Get properties to define the service
	std::map<std::string, std::string> properties;
	utils::Utils::getRESTProperties(properties);
	const std::string host = getHost(properties);
	const short port = getPort(properties);

	restbed::Service service;

	// Set service settings
	std::shared_ptr<restbed::Settings> settings = std::shared_ptr<restbed::Settings>(new restbed::Settings());
	settings->set_port(port);
	settings->set_root("/DBtoREST");

	// Publish the swagger file. This will allow to access to the REST service
	// through the swagger UI. As the swagger UI is an optional component to use the
	// the REST service, publishing this file will not have any effect in case we
	// do not use the swagger UI.
	std::shared_ptr<restbed::Resource> swaggerJsonService = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	swaggerJsonService->set_path("/swagger.json");
	swaggerJsonService->set_method_handler("GET", &rest::RESTHandler::swaggerJson);
	service.publish(swaggerJsonService);

	// Show information when entering to the root page
	std::shared_ptr<restbed::Resource> infoRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	infoRequest->set_path("/");
	infoRequest->set_method_handler("GET", rest::RESTHandler::infoHandler);
	service.publish(infoRequest);

	// Service to show databases
	std::shared_ptr<restbed::Resource> dbsRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	dbsRequest->set_paths(std::set<std::string>{"/alldbs"});
	dbsRequest->set_error_handler(&rest::RESTHandler::errorHandler);
	dbsRequest->set_method_handler("GET", &rest::RESTHandler::databaseHandlerJson); // Set the default return type when return type is not specified
	dbsRequest->set_method_handler("GET", {{"Accept", "application/xml"}, {"Content-Type", "application/xml"}}, &rest::RESTHandler::databaseHandlerXml);
	service.publish(dbsRequest);

	// Service to show tables from a database
	std::shared_ptr<restbed::Resource> tablesRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	tablesRequest->set_path("/alltables/{dbname:.*}");
	tablesRequest->set_error_handler(&rest::RESTHandler::errorHandler); // Set the default return type when return type is not specified
	tablesRequest->set_method_handler("GET", &rest::RESTHandler::tablesHandlerJson);
	tablesRequest->set_method_handler("GET", {{"Accept", "application/xml"}, {"Content-Type", "application/xml"}}, &rest::RESTHandler::tablesHandlerXml);
	service.publish(tablesRequest);

	// Service to show table contents
	std::shared_ptr<restbed::Resource> tableRequest = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	tableRequest->set_path("/table/{dbname:.*}/{tablename:.*}");
	tableRequest->set_method_handler("GET", &rest::RESTHandler::singleTableHandlerJson);
	tableRequest->set_error_handler(&rest::RESTHandler::errorHandler); // Set the default return type when return type is not specified
	tableRequest->set_method_handler("GET", {{"Accept", "application/xml"}, {"Content-Type", "application/xml"}}, &rest::RESTHandler::singleTableHandlerXml);
	service.publish(tableRequest);

	// Define the error handler
	service.set_error_handler(&rest::RESTHandler::errorHandler);

	service.start( settings );

	return EXIT_SUCCESS;
}
