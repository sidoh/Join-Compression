/*
 * JoinTable.h
 *
 *  Created on: Jul 11, 2011
 *      Author: mullins
 */

#ifndef JOINTABLE_H_
#define JOINTABLE_H_

#include <Table.h>

class Range {
public:
	Range(const int _left, const int _right)
		: left(_left),
		  right(_right)
	{};
	virtual ~Range() { };

	inline const int get_left() const { return left; }
	inline const int get_right() const { return right; }
	inline const int get_count() const { return right - left + 1; }

private:
	const int left;
	const int right;
};

class JoinTree {
public:
	JoinTree(const int _index, Table *_table, JoinTree *_left, JoinTree *_right)
		: index(_index),
		  table(_table),
		  left(_left),
		  right(_right)
	{ };

	virtual ~JoinTree() {
		if (left != NULL) {
			delete left;
		}
		if (right != NULL) {
			delete right;
		}
		if (range != NULL) {
			delete range;
		}
	}

	inline const int get_index() const {
		return index;
	}
	inline JoinTree* get_left() {
		return left;
	}
	inline JoinTree* get_right() {
		return right;
	}
	inline const Range* get_range() const {
		return range;
	}
	inline const int get_length() const {
		return length;
	}
	inline const bool is_root() const {
		return get_index() == 0;
	}
	inline JoinTree* set_left(JoinTree* left) {
		this->left = left;
		return this;
	}
	inline JoinTree* set_right(JoinTree* left) {
		this->right = right;
		return this;
	}

	static JoinTree* build(Table *join_table, const int index);

private:
	int index;
	int length;
	Table *table;
	JoinTree *left;
	JoinTree *right;
	Range *range;

	void update_ranges(int offset);

	static JoinTree* internal_build(Table* table, const int index);
};

class JoinTable : public Table {
public:
	JoinTable(Table *_joined,
			  Table *_left,
			  Table *_right)
		: joined(_joined),
		  left(_left),
		  right(_right),
		  join_tree(JoinTree::build(this, 0))
	{ };
	JoinTable(Table *_joined,
			  Table *_left,
			  Table *_right,
			  JoinTree *_join_tree)
		: joined(_joined),
		  left(_left),
		  right(_right),
		  join_tree(_join_tree)
	{ };
	virtual ~JoinTable() {
		delete left;
		delete right;
		delete joined;

		if (join_tree != NULL) {
			delete join_tree;
		}
	};

	virtual inline const int num_cols() {
		return joined->num_cols();
	}

	virtual inline Row* next_row() {
		return joined->next_row();
	}

	inline void rewind() {
		joined->rewind();
	}

	inline Table* get_left() const {
		return left;
	}

	inline Table* get_right() const {
		return right;
	}

	inline Table* get_underlying_table() {
		return joined;
	}

	inline const Table::_Type get_type() const {
		return Table::JOIN_TABLE;
	}

	inline JoinTree *get_join_tree() const {
		return join_tree;
	}

	inline Table* join(Table* other, const JoinSettings& settings) {
		return joined->join(other, settings);
	}

protected:
	Table *joined;
	Table *left;
	Table *right;

	JoinTree *join_tree;
};

#endif /* JOINTABLE_H_ */
