/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>

#include "../db/DBConnectionPool.h"
#include "../db/DBConnector.h"

using namespace std;

int main(void) {
	try {
		std::vector<std::string> v;
		std::shared_ptr<db::ConnectionPool> cp = db::ConnectionPool::getInstance();
		db::DBConnector::getDBs(cp->popConnection().get(), v);
		for (std::string s : v)
			std::cout << s << std::endl;
	} catch (sql::SQLException &e) {
		std::cerr << "ERROR: A problem has occurred: " << e.what() <<
				     "(mysql error code: " << e.getErrorCode() << ")" << std::endl;
	}
	return 0;
}
