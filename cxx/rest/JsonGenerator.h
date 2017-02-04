/**
 * @file JsonGenerator.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_REST_JSONGENERATOR_H_
#define CXX_REST_JSONGENERATOR_H_

#include <map>
#include <string>
#include <vector>

namespace rest {

class JsonGenerator {
public:
	static void getJson(const std::string& root, const std::vector<std::string> elements, std::string& jsonText);
};

} /* namespace rest */

#endif /* CXX_REST_JSONGENERATOR_H_ */
