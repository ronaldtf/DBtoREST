/**
 * @file JsonToXml.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "JsonToXml.h"

namespace rest {

std::string JsonToXml::convertToOneLine(const std::string& s) {
    std::string newStr;
    bool blank = false;
    bool backslash = false;
    size_t pos = 0;
    for (char c : s) {
        if (c == '\n' || c == '\t' || c == '\f' || c == '\r' || c== ' ') {
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

size_t JsonToXml::searchTag(const std::string& json, const size_t start, const size_t end, std::string& tag) {
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

std::string JsonToXml::getSubTags(const std::string rootTag, const std::string tagList, const int level) {
    size_t start = 0;
    // utils::Utils::trim(tagList)
    std::string out = "";
    size_t endPos = 0;
    while ((endPos = tagList.find_first_of(',', start)) != std::string::npos) {
        out += std::string(level, '\t') + "<" + rootTag + ">" + tagList.substr(start+1,endPos-start-2) + "</" + rootTag + ">" + "\n";
        start=endPos+1;
    }
    if (start < tagList.size())
        out += std::string(level, '\t') + "<" + rootTag + ">" + tagList.substr(start+1,tagList.size()-start-2) + "</" + rootTag + ">" + "\n";
    return out;
}

std::string JsonToXml::json2xml(const std::string& jsonString, const std::string rootTag) {
	std::string copy = convertToOneLine(jsonString);
	std::string header = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n";
	return header + "<" + rootTag + ">\n" + parseJson(copy, 0, copy.size(), 1) + "</" + rootTag + ">\n";
}

std::string JsonToXml::parseJson(const std::string& jsonString, size_t start, size_t end, int level) {
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

    	size_t notEmpty = jsonString.find_first_not_of(' ', next+1);
    	size_t nextBracket = jsonString.find_first_of('}', next+1);
    	if (notEmpty == nextBracket) {
            size_t endNoComma = jsonString.find_first_not_of(' ',nextBracket+1);
            if (endNoComma != std::string::npos && jsonString.at(endNoComma) == ',')
                ++endNoComma;
            return std::string(level, '\t') + "<"+ tag + ">"+ "</"+ tag + ">\n" + parseJson(jsonString, endNoComma ,tmpEnd, level);
    	}

        nextBracket = jsonString.find_last_not_of(' ',tmpEnd);
        if (jsonString.at(nextBracket) != '}') {
            size_t n = jsonString.find_last_of('}',tmpEnd);
            size_t n2 = jsonString.find_first_not_of(' ',n+1);
            if (n2 == std::string::npos)
                throw std::exception();
            if (jsonString.at(n2) == ',')
                ++n2;
            return std::string(level, '\t') + "<" + tag + ">\n" + parseJson(jsonString, next, n+1, level+1) + std::string(level, '\t') + "</" + tag + ">\n" + parseJson(jsonString, n2, tmpEnd, level);
        } else {
            return std::string(level, '\t') + "<" + tag + ">\n" + parseJson(jsonString, next, nextBracket+1, level+1) + std::string(level, '\t') + "</" + tag + ">" + "\n";
        }
    } else if (jsonString.at(next) == '[') {
        size_t nextBracket = jsonString.find_first_of(']', next);
        if (nextBracket == std::string::npos)
            throw std::exception();
        // Check it is not empty
        size_t notEmpty = jsonString.find_first_not_of(' ', next+1);
        if (notEmpty == nextBracket) {
            size_t endNoComma = jsonString.find_first_not_of(' ',nextBracket+1);
            if (endNoComma != std::string::npos && jsonString.at(endNoComma) == ',')
                ++endNoComma;
            return std::string(level, '\t') + "<"+ tag + ">"+ "</"+ tag + ">\n" + parseJson(jsonString, endNoComma ,tmpEnd, level);
        }
        size_t contPos = jsonString.find_first_not_of(' ', nextBracket+1);
        if (contPos < jsonString.size() && jsonString.at(contPos) == ',')
            ++contPos;

        size_t curlyBracket = jsonString.find_first_of('{', next+1);
        // The list contain entities
        if (curlyBracket == notEmpty) {
        	std::string parsed;
        	while (curlyBracket < nextBracket) {
        		if (jsonString.at(curlyBracket) != '{') {
        			throw std::exception();
        		}
        		size_t endCurlyBracket = jsonString.find_first_of('}', curlyBracket+1);
        		if (endCurlyBracket == std::string::npos) {
        			throw std::exception();
        		}
        		parsed += std::string(level,'\t') + "<" + tag + ">\n" + parseJson(jsonString, curlyBracket, endCurlyBracket+1, level+1) + std::string(level, '\t') + "</" + tag + ">\n";
        		curlyBracket = jsonString.find_first_not_of(' ', endCurlyBracket+1);
        		if (curlyBracket != std::string::npos && jsonString.at(curlyBracket) == ',')
        			curlyBracket = jsonString.find_first_not_of(' ', curlyBracket+1);
        	}
        	return parsed + parseJson(jsonString, nextBracket+1, tmpEnd, level);
        } else {
        	// The list only contain single elements
			std::string subtags = getSubTags(tag, jsonString.substr(next+1, nextBracket-next-1), level);
			return subtags + parseJson(jsonString, contPos, tmpEnd, level);
        }
    } else {
        std::string value;
        endTagPos = searchTag(jsonString, next, tmpEnd, value);
        size_t nextPos = jsonString.find_first_not_of(' ', endTagPos);
        if (jsonString.at(nextPos+1) == ',')
            ++nextPos;
        return std::string(level, '\t') + "<" + tag + ">" + value + "</" + tag + ">\n" + parseJson(jsonString, nextPos+1, tmpEnd, level);
    }
}

} /* namespace rest */
