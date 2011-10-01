/*
 * Table.h
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <Row.h>

class JoinSettings {
public:
	enum _Type {
		SQLITE3 = 1
	};

	JoinSettings() {};
	virtual ~JoinSettings() {};

	virtual const _Type get_type() const = 0;
};

class Table {
public:
	enum _Type {
		SQLITE3_TABLE = 0,
		JOIN_TABLE = 1,
		LAMBDA = 2
	};

	/**
	 *
	 * Get number of columns in the table
	 *
	 */
	virtual const int num_cols() = 0;

	/**
	 *
	 * Gets a row
	 *
	 */
	virtual Row* next_row() = 0;

	/**
	 *
	 * Rewinds to the beginning
	 *
	 */
	virtual void rewind() = 0;

	/**
	 *
	 *  Gets the type of tree.  Yuck.
	 *
	 */
	virtual const _Type get_type() const = 0;

	/**
	 *
	 * Join two tables
	 *
	 */
	virtual Table* join(Table *other, const JoinSettings& settings) = 0;
};


#endif /* TABLE_H_ */
