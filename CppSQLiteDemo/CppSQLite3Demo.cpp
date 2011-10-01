////////////////////////////////////////////////////////////////////////////////
// CppSQLite3 - A C++ wrapper around the SQLite3 embedded database library.
//
// Copyright (c) 2004..2007 Rob Groves. All Rights Reserved. rob.groves@btinternet.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// V3.0		03/08/2004	-Initial Version for sqlite3
//
// V3.1		16/09/2004	-Implemented getXXXXField using sqlite3 functions
//						-Added CppSQLiteDB3::tableExists()
// V3.2		12/07/2007	-Added tests for new functionality
////////////////////////////////////////////////////////////////////////////////
#include <CppSQLite3.h>
#include <SQLite3Table.h>
#include <Table.h>
#include <JoinTable.h>
#include <Row.h>
#include <tpch/TpchHelper.h>
#include <EncodedFileHeader.h>
#include <DictionaryDefinition.h>
#include <InnerDictionaryEntry.h>
#include <LeafDictionaryEntry.h>
#include <ColumnDictionaryEntry.h>
#include <IndexDictionary.h>
#include <StringDictionary.h>
#include <BigInt.h>
#include <Compressor.h>

#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const char* gszFile = "/Users/mullins/Documents/workspace/Join-Compression/data/tpch.db";

int main(int argc, char** argv) {
	CppSQLite3DB db;
	db.open(gszFile);

	/**
	ofstream myfile("data.bin", ios::binary);
	myfile.close();

	ifstream infile("data.bin", ios::binary);
	infile.close();
	**/

	/***
	EncodedFileHeader header(1, 2222222, 3);

	myfile << header;
	myfile.close();
	cout << "all done!" << endl;

	ifstream infile("data.bin", ios::binary);

	infile >> header;
	infile.close();

	cout << "Max dict entries: " << header.get_max_dictionary_entries() << endl;
	cout << "# Columns: " << header.get_num_columns() << endl;
	cout << "# dictionaries: " << header.get_num_dictionaries() << endl;
	***/

	TpchHelper dbhelper(&db);

//	cerr << "Loading tables into memory..." << endl;
//	dbhelper.load_into_memory();
//	cerr << "---> DONE" << endl;

	JoinTable *jt2;
	try {
		jt2 = dbhelper.get_query5_results();
	}
	catch (CppSQLite3Exception& e) {
		cout << "Caught SQL exception: " << e.errorMessage() << endl;
		return 1;
	}

	for(;;) {
		Row *r = jt2->next_row();
		if (! r) break;

		for (int i = 0; i < jt2->num_cols(); i++) {
			cout << r->get_column(i) << ",";
		}
		cout << endl;

		delete r;
	}

//	cout << "Join tree has: " << jt->get_length() << " nodes." << endl;
//	cout << "--> Spans range: " << jt->get_range()->get_left() << " -- "
//		 << jt->get_range()->get_right() << " (" << jt->get_range()->get_count()
//		 << ")" << endl;
//	jt = root->get_left();
//	cout << "--> Spans range: " << jt->get_range()->get_left() << " -- "
//		 << jt->get_range()->get_right() << " (" << jt->get_range()->get_count()
//		 << ")" << endl;
//	jt = root->get_right();
//	cout << "--> Spans range: " << jt->get_range()->get_left() << " -- "
//		 << jt->get_range()->get_right() << " (" << jt->get_range()->get_count()
//		 << ")" << endl;

	ofstream myfile("out.jc", ios::binary);
	jt2->rewind();
	Compressor::compress(jt2, myfile);
	myfile.close();

	/**
	cout << "Num columns: " << joined->num_cols() << endl;
	cout << "First row: ";

	Row *row = result->next_row();
	int j = 0;
	while (true) {
		for (int i = 0; i < joined->num_cols(); i++) {
			cout << row->get_column(i) << ",";
		}

		delete row;
		row = result->next_row();

		cout << endl;
		if (j++ % 1000 == 0)
			cerr << ".";
	}

	cout << endl;

	cout << "Building JoinTree..." << endl;
	JoinTree *jt = result->get_join_tree();

	cout << " Root index: " << jt->get_index() << endl;
	cout << "  Range: " << jt->get_range()->get_left() << " : " << jt->get_range()->get_right() << endl;
	cout << " Left index: " << jt->get_left()->get_index() << endl;
	cout << "  Range: " << jt->get_left()->get_range()->get_left() << " : " << jt->get_left()->get_range()->get_right() << endl;
	cout << " Rght index: " << jt->get_right()->get_index() << endl;
	cout << "  Range: " << jt->get_right()->get_range()->get_left() << " : " << jt->get_right()->get_range()->get_right() << endl;

	delete joined;
	delete row;

	return 0;
	***/
}

