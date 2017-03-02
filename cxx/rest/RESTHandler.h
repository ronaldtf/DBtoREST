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

/**
 * This class define the handler for the JSON requests
 */
class RESTHandler {
public:
	/**
	 * Output format types
	 */
	enum formatType { JSON, XML};
private:
	/**
	 * Return the response after setting certain headers and body
	 * @param[in] responseCode	Response code
	 * @param[in] body			Body content of the response
	 * @param[out] response		Response
	 */
	static void getResponse(const int responseCode, const std::string& body, restbed::Response& response);

	/**
	 * Define the handler when looking for the databases in the database manager
	 * @param[in] session		Session
	 * @paramp[in] formatType	Output format type
	 */
	static void databaseHandler(const std::shared_ptr<restbed::Session> session, const formatType format = JSON);

	/**
	 * Define the handler when looking for the tables in a database
	 * @param[in] session		Session
	 * @paramp[in] formatType	Output format type
	 */
	static void tablesHandler(const std::shared_ptr<restbed::Session> session, const formatType format = JSON);

	/**
	 * Define the handler when looking for a table content
	 * @param[in] session		Session
	 * @paramp[in] formatType	Output format type
	 */
	static void singleTableHandler(const std::shared_ptr<restbed::Session> session, const formatType format = JSON);

public:
	/**
	 * Define the handler when looking for the databases in the database manager in the JSON format
	 * @param[in] session	Session
	 */
	static void databaseHandlerJson(const std::shared_ptr<restbed::Session> session);
	/**
	 * Define the handler when looking for the databases in the database manager in the XML format
	 * @param[in] session	Session
	 */
	static void databaseHandlerXml(const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the handler when looking for the tables in a database in the JSON format
	 * @param[in] session	Session
	 */
	static void tablesHandlerJson(const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the handler when looking for the tables in a database in the XML format
	 * @param[in] session	Session
	 */
	static void tablesHandlerXml(const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the handler when looking for a table content in the JSON format
	 * @param[in] session	Session
	 */
	static void singleTableHandlerJson(const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the handler when looking for a table content in the XML format
	 * @param[in] session	Session
	 */
	static void singleTableHandlerXml(const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the error handler
	 * @param[in] code		Error code
	 * @param[in] exc		Exception thrown
	 * @param[in] session	Session
	 */
	static void errorHandler( const int code, const std::exception& exc, const std::shared_ptr<restbed::Session> session);

	/**
	 * Define the info handler
	 * @param[in] session	Session
	 */
	static void infoHandler(const std::shared_ptr<restbed::Session> session);

	/**
	 * Publish the swagger settings file
	 * @param[in] session	Session
	 */
	static void swaggerJson(const std::shared_ptr<restbed::Session> session);
};

} /* namespace account */

#endif /* CXX_REST_RESTHANDLER_H_ */
