/*
 * SQLite3RowBuilder.cpp
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#include <SQLite3RowBuilder.h>
#include <Row.h>
#include <string>
#include <vector>

Row * SQLite3RowBuilder::build_row(CppSQLite3Query & query) {
	vector<string> columns;

	for (int i = 0; i < query.numFields(); i++) {
		columns.push_back(string(query.fieldValue(i)));
	}

	return new Row(columns);
}
