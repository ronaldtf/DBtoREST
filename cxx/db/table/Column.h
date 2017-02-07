/**
 * @file Column.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_TABLE_COLUMN_H_
#define CXX_DB_TABLE_COLUMN_H_

#include <algorithm>
#include <string>
#include <vector>

namespace db {
namespace table {

class Column {
private:
	std::string columnName;
	std::vector<std::string> values;
	std::vector<std::shared_ptr<Column>> neighbors;

public:
	Column();

	Column(std::string columnName);

	Column(std::string columnName, std::string value);

	Column(const Column& c);

	virtual ~Column();

	void addValue(std::string value);

	void getValues(std::vector<std::string>& values) const;

	std::string getColumnName() const;

	void addNeighbor(std::shared_ptr<Column> column);

	void getNeighbors(std::vector<std::shared_ptr<Column>>& n) const;
};

}
} /* namespace db::table */

#endif /* CXX_DB_TABLE_COLUMN_H_ */
