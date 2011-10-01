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

char *get_raw_filename(char *buffer, char *dir, int query) {
	sprintf(buffer, "%s/%d-raw", dir, query);
	return buffer;
}

char *get_jc_filename(char *buffer, char *dir, int query) {
	sprintf(buffer, "%s/%d-jc", dir, query);
	return buffer;
}

JoinTable *get_query_results(TpchHelper &db_helper, int query_id) {
	if (query_id == 1) {
		return db_helper.get_query1_results();
	}
	else if (query_id == 2) {
		return db_helper.get_query2_results();
	}
	else if (query_id == 3) {
		return db_helper.get_query3_results();
	}
	else if (query_id == 4) {
		return db_helper.get_query4_results();
	}
	else if (query_id == 5) {
		return db_helper.get_query5_results();
	}
	else if (query_id == 6) {
		return db_helper.get_query6_results();
	}
	else if (query_id == 7) {
		return db_helper.get_query7_results();
	}
	else {
		throw new string("Unknown query ID");
	}
}

int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "Syntax is: ./Join-Compression <db_file> <num_dict_entries> <results_dir>" << endl;
		exit(1);
	}

	char *db_file = argv[1];
	int num_dict_entries = atoi(argv[2]);
	char *results_dir = argv[3];
	char s_buffer[4096];

	CppSQLite3DB db;
	db.open(db_file);
	TpchHelper dbhelper(&db);
	
	for (int query_id = 1; query_id <= 7; query_id++) {
		cout << "Processing query " << query_id << "..." << endl;
		ofstream raw_out(get_raw_filename(s_buffer, results_dir, query_id));

		JoinTable *query_results;
		try {
			query_results = get_query_results(dbhelper, query_id);
		}
		catch (CppSQLite3Exception& e) {
			cout << "Caught SQL exception: " << e.errorMessage() << endl;
			return 1;
		}

		cout << "---> Writing raw results..." << endl;
		int num_rows = 0;
		int num_cols = query_results->num_cols();
		for (;; num_rows++) {
			Row *r = query_results->next_row();
			if (! r) break;

			for (int i = 0; i < num_cols; i++) {
				raw_out << r->get_column(i);
				if (i < (num_cols - 1)) {
					raw_out << ",";
				}
			}
			raw_out << endl;

			delete r;
		}
		raw_out.close();
		cout << " DONE! Wrote " << num_rows << " rows." << endl;

		cout << "---> Writing compressed results... " << endl;

		query_results->rewind();
		ofstream comp_out(get_jc_filename(s_buffer, results_dir, query_id), ios::binary);
		Compressor::compress(query_results, comp_out);
		cout << " DONE!" << endl;
	}
}
