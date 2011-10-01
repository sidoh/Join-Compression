/*
 * ColumnDictionaryEntry.h
 *
 *  Created on: Jul 21, 2011
 *      Author: mullins
 */

#ifndef COLUMNDICTIONARYENTRY_H_
#define COLUMNDICTIONARYENTRY_H_

#include <string>
#include <iostream>
using namespace std;

class ColumnDictionaryEntry {
public:
	ColumnDictionaryEntry(const string& _value)
		: value(_value)
	{ };

	virtual ~ColumnDictionaryEntry() { };

	inline const string& get_value() const {
		return value;
	}

	inline void write(ostream& out) const {
		char null_byte = '\0';

		out.write(value.c_str(), sizeof(char)*value.length());
		out.write(&null_byte, sizeof(char));
	}
	static ColumnDictionaryEntry* read(istream& in);

private:
	string value;
};

#endif /* COLUMNDICTIONARYENTRY_H_ */
