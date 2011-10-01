/*
 * TpchHelper.h
 *
 *  Created on: Jul 12, 2011
 *      Author: mullins
 */

#ifndef TPCHHELPER_H_
#define TPCHHELPER_H_

#include <Table.h>
#include <SQLite3Table.h>
#include <string>

using namespace std;

class TpchHelper {
public:
	class TableNames {
	public:
		static const string NATIONS;
		static const string REGIONS;
		static const string SUPPLIER;
		static const string CUSTOMER;
		static const string ORDERS;
		static const string PART;
		static const string PARTSUPP;
		static const string LINEITEM;
	};

	TpchHelper(CppSQLite3DB *_db)
		: db(_db),
		  in_memory_loaded(false)
	{};
	virtual ~TpchHelper() { };

	void load_into_memory();

	SQLite3Table *get_table(const string& name);
	SQLite3Table *get_nations_table();
	SQLite3Table *get_regions_table();
	SQLite3Table *get_supplier_table();
	SQLite3Table *get_customer_table();
	SQLite3Table *get_orders_table();
	SQLite3Table *get_part_table();
	SQLite3Table *get_partsupp_table();
	SQLite3Table *get_lineitem_table();

	JoinTable *get_query1_results();
	JoinTable *get_query2_results();
	JoinTable *get_query3_results();
	JoinTable *get_query4_results();
	JoinTable *get_query5_results();
	JoinTable *get_query6_results();
	JoinTable *get_query7_results();

private:
	CppSQLite3DB *db;

	bool in_memory_loaded;
};

#endif /* TPCHHELPER_H_ */
