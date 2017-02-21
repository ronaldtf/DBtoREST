/**
 * @file RESTHandler.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_REST_RESTHANDLER_H_
#define CXX_REST_RESTHANDLER_H_

#include <memory>
#include <restbed>
#include <vector>

namespace rest {

class RESTHandler {
public:
	enum formatType { JSON, XML};
private:
	static void getResponse(int responseCode, const std::string& body, restbed::Response& response);

	static void databaseHandler(const std::shared_ptr<restbed::Session> session, formatType format = JSON);
	static void tablesHandler(const std::shared_ptr<restbed::Session> session, formatType format = JSON);
	static void singleTableHandler(const std::shared_ptr<restbed::Session> session, formatType format = JSON);

public:
	static void databaseHandlerJson(const std::shared_ptr<restbed::Session> session);
	static void databaseHandlerXml(const std::shared_ptr<restbed::Session> session);

	static void tablesHandlerJson(const std::shared_ptr<restbed::Session> session);
	static void tablesHandlerXml(const std::shared_ptr<restbed::Session> session);

	static void singleTableHandlerJson(const std::shared_ptr<restbed::Session> session);
	static void singleTableHandlerXml(const std::shared_ptr<restbed::Session> session);

	static void errorHandler( const int, const std::exception&, const std::shared_ptr<restbed::Session> session);

	static void swaggerJson(const std::shared_ptr<restbed::Session> session);
};

} /* namespace account */

#endif /* CXX_REST_RESTHANDLER_H_ */
