/*
 * IndexDictionary.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: mullins
 */

#include "IndexDictionary.h"
#include <iostream>
using namespace std;

vector<unsigned long>* IndexDictionary::EMPTY_KEY = NULL;
vector<unsigned long>* IndexDictionary::DELETED_KEY = new vector<unsigned long>();

IndexDictionary::IndexDictionary(const unsigned long  _max_entries)
	: max_entries(_max_entries),
	  next_free_location(0)
{
	entries = new vector<vector<unsigned long> *>();
	reverse_entries = new dense_hash_map<
			const vector<unsigned long>*,
			unsigned long,
			vector_hash,
			vector_equals>(max_entries);

	if (IndexDictionary::EMPTY_KEY == NULL) {
		IndexDictionary::EMPTY_KEY = new vector<unsigned long>();
		IndexDictionary::EMPTY_KEY->push_back(-1);
	}

	reverse_entries->set_deleted_key(IndexDictionary::DELETED_KEY);
	reverse_entries->set_empty_key(IndexDictionary::EMPTY_KEY);
};

void IndexDictionary::push(const vector<unsigned long> & allocator) {
	const vector<unsigned long> *key = new vector<unsigned long>(allocator);

	if (entries->size() == max_entries) {
		reverse_entries->erase(entries->at(next_free_location));
		entries->erase(entries->begin() + next_free_location);

		(*entries)[next_free_location] = new vector<unsigned long>(allocator);
	}
	else {
		entries->push_back(new vector<unsigned long>(allocator));
	}

	(*reverse_entries)[key] = next_free_location;
	next_free_location = ((next_free_location + 1) % max_entries);
}

const unsigned long IndexDictionary::lookup(const vector<unsigned long> & allocator) {
	return reverse_entries->find(&allocator)->second;
}

const vector<unsigned long >& IndexDictionary::reverse_lookup(const unsigned long index) {
	return *entries->at(index);
}

const bool IndexDictionary::contains(vector<unsigned long >& key) {
	return (reverse_entries->find(&key) != reverse_entries->end());
}

vector<IndexDictionary*>* IndexDictionary::get_array(const int count, const int max_entries) {
	vector<IndexDictionary*>* dicts = new vector<IndexDictionary*>();

	for (int i = 0; i < count; i++) {
		dicts->push_back(new IndexDictionary(max_entries));
	}

	return dicts;
}






