/*
 * EncodedFileHeader.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: mullins
 */

#include "EncodedFileHeader.h"

ostream& operator<<(ostream& stream, const EncodedFileHeader& header) {

	EncodedFileHeader::write_field(stream, header.__unused_field_1);
	EncodedFileHeader::write_field(stream, header.__unused_field_2);
	EncodedFileHeader::write_field(stream, header.max_dictionary_entries);
	EncodedFileHeader::write_field(stream, header.num_columns);
	EncodedFileHeader::write_field(stream, header.num_dictionaries);

	return stream;
}

istream& operator>>(istream& stream, EncodedFileHeader& header) {

	unsigned int fields[5];
	stream.read((char *)fields, sizeof(unsigned int)*5);

	header.__unused_field_1 = fields[0];
	header.__unused_field_2 = fields[1];
	header.max_dictionary_entries = fields[2];
	header.num_columns = fields[3];
	header.num_dictionaries = fields[4];

	return stream;
}

void EncodedFileHeader::write_field(ostream & stream, const unsigned int field) {
	for (int i = ((sizeof(unsigned int)*8) - 8); i >= 0; i -= 8) {
		char byte = ((field >> i) & 0xFF);
		stream.write(&byte, sizeof(char));
	}
}

const unsigned int EncodedFileHeader::read_fields(istream & in) {
	unsigned int val = 0;

	for (int i = ((sizeof(val)*8) - 8); i >= 0; i -= 8) {
		char byte = 0;
		in.read(&byte, sizeof(char));

		val |= (byte << i);
	}

	return val;
}


