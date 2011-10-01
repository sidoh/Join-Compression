/*
 * DictionaryDefinition.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: mullins
 */

#include "DictionaryDefinition.h"
#include <BigInt.h>

void DictionaryDefinition::write(ostream& out) const {
	BigInt::write(type, out);
	BigInt::write(index, out);
	BigInt::write(field1, out);
	BigInt::write(field2, out);
}

DictionaryDefinition DictionaryDefinition::read(istream& in) {

	const DictionaryDefinition::_Type type
		= static_cast<DictionaryDefinition::_Type>(BigInt::read(in));
	const unsigned long dict_index = BigInt::read(in);
	const unsigned long field1     = BigInt::read(in);
	const unsigned long field2     = BigInt::read(in);

	return DictionaryDefinition(
			type,
			dict_index,
			field1,
			field2);
}
