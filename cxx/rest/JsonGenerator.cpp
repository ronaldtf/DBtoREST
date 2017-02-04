/**
 * @file JsonGenerator.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "JsonGenerator.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

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

} /* namespace rest */
