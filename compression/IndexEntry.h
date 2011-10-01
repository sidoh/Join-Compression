/*
 * IndexEntry.h
 *
 *  Created on: Jul 19, 2011
 *      Author: mullins
 */

#ifndef INDEXENTRY_H_
#define INDEXENTRY_H_

#include <iostream>
#include <BigInt.h>
using namespace std;

class IndexEntry {
public:
	inline static const unsigned long read(istream& in) {
		return BigInt::read(in);
	}

	inline static void write(const unsigned long value, ostream& out) {
		BigInt::write(value, out);
	}
private:
	IndexEntry() { };
	virtual ~IndexEntry() { };
};

#endif /* INDEXENTRY_H_ */
