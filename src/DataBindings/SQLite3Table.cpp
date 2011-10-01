/*
 * SQLite3Table.cpp
 *
 *  Created on: Jul 11, 2011
 *      Author: mullins
 */

#include "SQLite3Table.h"
#include <iostream>
#include <sstream>

const int SQLite3Table::num_cols(){
	return query.numFields();
}

Row *SQLite3Table::next_row() {
	if (query.eof()) {
		return NULL;
	}

	// Get row
	Row *result = row_builder.build_row(query);

	// Move to next one
	query.nextRow();

	return result;
}

void SQLite3Table::rewind() {
	query.finalize();
	this->run_query();
}

Table *SQLite3Table::join(Table *other, const JoinSettings& settings) {
	if (settings.get_type() != JoinSettings::SQLITE3) {
		throw new string("JoinSettings needs to be SQLite3JoinSettings");
	}

	const SQLite3JoinSettings& sql_settings = dynamic_cast<const SQLite3JoinSettings& >(settings);
	if (other->get_type() == Table::SQLITE3_TABLE) {
		return join(this, dynamic_cast<SQLite3Table *>(other),
				sql_settings.get_left_join_key(),
				sql_settings.get_right_join_key());
	}
	else if (other->get_type() == Table::JOIN_TABLE) {
		JoinTable *jt = dynamic_cast<JoinTable *>(other);

		return this->join(jt->get_underlying_table(), settings);
	}
	else {
		throw new string("Unknown table type");
	}
}

void SQLite3Table::run_query() {
	query = db->execQuery(query_s->c_str());
}

// static
JoinTable *SQLite3Table::join(SQLite3Table *left, SQLite3Table *right, const string & join_key_left, const string & join_key_right) {
	if (left->db != right->db) {
		throw new string("Can't join tables from different databases.");
	}

	stringstream stream;

	stream << "SELECT * FROM (" << left->get_query() << ") AS tab1, "
		   << "(" << right->get_query() << ") AS tab2 "
		   << "WHERE tab1." << join_key_left << " = "
		   << "tab2." << join_key_right;

	return new JoinTable(
		new SQLite3Table(left->db, stream.str()),
		left,
		right);
}
