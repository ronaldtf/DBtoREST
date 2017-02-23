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

/**
 * This class creates a JSON document for a list of values or a table
 */
class JsonGenerator {
private:
	/**
	 * Create a JSON document
	 * @param[in] docAlloc		Document allocator
	 * @param[in] table			Table values
	 * @param[out] jsonElements	JSON document
	 */
	static void getJson(rapidjson::Document::AllocatorType& docAlloc, const std::shared_ptr<db::table::Column> table, std::vector<rapidjson::Value>& jsonElements);
public:
	/**
	 * Create a JSON document given a list of values
	 * @param[in] root			Root tag
	 * @param[in] elements		List of values to generate the JSON document
	 * @param[out] jsonText		JSON document in text format
	 */
	static void getJson(const std::string& root, const std::vector<std::string> elements, std::string& jsonText);

	/**
	 * Create a JSON document given a database table
	 * @param[in] root			Root tag
	 * @param[in] table			Table values
	 * @param[out] jsonText		JSON document in text format
	 */
	static void getJson(const std::string& root, const std::shared_ptr<db::table::Column> table, std::string& jsonText);
};

} /* namespace rest */

#endif /* CXX_REST_JSONGENERATOR_H_ */
