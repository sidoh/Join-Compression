/*
 * ColumnDictionaryEntry.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: mullins
 */

#include "ColumnDictionaryEntry.h"


ColumnDictionaryEntry *ColumnDictionaryEntry::read(istream & in) {
	// TODO: better way to do this...
	string value;
	char buffer;
	in.read(&buffer, sizeof(char));

	while (buffer != '\0') {
		value.append(sizeof(char), buffer);
		in.read(&buffer, sizeof(char));
	}

	return new ColumnDictionaryEntry(value);
}

