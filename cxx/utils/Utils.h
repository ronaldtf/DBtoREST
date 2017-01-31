/**
 * @file Utils.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_UTILS_UTILS_H_
#define CXX_UTILS_UTILS_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace utils {

class Utils {
public:

	static const char SEPARATOR;

	enum dbVarType { INT, STRING, DATE, UNKNOWN };

	static void trim(std::string &s);
	static std::vector<std::string> tokenize(const std::string &s);
	static void parseFile(const std::string fileName, std::map<std::string, std::string> &properties);
	static std::string getIpAddress(std::string hostname);
	static int str2int(std::string& s);
	static dbVarType getType(const std::string& s);

};

} /* namespace account */

#endif /* CXX_UTILS_UTILS_H_ */
