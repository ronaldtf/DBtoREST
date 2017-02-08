/**
 * @file JsonGenerator.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "JsonGenerator.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <iostream>

namespace rest {

void JsonGenerator::getJson(const std::string& root, const std::vector<std::string> elements, std::string& jsonText) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& docAlloc = document.GetAllocator();

	rapidjson::Value list = rapidjson::Value(rapidjson::kArrayType);
	for (std::string element : elements) {
		rapidjson::Value v(element.c_str(), docAlloc);
		list.PushBack(v, docAlloc);
	}

	rapidjson::Value rootJson(root.c_str(), docAlloc);
	document.AddMember(rootJson, list, docAlloc);

	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer = rapidjson::Writer<rapidjson::StringBuffer>(strBuf);
	document.Accept(writer);

	jsonText = strBuf.GetString();
}

void JsonGenerator::getJson(rapidjson::Document::AllocatorType& docAlloc, const std::shared_ptr<db::table::Column> table, std::vector<rapidjson::Value>& jsonElements) {
	if (table == nullptr)
		return;
	std::string columnName = table->getColumnName();

	std::vector<std::string> values;
	table->getValues(values);

	size_t numRows = values.size();
	rapidjson::Value key(columnName.c_str(), docAlloc);
	for (size_t pos = 0; pos < numRows; ++pos) {
		rapidjson::Value key(columnName.c_str(), docAlloc);
		rapidjson::Value val(values.at(pos).c_str(), docAlloc);
		jsonElements.at(pos).AddMember(key,val, docAlloc);
	}

	getJson(docAlloc, table->getNeighbor(), jsonElements);
}

void JsonGenerator::getJson(const std::string& root, const std::shared_ptr<db::table::Column> table, std::string& jsonText) {

	if (table == nullptr)
		return;

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& docAlloc = document.GetAllocator();

	rapidjson::Value list = rapidjson::Value(rapidjson::kArrayType);

	std::vector<std::string> column;
	table->getValues(column);
	size_t numRows = column.size();

	std::vector<rapidjson::Value> members = std::vector<rapidjson::Value>(numRows);
	for (rapidjson::Value& v : members) {
		v.SetObject();
	}
	getJson(docAlloc, table, members);

	for (rapidjson::Value& member : members) {
		rapidjson::Value key(root.c_str(), docAlloc);
		list.PushBack(member, docAlloc);
	}

	rapidjson::Value rootJson(root.c_str(), docAlloc);
	document.AddMember(rootJson, list, docAlloc);

	rapidjson::StringBuffer strBuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer = rapidjson::Writer<rapidjson::StringBuffer>(strBuf);
	document.Accept(writer);

	jsonText = strBuf.GetString();
}

} /* namespace rest */
