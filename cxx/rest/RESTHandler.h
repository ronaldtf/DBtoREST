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
private:
	static void getDBs(std::vector<std::string>& v);
	static void getTables(const std::string dbName, std::vector<std::string>& tables);
	static void getSingleTable(const std::string dbName, const std::string tableName, std::shared_ptr<db::table::Column>& table);
	static void getResponse(int responseCode, std::string& body, restbed::Response& response);
public:
	static void databaseHandler(const std::shared_ptr<restbed::Session> session);
	static void tablesHandler(const std::shared_ptr<restbed::Session> session);
	static void singleTableHandler(const std::shared_ptr<restbed::Session> session);
	static void errorHandler( const int, const std::exception&, const std::shared_ptr<restbed::Session> session);
	static void swaggerJson(const std::shared_ptr<restbed::Session> session);
};

} /* namespace account */

#endif /* CXX_REST_RESTHANDLER_H_ */
