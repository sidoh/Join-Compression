/*
 * BigInt.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: mullins
 */

#include "BigInt.h"

void BigInt::write(const unsigned long value, ostream& stream) {
	unsigned long buffer = value;

	for (;;) {
		unsigned char byte = (buffer & 0x7F);
		buffer >>= 7;

		if (buffer > 0) {
			byte |= 0x80;
			stream.write((char *)&byte, sizeof(unsigned char));
		}
		else {
			stream.write((char *)&byte, sizeof(unsigned char));
			break;
		}
	}
}

const unsigned long BigInt::read(istream& stream) {
	unsigned long value = 0;
	unsigned int shift = 0;

	for (;;) {
		unsigned char buffer;
		stream.read((char *)&buffer, sizeof(unsigned char));

		value |= (static_cast<long>(buffer & 0x7F) << shift);
		shift += 7;

		if ((buffer & 0x80) != 0x80) {
			break;
		}
	}

	return value;
}


