/**
 * @file DBExecutor.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_DBEXECUTOR_H_
#define CXX_DB_DBEXECUTOR_H_
#include <memory>
#include <vector>

#include "../table/Column.h"

namespace db {

class DBExecutor {
private:
	DBExecutor();
public:
	static void getDBs(std::vector<std::string>& databases);
	static void getTables(const std::string& db, std::vector<std::string>& tables);
	static void getTableInfo(const std::string& db, const std::string& tableName, std::shared_ptr<db::table::Column>& table);
};

} /* namespace account */

#endif /* CXX_DB_DBEXECUTOR_H_ */
