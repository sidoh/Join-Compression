/*
 * TpchHelper.cpp
 *
 *  Created on: Jul 12, 2011
 *      Author: mullins
 */

#include "TpchHelper.h"

#include <sstream>
#include <iostream>

const string TpchHelper::TableNames::NATIONS = "NATION";
const string TpchHelper::TableNames::REGIONS = "REGION";
const string TpchHelper::TableNames::SUPPLIER = "SUPPLIER";
const string TpchHelper::TableNames::CUSTOMER = "CUSTOMER";
const string TpchHelper::TableNames::ORDERS = "ORDERS";
const string TpchHelper::TableNames::PART = "PART";
const string TpchHelper::TableNames::PARTSUPP = "PARTSUPP";
const string TpchHelper::TableNames::LINEITEM = "LINEITEM";

SQLite3Table *TpchHelper::get_table(const string & name) {
	stringstream buffer;
	buffer << "SELECT * FROM ";

	if (in_memory_loaded) {
		buffer << "aux." << name;
	}
	else {
		buffer << name;
	}

	return new SQLite3Table(db, buffer.str());
}

SQLite3Table *TpchHelper::get_nations_table() {
	return get_table(TableNames::NATIONS);
}

SQLite3Table *TpchHelper::get_regions_table() {
	return get_table(TableNames::REGIONS);
}

SQLite3Table *TpchHelper::get_supplier_table() {
	return get_table(TableNames::SUPPLIER);
}

SQLite3Table *TpchHelper::get_customer_table() {
	return get_table(TableNames::CUSTOMER);
}

SQLite3Table *TpchHelper::get_orders_table() {
	return get_table(TableNames::ORDERS);
}

SQLite3Table *TpchHelper::get_part_table() {
	return get_table(TableNames::PART);
}

SQLite3Table *TpchHelper::get_partsupp_table() {
	return get_table(TableNames::PARTSUPP);
}

SQLite3Table *TpchHelper::get_lineitem_table() {
	return get_table(TableNames::LINEITEM);
}

void TpchHelper::load_into_memory() {
	try{
	db->execQuery("ATTACH DATABASE ':memory:' AS aux;");
	db->execQuery("CREATE TABLE aux.nation AS SELECT * FROM NATION;");
	db->execQuery("CREATE TABLE aux.region AS SELECT * FROM REGION;");
	db->execQuery("CREATE TABLE aux.supplier AS SELECT * FROM SUPPLIER;");
	db->execQuery("CREATE TABLE aux.customer AS SELECT * FROM CUSTOMER;");
	db->execQuery("CREATE TABLE aux.orders AS SELECT * FROM ORDERS;");
	db->execQuery("CREATE TABLE aux.lineitem AS SELECT * FROM LINEITEM;");
	db->execQuery("CREATE TABLE aux.partsupp AS SELECT * FROM PARTSUPP;");
	db->execQuery("CREATE TABLE aux.part AS SELECT * FROM PART;");
	db->execQuery("CREATE INDEX aux.customer_custkey ON aux.CUSTOMER (C_CUSTKEY);");
	db->execQuery("CREATE INDEX aux.customer_nationkey ON aux.CUSTOMER (C_NATIONKEY);");
	db->execQuery("CREATE INDEX aux.lineitem_orderkey ON aux.LINEITEM (L_ORDERKEY);");
	db->execQuery("CREATE INDEX aux.lineitem_partkey ON aux.LINEITEM (L_PARTKEY);");
	db->execQuery("CREATE INDEX aux.lineitem_psuppkey ON aux.LINEITEM (L_SUPPKEY);");
	db->execQuery("CREATE INDEX aux.nation_nationkey ON aux.NATION (N_NATIONKEY);");
	db->execQuery("CREATE INDEX aux.nation_regionkey ON aux.NATION (N_REGIONKEY);");
	db->execQuery("CREATE INDEX aux.order_custkey ON aux.ORDERS (O_CUSTKEY);");
	db->execQuery("CREATE INDEX aux.order_orderkey ON aux.ORDERS (O_ORDERKEY);");
	db->execQuery("CREATE INDEX aux.part_partkey ON aux.PART (P_PARTKEY);");
	db->execQuery("CREATE INDEX aux.partsupp_partkey ON aux.PARTSUPP (PS_PARTKEY);");
	db->execQuery("CREATE INDEX aux.partsupp_suppkey ON aux.PARTSUPP (PS_SUPPKEY);");
	db->execQuery("CREATE INDEX aux.region_regionkey ON aux.REGION (R_REGIONKEY);");
	db->execQuery("CREATE INDEX aux.supplier_s_nationkey ON aux.SUPPLIER (S_NATIONKEY);");
	db->execQuery("CREATE INDEX aux.supplier_s_suppkey ON aux.SUPPLIER (S_SUPPKEY);");
	}
	catch (CppSQLite3Exception& e) {
		cout << "caught sqlite3 error: " << e.errorMessage();
	}

	in_memory_loaded = true;
}

