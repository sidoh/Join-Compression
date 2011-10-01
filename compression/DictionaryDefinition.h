/*
 * DictionaryDefinition.h
 *
 *  Created on: Jul 19, 2011
 *      Author: mullins
 */

#ifndef DICTIONARYDEFINITION_H_
#define DICTIONARYDEFINITION_H_

#include <iostream>
using namespace std;

class DictionaryDefinition {
public:
	enum _Type {
		TYPE_LEAF = 0,
		TYPE_INNER = 1
	};

	DictionaryDefinition(const _Type _type,
			const unsigned long _index,
			const unsigned long _field1,
			const unsigned long _field2)
		: type(_type),
		  index(_index),
		  field1(_field1),
		  field2(_field2)
	{ };

	virtual ~DictionaryDefinition() { };

	/**
	 *
	 */
	inline const _Type get_type() const {
		return type;
	}

	/**
	 * Get dictionary index
	 */
	inline const unsigned long get_index() const {
		return index;
	}

	/**
	 * Get left child index. Only makes sense if this is an inner node.
	 *
	 */
	inline const unsigned long get_left_index() const {
		return field1;
	}

	/**
	 * Get the right child index.  Only makes sense if this is an
	 * inner node.
	 *
	 */
	inline const unsigned long get_right_index() const {
		return field2;
	}

	/**
	 * Get the column index. Only makes sense if this is a leaf node.
	 *
	 */
	inline const unsigned long get_col_index() const {
		return field1;
	}

	/**
	 * Get the number of columns this dictionary is responsible for.
	 *
	 */
	inline const unsigned long get_num_cols() const {
		return field2;
	}

	void write(ostream& out) const;
	static DictionaryDefinition read(istream& in);
protected:

private:
	const _Type type;
	const unsigned long index;
	const unsigned long field1;
	const unsigned long field2;
};

#endif /* DICTIONARYDEFINITION_H_ */
