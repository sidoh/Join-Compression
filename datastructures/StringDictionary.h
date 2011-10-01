/*
 * Dictionary.h
 *
 *  Created on: Jul 17, 2011
 *      Author: mullins
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <google/dense_hash_map>

using namespace std;
using google::dense_hash_map;

struct string_equals {
	bool operator()(const string* s1, const string* s2) const {
		return *s1 == *s2;
	}
};

/**
 * DJB2 hash fn
 */
struct string_hash {
	size_t operator()(const string* s) const {
		size_t hash = 5381;
		int c;
		const char* cstr = s->c_str();

		while ((c = *cstr++) != '\0') {
			hash = hash * 31 ^ c;
		}

		return hash;
	}
};

class StringDictionary {
public:
	StringDictionary(const int _max_entries)
		: next_free_location(0),
		  max_entries(_max_entries)
	{

		entries = new vector<const string*>();
		reverse_entries = new dense_hash_map<
			const string*,
			unsigned int,
			string_hash,
			string_equals>(max_entries);

		entries->reserve(max_entries);
		reverse_entries->set_deleted_key(new string("\x3\x2\x1"));
		reverse_entries->set_empty_key(new string("\x1\x2\x3"));
	}
	virtual ~StringDictionary() {
		delete entries;
		delete reverse_entries;
	}

	void push(const string& value);
	const string& reverse_lookup(const unsigned int index) const;
	const unsigned int lookup(const string& value) const;
	const bool contains(const string& value) const;

	static vector<StringDictionary*>* get_array(const int count, const int _max_entries);

private:
	vector<const string*> *entries;
	dense_hash_map<const string*, unsigned int, string_hash, string_equals> *reverse_entries;
	unsigned int next_free_location;
	const unsigned int max_entries;
};

#endif /* DICTIONARY_H_ */
