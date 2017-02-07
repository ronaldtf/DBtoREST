/**
 * @file JsonGenerator.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_REST_JSONGENERATOR_H_
#define CXX_REST_JSONGENERATOR_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "../db/table/Column.h"

namespace rest {

class JsonGenerator {
private:
	static void getJson(rapidjson::Document::AllocatorType& docAlloc, const std::shared_ptr<db::table::Column> table, std::vector<rapidjson::Value>& jsonElements);
public:
	static void getJson(const std::string& root, const std::vector<std::string> elements, std::string& jsonText);
	static void getJson(const std::string& root, const std::shared_ptr<db::table::Column> table, std::string& jsonText);
};

} /* namespace rest */

#endif /* CXX_REST_JSONGENERATOR_H_ */
