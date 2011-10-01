/*
 * Compressor.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: mullins
 */

#include "Compressor.h"

#include <EncodedFileHeader.h>
#include <DictionaryDefinition.h>
#include <StringDictionary.h>
#include <IndexDictionary.h>
#include <ColumnDictionaryEntry.h>
#include <IndexEntry.h>
#include <InnerDictionaryEntry.h>
#include <LeafDictionaryEntry.h>

void Compressor::compress(JoinTable *table, ostream & out) {
	JoinTree *tree = table->get_join_tree();

	out << EncodedFileHeader(MAX_ENTRIES, table->num_cols(), tree->get_length());
	write_dictionary_definitions(tree, out);

	// Initialize dictionaries
	vector<StringDictionary*> *column_dicts = StringDictionary::get_array(
			table->num_cols(),
			MAX_ENTRIES);
	vector<IndexDictionary*> *index_dicts = IndexDictionary::get_array(
			tree->get_length(),
			MAX_ENTRIES);

	Row *row;
	int i = 0;
	while ((row = table->next_row()) != NULL) {
		encode_row(row, column_dicts, index_dicts, tree, tree->get_length(), out);

		delete row;

		if ((i % 1000) == 0) {
			cerr << ".";
			fflush(stdout);
		}
		i++;
	}
	cerr << "Done! Compressed " << i << " rows." << endl;

	delete column_dicts;
	delete index_dicts;
}

void Compressor::write_dictionary_definitions(JoinTree *tree, ostream & out) {
	if (tree->get_left() == NULL) {
		DictionaryDefinition(
				DictionaryDefinition::TYPE_LEAF,
				tree->get_index(),
				tree->get_range()->get_left(),
				tree->get_range()->get_count())
			.write(out);
	}
	else {
		write_dictionary_definitions(tree->get_left(), out);
		write_dictionary_definitions(tree->get_right(), out);

		DictionaryDefinition(
				DictionaryDefinition::TYPE_INNER,
				tree->get_index(),
				tree->get_left()->get_index(),
				tree->get_right()->get_index())
			.write(out);
	}
}

const unsigned long Compressor::encode_row(Row *row,
		vector<StringDictionary*> *col_dictionaries,
		vector<IndexDictionary*> *join_dictionaries,
		JoinTree *join_tree,
		const int join_tree_len,
		ostream & out) {

	const Range *rng = join_tree->get_range();

	// Base case: this is a leaf node in the join tree
	if (join_tree->get_left() == NULL) {
		// Build a collection of column indexes.
		vector<unsigned long> col_indexes;

		for (int i = rng->get_left(); i <= rng->get_right(); i++) {
			StringDictionary *dict = col_dictionaries->at(i);
			const string& value    = row->get_column(i);

			if (! dict->contains(value)) {
				IndexEntry::write((i + join_tree_len), out);
				ColumnDictionaryEntry(value)
					.write(out);

				dict->push(value);
			}

			col_indexes.push_back(dict->lookup(value));
		}

		IndexDictionary *dict = join_dictionaries->at(join_tree->get_index());

		if (! dict->contains(col_indexes)) {

			IndexEntry::write(join_tree->get_index(), out);
			LeafDictionaryEntry(col_indexes)
				.write(out);

			dict->push(col_indexes);
		}

		return dict->lookup(col_indexes);
	}
	else {
		// Build a recursive dictionary
		vector<unsigned long> dict_indexes;

		IndexDictionary *dict = join_dictionaries->at(join_tree->get_index());

		dict_indexes.push_back(
			encode_row(row, col_dictionaries, join_dictionaries, join_tree->get_left(), join_tree_len, out));
		dict_indexes.push_back(
			encode_row(row, col_dictionaries, join_dictionaries, join_tree->get_right(), join_tree_len, out));

		// If this is the root, just write and exit.  We do this because we assume that not
		// very many repeated rows will occur, so maintaining a top-level dictionary would
		// be a waste.
		if (join_tree->is_root()) {
			InnerDictionaryEntry(join_tree->get_index(),
					dict_indexes[0],
					dict_indexes[1])
				.write(out);
			return 0;
		}

		// Otherwise, behave normally.
		if (! dict->contains(dict_indexes)) {
			IndexEntry::write(join_tree->get_index(), out);
			InnerDictionaryEntry(join_tree->get_index(),
					dict_indexes[0],
					dict_indexes[1])
				.write(out);
			dict->push(dict_indexes);
		}

		return dict->lookup(dict_indexes);
	}
}