JoinTable *TpchHelper::get_query1_results() {
	Table *n1 =
		get_orders_table()->join(
			get_lineitem_table(),
			SQLite3JoinSettings("O_ORDERKEY", "L_ORDERKEY"));
	Table *r =
		get_customer_table()->join(
			n1,
			SQLite3JoinSettings("C_CUSTKEY", "O_CUSTKEY"));

	return dynamic_cast<JoinTable*>(r);
}

JoinTable *TpchHelper::get_query2_results() {
	Table *pkeys =
			get_partsupp_table()->join(
				get_part_table(),
				SQLite3JoinSettings("PS_PARTKEY", "P_PARTKEY"));
	Table *snations =
			get_supplier_table()->join(
				get_nations_table(),
				SQLite3JoinSettings("S_NATIONKEY", "N_NATIONKEY"));

	return dynamic_cast<JoinTable*>(pkeys->join(snations,
			SQLite3JoinSettings("PS_SUPPKEY", "S_SUPPKEY")));
}



JoinTable *TpchHelper::get_query3_results() {
	return dynamic_cast<JoinTable*>(get_supplier_table()->join(
			get_lineitem_table(),
			SQLite3JoinSettings("S_SUPPKEY", "L_SUPPKEY")));
}


JoinTable *TpchHelper::get_query4_results() {
	return dynamic_cast<JoinTable*>(get_customer_table()->join(
			get_orders_table(),
			SQLite3JoinSettings("C_CUSTKEY", "O_CUSTKEY")));
}

JoinTable *TpchHelper::get_query5_results() {
	Table *n1 = get_customer_table()
		->join(
			get_orders_table(),
			SQLite3JoinSettings("C_CUSTKEY", "O_CUSTKEY"));
	Table *n2 =
		n1->join(
			get_lineitem_table(),
			SQLite3JoinSettings("O_ORDERKEY", "L_ORDERKEY"));

	Table *n3 = get_nations_table()
		->join(
			get_regions_table(),
			SQLite3JoinSettings("N_REGIONKEY", "R_REGIONKEY"));
	Table *n4 =
		n3->join(
			get_supplier_table(),
			SQLite3JoinSettings("N_NATIONKEY", "S_NATIONKEY"));

	return dynamic_cast<JoinTable*>(n2->join(n4, SQLite3JoinSettings("L_SUPPKEY", "S_SUPPKEY")));
}

JoinTable *TpchHelper::get_query6_results() {
	Table *nr = get_nations_table()
		->join(
			get_regions_table(),
			SQLite3JoinSettings("N_REGIONKEY", "R_REGIONKEY"));
	Table *n1 = get_supplier_table()
		->join(
			nr,
			SQLite3JoinSettings("S_NATIONKEY", "N_NATIONKEY"));
	Table *n2 = get_partsupp_table()
		->join(
			get_part_table(),
			SQLite3JoinSettings("PS_PARTKEY", "P_PARTKEY"));

	return dynamic_cast<JoinTable*>(n1->join(n2, SQLite3JoinSettings("S_SUPPKEY", "PS_SUPPKEY")));
}

JoinTable *TpchHelper::get_query7_results() {
	return dynamic_cast<JoinTable*>(
		get_lineitem_table()->join(
			get_orders_table(),
			SQLite3JoinSettings("L_ORDERKEY","O_ORDERKEY")));
}










