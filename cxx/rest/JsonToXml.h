/**
 * @file JsonToXml.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_REST_JSONTOXML_H_
#define CXX_REST_JSONTOXML_H_

#include <string>

namespace rest {

/**
 * This class converts a JSON formatted text to a text with XML format
 */
class JsonToXml {
private:
	/**
	 * Convert a multiple line strings to a single line string. It removes the new lines, tabs, multiple spaces...
	 * @param[in] s		Input string
	 * @return			Converted string
	 */
	static std::string convertToOneLine(const std::string& s);

	/**
	 * Extracts a tag (the next string between "" symbols) in a JSON text.
	 * @param[in] json		JSON text
	 * @param[in] start		Start position where to start searching
	 * @param[in] end		Last position where to end searching
	 * @param[out] tag		Output tag
	 * @return				End position of the tag
	 */
	static size_t searchTag(const std::string& json, const size_t start, const size_t end, std::string& tag);

	/**
	 * Get the xml for a list of tags in a JSON text
	 * @param[in] rootTag	Root tag
	 * @param[in] tagList	List of tags in JSON format
	 * @param[in] level		Tag level
	 * @return				XML converted text
	 */
	static std::string getSubTags(const std::string rootTag, const std::string tagList, const int level);

	/**
	 * Parse a JSON document and convert it to XML
	 * @param[in] jsonString	JSON formatted text
	 * @param[in] start			Start position in the document to convert to XML
	 * @param[in] end			End position in the document to convert to XML
	 * @param[in] level			Tag level
	 * @return					XML converted text
	 */
	static std::string parseJson(const std::string& jsonString, const size_t start, const size_t end, int level = 0);
public:
	/**
	 * Convert a full JSON document to XML
	 * @param[in] jsonString	JSON document
	 * @param[in] rootTag		XML root tag
	 * @return					XML converted document
	 */
	static std::string json2xml(const std::string& jsonString, const std::string rootTag);
};

} /* namespace rest */

#endif /* CXX_REST_JSONTOXML_H_ */
