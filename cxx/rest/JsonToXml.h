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
	static size_t searchTag(const std::string& json, const size_t start, const size_t end, std::string& tag);
	static std::string getSubTags(std::string rootTag, std::string tagList);
	static std::string parseJson(const std::string& jsonString, size_t start, size_t end, int level = 0);
public:
	static std::string json2xml(const std::string& jsonString);
};

} /* namespace rest */

#endif /* CXX_REST_JSONTOXML_H_ */
