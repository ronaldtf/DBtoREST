/**
 * @file JsonToXml.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "JsonToXml.h"
#include <iostream>

namespace rest {

std::string convertToOneLine(const std::string& s) {
	std::string newStr;
	bool blank = false;
	bool backslash = false;
	size_t pos = 0;
	for (char c : s) {
		if (c == '\n' || c == '\t' || c == '\f' || c == '\r') {
			if (pos == 0)
				continue;
			if (!blank) {
				newStr += ' ';
			}
			blank = true;
			backslash = false;
		} else if (c == '\\') {
			if (backslash) {
				newStr += '\\';
				blank = false;
			}
			backslash = true;
		} else {
			if (backslash) {
				if (c == 'n' || c == 't' || c == 'f' || c == 'r' || c == '0') {
					if (!blank) {
						blank = true;
						newStr += ' ';
					}
				} else {
					newStr += c;
				}
				backslash = false;
			} else {
				backslash = false;
				blank = false;
				newStr += c;
			}
		}
		++pos;
	}
	if (backslash)
		newStr += '\\';
	newStr = newStr.substr(newStr.find_first_not_of(' '), newStr.size());
	newStr = newStr.substr(0, newStr.find_last_not_of(' ') + 1);
	return newStr;
}

size_t searchTag(const std::string& json, const size_t start, const size_t end, std::string& tag) {
	if (start >= json.size() || end >= json.size())
		throw std::exception();
	size_t startTagPos = json.find_first_not_of(' ', start);
	if (startTagPos == std::string::npos)
		throw std::exception();
	size_t endTagPos = json.find_first_of("\"", startTagPos + 1);
	if (endTagPos == std::string::npos)
		throw std::exception();
	tag = json.substr(startTagPos+1, endTagPos-startTagPos-1);
	return endTagPos;
}

std::string parseJson(const std::string& jsonString, size_t start, size_t end, int level = 0) {
	if (start >= end)
		return "";
	if (start == 0 && jsonString.at(start) != '{' && jsonString.at(end-1) != '}')
		throw std::exception();
	size_t tmpStart = start;
	size_t tmpEnd = end;
	if (jsonString.at(start) == '{' ) {
		size_t p = jsonString.find_last_not_of(' ',end-1);
		if (jsonString.at(p) != '}') {
			throw std::exception();
		}
		++tmpStart;
		tmpEnd = p-1;
	}

	std::string tag;
	size_t endTagPos = searchTag(jsonString, tmpStart, tmpEnd, tag);

	size_t aux1 = jsonString.find_first_not_of(' ', endTagPos+1);
	size_t aux2 = jsonString.find_first_of(':', endTagPos+1);
	if (aux1 != aux2) {
		throw std::exception();
	}
	size_t next = jsonString.find_first_not_of(' ', aux1+1);
	if (jsonString.at(next) == '{') {
		size_t nextBracket = jsonString.find_first_of('}',next);
		if (nextBracket == std::string::npos)
			throw std::exception();
		std::string a = parseJson(jsonString, next, nextBracket+1, level+1) ;
		std::string b;// = parseJson(jsonString, nextBracket+2, jsonString.find_first_of('}', nextBracket+1), level+1) ;
		return std::string(level, '\t') + "<" + tag + ">\n" + a + b + std::string(level, '\t') + "</" + tag + ">" + "\n";
	} else {
		std::string value;
		endTagPos = searchTag(jsonString, next, tmpEnd, value);
		size_t nextPos = jsonString.find_first_not_of(' ', endTagPos);
		if (jsonString.at(nextPos+1) == ',')
			++nextPos;
		return std::string(level, '\t') + "<" + tag + ">" + value + "</" + tag + ">\n" + parseJson(jsonString, nextPos+1, tmpEnd, level);
	}
}

}


int main() {
	std::string a = "{\"glossary\": {\"title\": \"example glossary\",\"GlossDiv\": {\"title\": \"S\",\"GlossList\": {\"GlossEntry\": {\"ID\": \"SGML\",\"SortAs\": \"SGML\",\"GlossTerm\": \"Standard Generalized Markup Language\",\"Acronym\": \"SGML\",\"Abbrev\": \"ISO 8879:1986\",\"GlossDef\": {\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\"},\"GlossSee\": \"markup\"}}}}}";
	std::cout << rest::parseJson(a, 0, a.size());
	return 0;

} /* namespace rest */
