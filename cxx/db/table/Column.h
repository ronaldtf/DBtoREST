/**
 * @file Column.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef CXX_DB_TABLE_COLUMN_H_
#define CXX_DB_TABLE_COLUMN_H_

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace db {
namespace table {

class Column {
private:
	std::string columnName;
	std::vector<std::string> values;
	std::shared_ptr<Column> neighbor;

public:
	Column();

	Column(std::string columnName);

	Column(std::string columnName, std::string value);

	Column(const Column& c);

	virtual ~Column();

	void addValue(std::string value);

	void getValues(std::vector<std::string>& values) const;

	std::string getColumnName() const;

	void setNeighbor(std::shared_ptr<Column> column);

	std::shared_ptr<Column> getNeighbor() const;
};

}
} /* namespace db::table */

#endif /* CXX_DB_TABLE_COLUMN_H_ */
