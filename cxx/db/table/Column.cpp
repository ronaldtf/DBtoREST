/**
 * @file Column.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Column.h"

namespace db {
namespace table{

Column::Column() : _columnName(""), _values(), _neighbor(nullptr) {
}

Column::Column(std::string columnName) : _columnName(columnName), _values(), _neighbor(nullptr) {

}

Column::Column(std::string columnName, std::string value) : _columnName(columnName), _values(), _neighbor(nullptr) {
	_values.push_back(value);
}

Column::Column(const Column& c) {
	this->_columnName = c._columnName;
	std::copy(c._values.begin(), c._values.end(), this->_values.begin());
	this->_neighbor = c.getNeighbor();
}

Column::~Column() {
	this->_values.clear();
}

void Column::addValue(std::string value) {
	_values.push_back(value);
}

void Column::getValues(std::vector<std::string>& values) const {
	values = this->_values;
}

std::string Column::getColumnName() const {
	return this->_columnName;
}

void Column::setNeighbor(std::shared_ptr<Column> column) {
	this->_neighbor = column;
}

std::shared_ptr<Column>  Column::getNeighbor() const {
	return this->_neighbor;
}


}
}
