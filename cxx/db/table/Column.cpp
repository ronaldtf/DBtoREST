/**
 * @file Column.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Column.h"

namespace db {
namespace table{

Column::Column() : columnName(""), values(), neighbors() {
}

Column::Column(std::string columnName) : columnName(columnName), values(), neighbors() {

}

Column::Column(std::string columnName, std::string value) : columnName(columnName), values(), neighbors() {
	values.push_back(value);
}

Column::Column(const Column& c) {
	this->columnName = c.columnName;
	std::copy(c.values.begin(), c.values.end(), this->values.begin());
	for (std::shared_ptr<Column> column : c.neighbors) {
		this->neighbors.push_back(std::shared_ptr<Column>(new Column(*column)));
	}
}

Column::~Column() {
	this->values.clear();
	this->neighbors.clear();
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

void Column::addNeighbor(std::shared_ptr<Column> column) {
	this->neighbors.push_back(column);
}

void Column::getNeighbors(std::vector<std::shared_ptr<Column>>& n) const {
	n = this->neighbors;
}


}
}


