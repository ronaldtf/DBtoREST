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

#include "../utils/Utils.h"

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

void rootHandler(const std::shared_ptr<restbed::Session> session) {
	if (session->is_open()) {
	    std::string body = "DBtoREST";
	    for ( const auto key : session->keys( ) ) {
	        std::string value = session->get(key);
	        body += key + "=" + value + "\n";
	    }
	    const auto request = session->get_request( );
	    for (std::pair<std::string, std::string> param : request->get_query_parameters()) {
	        session->set(param.first, param.second);
	    }
	    session->close(restbed::OK, body, { { "Connection", "close" } } );
	} else {
		std::cerr << "Internal server error" << std::endl;
	}
}

int main() {

	std::map<std::string, std::string> properties;
	utils::Utils::getRESTProperties(properties);
	std::string host = getHost(properties);
	const short port = getPort(properties);

	std::shared_ptr<restbed::Settings> settings = std::shared_ptr<restbed::Settings>(new restbed::Settings());
	settings->set_port(port);
	settings->set_root("/");

	std::shared_ptr<restbed::Resource> rootPage = std::shared_ptr<restbed::Resource>(new restbed::Resource());
	rootPage->set_path("/");
	rootPage->set_error_handler(&errorHandler);
	rootPage->set_method_handler("GET", rootHandler);

	restbed::Service service;
	service.publish(rootPage);
	service.set_error_handler(&errorHandler);

	service.start( settings );

	return EXIT_SUCCESS;
}
