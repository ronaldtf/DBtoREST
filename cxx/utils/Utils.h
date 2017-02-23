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

/**
 * This classes defines the generic utilities for different purposes
 */
class Utils {
private:
	/**
	 * This method parses a properties file and stores the key and values in a map
	 * @param[in] fileName		Parameter file
	 * @param[out] properties	Map with the propertyName as key and propertyValue as value
	 */
	static void parseFile(const std::string fileName, std::map<std::string, std::string> &properties);
public:
	/**
	 * Separator in the properties file
	 */
	static const char SEPARATOR;
	/**
	 * Database connection properties file
	 */
	static const std::string DB_CONF;
	/**
	 * REST service properties file
	 */
	static const std::string REST_CONF;

	/**
	 * Remove blank spaces at the beginning and end of a string
	 * @param[inout] s	String (to be) trimmed
	 */
	static void trim(std::string &s);

	/**
	 * Extracts the tokens from a string, i.e. the elements separated by
	 * the SEPARATOR
	 * @param[in] s		String with tokens
	 * @return			List of extracted tokens
	 */
	static std::vector<std::string> tokenize(const std::string &s);

	/**
	 * Extract the properties related to the database service
	 */
	static void getDBProperties(std::map<std::string, std::string>& properties);

	/**
	 * Extract the properties related to the rest service
	 */
	static void getRESTProperties(std::map<std::string, std::string>& properties);

	/**
	 * Get the IP for a given host name
	 * @param[in] hostname	Host name
	 * @return				Returns the IP for the given host name
	 */
	static std::string getIpAddress(const std::string hostname);

	/**
	 * Converts an integer string to an integer, or -1 in case it is not convertible
	 * @param[in] s			Integer string
	 * @return				Integer value of the input string, or -1 in case it is
	 *                      not a valid number
	 */
	static int str2int(std::string& s);
};

} /* namespace account */

#endif /* CXX_UTILS_UTILS_H_ */
