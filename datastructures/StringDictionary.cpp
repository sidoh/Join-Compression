/*
 * Dictionary.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: mullins
 */

#include "StringDictionary.h"

void StringDictionary::push(const string& _value) {
	string* value = new string(_value);

	if (entries->size() == max_entries) {
		string *old_value = entries->at(next_free_location);

		reverse_entries->erase(old_value);
		(*entries)[next_free_location] = value;

		delete old_value;
	}
	else {
		entries->push_back(value);
	}

	(*reverse_entries)[value] = next_free_location;
	next_free_location = ((next_free_location + 1) % max_entries);
}

const string& StringDictionary::reverse_lookup(const unsigned int index) const {
	return *(entries->at(index));
}

const unsigned int StringDictionary::lookup(const string& _value) const {
	if (! contains(_value)) {
		return -1;
	}

	return (*reverse_entries)[&_value];
}

const bool StringDictionary::contains(const string & value) const {
	return (reverse_entries->find(&value) != reverse_entries->end());
}

vector<StringDictionary*>* StringDictionary::get_array(const int count, const int max_entries) {
	vector<StringDictionary*> *dict_collection = new vector<StringDictionary*>();

	for (int i = 0; i < count; i++) {
		dict_collection->push_back(new StringDictionary(max_entries));
	}

	return dict_collection;
}
