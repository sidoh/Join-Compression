/*
 * InnerDictionaryEntry.h
 *
 *  Created on: Jul 19, 2011
 *      Author: mullins
 */

#ifndef INNERDICTIONARYENTRY_H_
#define INNERDICTIONARYENTRY_H_

#include <iostream>
#include <BigInt.h>
using namespace std;

class InnerDictionaryEntry {
public:
	InnerDictionaryEntry(const unsigned long _tree_index)
			: tree_index(_tree_index),
			  left_index(0),
			  right_index(0)
	{ };
	InnerDictionaryEntry(const unsigned long _tree_index, const unsigned long _left, const unsigned long _right)
			: tree_index(_tree_index),
			  left_index(_left),
			  right_index(_right)
	{ };
	virtual ~InnerDictionaryEntry() { };

	InnerDictionaryEntry& set_left_index(const unsigned long value) {
		this->left_index = value;
		return *this;
	}
	InnerDictionaryEntry& set_right_index(const unsigned long value) {
		this->right_index = value;
		return *this;
	}
	InnerDictionaryEntry& set_tree_index(const unsigned long value) {
		this->tree_index = value;
		return *this;
	}

	inline const unsigned long get_left_index() const {
		return left_index;
	}
	inline const unsigned long get_right_index() const {
		return right_index;
	}
	inline const unsigned long get_tree_index() const {
		return tree_index;
	}

	inline static InnerDictionaryEntry read(istream& in) {
		unsigned long tree_index  = BigInt::read(in);
		unsigned long left_index  = BigInt::read(in);
		unsigned long right_index = BigInt::read(in);

		return InnerDictionaryEntry(tree_index,
				left_index,
				right_index);
	}
	inline void write(ostream& out) {
		BigInt::write(tree_index, out);
		BigInt::write(left_index, out);
		BigInt::write(right_index, out);
	}

private:
	unsigned long tree_index;
	unsigned long left_index;
	unsigned long right_index;

};

#endif /* INNERDICTIONARYENTRY_H_ */
