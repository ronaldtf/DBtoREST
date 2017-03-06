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

/**
 * This class defines a column in a table and the link to the next column.
 * This way, a full table is defined through a set of columns and links.
 * This structure is dynamic and, therefore, it can be used for any table with
 * any number of columns.
 */
class Column {
private:
	/**
	 * Name of the column
	 */
	std::string _columnName;
	/**
	 * Values saved in the column
	 */
	std::vector<std::string> _values;
	/**
	 * Link to the next column in the table
	 */
	std::shared_ptr<Column> _neighbor;

public:
	/**
	 * Class constructor
	 */
	Column();

	/**
	 * Class constructor.
	 * @param[in] columnName	Name of the column in the table from the database
	 */
	Column(std::string columnName);

	/**
	 * Class constructor
	 * @param[in] columnName	Name of the column in the table from the database
	 * @param[in] value			A single value in the column
	 */
	Column(std::string columnName, std::string value);

	/**
	 * Copy constructor
	 * @param[in] c				Column to be copied
	 */
	Column(const Column& c);

	/**
	 * Class destructor
	 */
	virtual ~Column();

	/**
	 * Add a value to the column
	 * @param[in] value			Value to be added
	 */
	void addValue(std::string value);

	/**
	 * Get column values
	 * @param[out] values		Values stored in the table
	 */
	void getValues(std::vector<std::string>& values) const;

	/**
	 * Get the name of the column
	 * @return 					Name of the column
	 */
	std::string getColumnName() const;

	void setNeighbor(std::shared_ptr<Column> column);

	/**
	 * Get the link to the next column in the table
	 * @return					Neighbor column to the given one
	 */
	std::shared_ptr<Column> getNeighbor() const;
};

}
} /* namespace db::table */

#endif /* CXX_DB_TABLE_COLUMN_H_ */
