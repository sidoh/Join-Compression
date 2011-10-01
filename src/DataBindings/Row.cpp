/*
 * Row.cpp
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#include <Row.h>
#include <algorithm>

Row::Row(const std::vector<std::string> &_columns) {
	columns = new vector<std::string>(_columns);
}

Row::~Row() {
	delete columns;
}
