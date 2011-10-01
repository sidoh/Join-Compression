/*
 * LeafDictionaryEntry.h
 *
 *  Created on: Jul 19, 2011
 *      Author: mullins
 */

#ifndef LEAFDICTIONARYENTRY_H_
#define LEAFDICTIONARYENTRY_H_

#include <vector>
#include <iostream>
#include <BigInt.h>
using namespace std;

class LeafDictionaryEntry {
public:
	LeafDictionaryEntry()
		: col_indexes(new vector<unsigned long>())
	{ };
	LeafDictionaryEntry(const vector<unsigned long>& _values)
		: col_indexes(new vector<unsigned long>(_values))
	{ };

	virtual ~LeafDictionaryEntry() {
		delete col_indexes;
	}

	LeafDictionaryEntry& add_to_col_indexes(const unsigned long value) {
		col_indexes->push_back(value);
		return *this;
	}
	const vector<unsigned long> *get_col_indexes() const {
		return col_indexes;
	}
	const int get_num_col_indexes() const {
		return col_indexes->size();
	}

	inline const void write(ostream& out) const {
		for (vector<unsigned long>::iterator itr = col_indexes->begin();
				itr != col_indexes->end(); itr++) {
			BigInt::write(*itr, out);
		}
	}
	inline static LeafDictionaryEntry read(istream& in, const int num_entries) {
		LeafDictionaryEntry entry;

		for (int i = 0; i < num_entries; i++) {
			entry.add_to_col_indexes(BigInt::read(in));
		}

		return entry;
	}

private:
	vector<unsigned long> *col_indexes;
};

#endif /* LEAFDICTIONARYENTRY_H_ */
