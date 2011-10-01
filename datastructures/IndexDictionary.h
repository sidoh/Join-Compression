/*
 * IndexDictionary.h
 *
 *  Created on: Jul 21, 2011
 *      Author: mullins
 */

#ifndef INDEXDICTIONARY_H_
#define INDEXDICTIONARY_H_

#include <vector>
#include <map>
#include <iostream>
#include <google/dense_hash_map>
using namespace std;

using google::dense_hash_map;

/**
 * A vector equality functor
 */
struct vector_equals {
	bool operator()(const vector<unsigned long>* v1, const vector<unsigned long>* v2) const {
		return *v1 == *v2;
	}
};

/**
 * A hash fn for vectors... borrowed from python's tuple hash
 */
struct vector_hash {
	size_t operator()(const vector<unsigned long>* v) const {
		size_t value = 0x34578;

		for (vector<unsigned long>::const_iterator it = v->begin(); it < v->end(); it++) {
			value = (1000003 * value) ^ (*it);
		}
		value ^= v->size();

		return value;
	}
};

class IndexDictionary {
public:
	IndexDictionary(const unsigned long _max_entries);
	virtual ~IndexDictionary() {
		delete entries;
		delete reverse_entries;
	}

	void push(const vector<unsigned long>&);
	const unsigned long lookup(const vector<unsigned long>&);
	const vector<unsigned long>& reverse_lookup(const unsigned long);
	const bool contains(vector<unsigned long>&);

	static vector<IndexDictionary*>* get_array(const int count, const int max_entries);

private:
	const unsigned long max_entries;
	unsigned long next_free_location;

	static vector<unsigned long>* EMPTY_KEY;
	static vector<unsigned long>* DELETED_KEY;

	vector<vector<unsigned long>*> *entries;
	dense_hash_map<const vector<unsigned long>*, unsigned long, vector_hash, vector_equals> *reverse_entries;
};

#endif /* INDEXDICTIONARY_H_ */
