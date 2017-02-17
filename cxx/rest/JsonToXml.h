/**
 * @file JsonToXml.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_REST_JSONTOXML_H_
#define CXX_REST_JSONTOXML_H_

#include <string>

namespace rest {

class JsonToXml {
private:
	static std::string convertToOneLine(const std::string& s);
public:
	static std::string json2xml(const std::string& jsonString);
};

} /* namespace rest */

#endif /* CXX_REST_JSONTOXML_H_ */
