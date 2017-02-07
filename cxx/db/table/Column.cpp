/**
 * @file Column.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Column.h"

namespace db {
namespace table{

Column::Column() : columnName(""), values(), neighbor(nullptr) {
}

Column::Column(std::string columnName) : columnName(columnName), values(), neighbor(nullptr) {

}

Column::Column(std::string columnName, std::string value) : columnName(columnName), values(), neighbor(nullptr) {
	values.push_back(value);
}

Column::Column(const Column& c) {
	this->columnName = c.columnName;
	std::copy(c.values.begin(), c.values.end(), this->values.begin());
	this->neighbor = c.getNeighbor();
}

Column::~Column() {
	this->values.clear();
}

void Column::addValue(std::string value) {
	values.push_back(value);
}

void Column::getValues(std::vector<std::string>& values) const {
	values = this->values;
}

std::string Column::getColumnName() const {
	return this->columnName;
}

void Column::setNeighbor(std::shared_ptr<Column> column) {
	this->neighbor = column;
}

std::shared_ptr<Column>  Column::getNeighbor() const {
	return this->neighbor;
}


}
}


