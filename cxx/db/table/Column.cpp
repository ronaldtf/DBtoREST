/**
 * @file Column.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Column.h"

namespace db {
namespace table{

template<typename T>
Column<T>::Column(std::string columnName) : columnName(columnName), values(), neighbors() {

}

template<typename T>
Column<T>::Column(std::string columnName, T value) : columnName(columnName), values(), neighbors() {
	values.push_back(value);
}

template<typename T>
Column<T>::Column(const Column& c) {
	this->columnName = c.columnName;
	std::copy(c.values.values.begin(), c.values.end(), this->values.begin());
	for (std::shared_ptr<Column> column : c.neighbors) {
		this->neighbors.push_back(std::shared_ptr<Column>(new Column(*column)));
	}
}

template<typename T>
Column<T>::~Column() {
	this->values.clear();
	this->neighbors.clear();
}

template<typename T>
void Column<T>::addValue(T value) {
	values.push_back(value);
}

template<typename T>
void Column<T>::getValues(std::vector<T>& values) {
	values = this->values;
}

template<typename T>
std::string Column<T>::getColumnName() {
	return this->columnName;
}

template<typename T>
void Column<T>::addNeighbor(Column& column) {
	this->neighbors.push_back(column);

}
}
}


