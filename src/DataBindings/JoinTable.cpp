/*
 * JoinTable.cpp
 *
 *  Created on: Jul 11, 2011
 *      Author: mullins
 */

#include "JoinTable.h"

JoinTree *JoinTree::build(Table *table, const int index) {
	JoinTree *tree = internal_build(table, index);
	tree->update_ranges(0);

	return tree;
}

JoinTree *JoinTree::internal_build(Table *table, const int index) {
	// Base case: this isn't a join table
	if (table->get_type() != Table::JOIN_TABLE) {
		JoinTree* leaf = new JoinTree(index, table, 0, 0);
		leaf->length = 1;

		return leaf;
	}
	// Otherwise, recursively build left and right children.
	else {
		JoinTable *join_table = dynamic_cast<JoinTable*>(table);

		JoinTree *left  = internal_build(join_table->get_left(), index+1);
		JoinTree *right = internal_build(join_table->get_right(), left->get_index()+1);

		JoinTree *node = new JoinTree(index, table, left, right);
		node->length = (1 + left->get_length() + right->get_length());

		return node;
	}
}

void JoinTree::update_ranges(int offset) {
	range = new Range(offset, offset+(table->num_cols() - 1));

	if (left != NULL) {
		left->update_ranges(offset);
		right->update_ranges(left->get_range()->get_right() + 1);
	}
}
