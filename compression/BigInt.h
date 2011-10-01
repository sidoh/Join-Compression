/*
 * BigInt.h
 *
 *  Created on: Jul 18, 2011
 *      Author: mullins
 */

#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
using namespace std;

class BigInt {
public:
	BigInt() { };
	virtual ~BigInt() { };

	static void write(const unsigned long value, ostream& stream);
	static const unsigned long read(istream& stream);
};

#endif /* BIGINT_H_ */
