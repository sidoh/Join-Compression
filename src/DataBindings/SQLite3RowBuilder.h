/*
 * SQLite3RowBuilder.h
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#ifndef SQLITE3ROWBUILDER_H_
#define SQLITE3ROWBUILDER_H_

#include <Row.h>
#include <sqlite3.h>
#include <CppSQLite3.h>

class SQLite3RowBuilder {
public:
	SQLite3RowBuilder() {};
	~SQLite3RowBuilder() {};

	Row* build_row(CppSQLite3Query& query);
};

#endif /* SQLITE3ROWBUILDER_H_ */

