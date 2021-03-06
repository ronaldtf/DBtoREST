/**
 * @file Utils.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Utils.h"
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sstream>

namespace utils {

const char Utils::SEPARATOR = ':';
const std::string Utils::DB_CONF = "conf/db.properties";
const std::string Utils::REST_CONF = "conf/rest.properties";

void Utils::trim(std::string &s) {
	// Remove spaces at the beginning of the string
	s.erase(s.begin(),  std::find_if(s.begin(),  s.end(),  std::not1(std::ptr_fun<int,int>(std::isspace))));
	// Remove spaces at the end of the string
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int,int>(std::isspace))).base(), s.end());
};


std::vector<std::string> Utils::tokenize(const std::string &s) {
	std::vector<std::string> tokens;
	std::string::const_iterator it = s.begin();
	while (it != s.end()) {
		std::string::const_iterator it2 = std::find(it, s.end(), Utils::SEPARATOR);
		std::string tmp = std::string(it, it2);
		trim(tmp);
		if (!tmp.empty()) {
			tokens.push_back(tmp);
		}
		it = (it2 == s.end()) ? it2 : it2 + 1;
	}
	return tokens;
}


void Utils::parseFile(const std::string fileName, std::map<std::string, std::string> &properties) {
	std::ifstream *ifs = new std::ifstream(fileName, std::ios::in);
	std::string line;
	std::vector<std::string> tokens;
	while (std::getline(*ifs, line)) {
		// Disable comment or empty lines
		if (line.empty() || line.at(0) == '#')
			continue;
		trim(line);
		tokens = tokenize(line);
		if (tokens.size() < 2) {
			std::cerr << "Wrong file format. It must contain lines with <key> <value>" << std::endl;
			throw std::exception();
		} else {
			properties.insert(std::make_pair(tokens.at(0), tokens.at(1)));
		}
		tokens.clear();
	}
	ifs->close();
}

void Utils::getDBProperties(std::map<std::string, std::string>& properties) {
	parseFile(DB_CONF, properties);
}

void Utils::getRESTProperties(std::map<std::string, std::string>& properties) {
	parseFile(REST_CONF, properties);
}

std::string Utils::getIpAddress(const std::string hostname) {
	struct hostent* hostEnt = gethostbyname(hostname.c_str());
	if (hostEnt == NULL) {
		herror("gethostbyname");
		return "";
	}
	return std::string(inet_ntoa(*(struct in_addr*)hostEnt->h_addr));
}

int Utils::str2int(std::string& s) {
	try {
		int ret_int;
		std::istringstream iss(s);
		iss >> ret_int;
		return ret_int;
	} catch(...) {
		return -1;
	}
}

} /* namespace account */
