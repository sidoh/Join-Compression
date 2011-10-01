/*
 * Compressor.h
 *
 *  Created on: Jul 24, 2011
 *      Author: mullins
 */

#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <iostream>

#include <Table.h>
#include <JoinTable.h>
#include <StringDictionary.h>
#include <IndexDictionary.h>

class Compressor {
public:
	Compressor() { };
	virtual ~Compressor() { };

	Table* decompress(istream& in);
	
	inline static void compress(JoinTable *table, ostream& out) {
		compress(table, out, Compressor::DEFAULT_DICT_ENTRIES);
	}

	static void compress(JoinTable *table, ostream& out, int dict_entries);

private:
	const static unsigned long DEFAULT_DICT_ENTRIES = 10000;

	/*private vector<StringDictionary*>* col_dictionaries;
	private vector<IndexDictionary*>* join_dictionaries;
	JoinTree* join_tree,
	istream& in;*/

	static const unsigned long encode_row(
			Row* row,
			vector<StringDictionary*>* col_dictionaries,
			vector<IndexDictionary*>* join_dictionaries,
			JoinTree* join_tree,
			const int join_tree_len,
			ostream& out);
	static void write_dictionary_definitions(JoinTree *tree, ostream& out);
};

#endif /* COMPRESSOR_H_ */
