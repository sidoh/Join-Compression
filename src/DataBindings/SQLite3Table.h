/*
 * SQLite3Table.h
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#ifndef SQLITE3TABLE_H_
#define SQLITE3TABLE_H_

#include <Table.h>
#include <Row.h>
#include <SQLite3RowBuilder.h>
#include <CppSQLite3.h>
#include <JoinTable.h>

#include <string>

class SQLite3JoinSettings : public JoinSettings {
public:
	SQLite3JoinSettings(const string& _left_join_key, const string& _right_join_key)
		: left_join_key(new string(_left_join_key)),
		  right_join_key(new string(_right_join_key))
	{ };

	virtual ~SQLite3JoinSettings() {
		delete left_join_key;
		delete right_join_key;
	}

	inline const string& get_left_join_key() const {
		return *left_join_key;
	}

	inline const string& get_right_join_key() const {
		return *right_join_key;
	}

	inline const JoinSettings::_Type get_type() const {
		return JoinSettings::SQLITE3;
	}

private:
	const string* left_join_key;
	const string* right_join_key;
};

class SQLite3Table : public Table {
public:
	SQLite3Table(CppSQLite3DB * _db, const string& _query)
		: db(_db)
	{
		query_s = new string(_query);
		this->run_query();
	}

	virtual ~SQLite3Table() {
		delete query_s;
	}

	inline const string& get_query() const {
		return *query_s;
	}

	inline const Table::_Type get_type() const {
		return Table::SQLITE3_TABLE;
	}

	const int num_cols();

	Row* next_row();

	void rewind();

	Table* join(Table *other, const JoinSettings& settings);

private:
	CppSQLite3DB *db;
	CppSQLite3Query query;
	string *query_s;
	SQLite3RowBuilder row_builder;

	static JoinTable* join(SQLite3Table *left,
			SQLite3Table *right,
			const string& join_key_left,
			const string& join_key_right);

	void run_query();
};


#endif /* SQLITE3TABLE_H_ */
