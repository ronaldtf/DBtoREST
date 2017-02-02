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

template<class T>
class Column {
private:
	std::string columnName;
	std::vector<T> values;
	std::vector<std::shared_ptr<Column> > neighbors;

public:
	Column(std::string columnName);

	Column(std::string columnName, T value);

	Column(const Column& c);

	virtual ~Column();

	void addValue(T value);

	void getValues(std::vector<T>& values);

	std::string getColumnName();

	void addNeighbor(Column& column);
};

}
} /* namespace db::table */

#endif /* CXX_DB_TABLE_COLUMN_H_ */
