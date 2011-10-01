/*
 * CompressedRowIterator.h
 *
 *  Created on: Jul 26, 2011
 *      Author: mullins
 */

#ifndef COMPRESSEDROWITERATOR_H_
#define COMPRESSEDROWITERATOR_H_

#include <string>
#include <iostream>

#include <Table.h>

class CompressedRowIterator : public Table {
public:
	CompressedRowIterator(const int __num_cols, iostream& _in)
		: _num_cols(__num_cols),
		  in(_in)
	{ };
	virtual ~CompressedRowIterator()
	{ };

	virtual inline const int num_cols() {
		return _num_cols;
	}
	virtual inline Table* join(Table* other, const JoinSettings& settings) {
		throw new string("Cannot join a LAMBDA table.");
	}
	virtual inline const Table::_Type get_type() const {
		return Table::LAMBDA;
	}

	virtual Row* next_row();
	virtual void rewind();

private:
	 const int _num_cols;
	 istream& in;
};

#endif /* COMPRESSEDROWITERATOR_H_ */
