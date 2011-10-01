/*
 * EncodedFileHeader.h
 *
 *  Created on: Jul 17, 2011
 *      Author: mullins
 */

#ifndef ENCODEDFILEHEADER_H_
#define ENCODEDFILEHEADER_H_

#include <iostream>
using namespace std;

class EncodedFileHeader {
public:
	EncodedFileHeader(const unsigned int _max_dictioanry_entries,
			const unsigned int _num_columns,
			const unsigned int _num_dictionaries)
		: __unused_field_1(2),
		  __unused_field_2(2),
		  max_dictionary_entries(_max_dictioanry_entries),
		  num_columns(_num_columns),
		  num_dictionaries(_num_dictionaries)
	{ };

	virtual ~EncodedFileHeader() { };

	friend ostream& operator<<(ostream& stream, const EncodedFileHeader& header);
	friend istream& operator>>(istream& stream, EncodedFileHeader& header);

	inline const unsigned int get_max_dictionary_entries() const {
		return max_dictionary_entries;
	}

	inline const unsigned int get_num_columns() const {
		return num_columns;
	}

	inline const unsigned int get_num_dictionaries() const {
		return num_dictionaries;
	}

private:
	unsigned int __unused_field_1;
	unsigned int __unused_field_2;
	unsigned int max_dictionary_entries;
	unsigned int num_columns;
	unsigned int num_dictionaries;

	static void write_field(ostream& stream, const unsigned int field);
	const unsigned int read_fields(istream& in);
};

#endif /* ENCODEDFILEHEADER_H_ */
