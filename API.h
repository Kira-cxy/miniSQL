#pragma once
#include "Basis.h"
#include "TableStruct.h"
#include "Catalog.h"
#include "BufferManager.h"
#include "IndexManager.h"
#include "RecordManager.h"

class API
{
public:
	API() {};
	~API() {};
	void createTable(TableStruct&);
	void dropTable(std::string);
	void createIndex(std::string, std::string, std::string);
	void dropIndex(std::string);
	vector<Tuple> select(std::string tableName, vector<Condition>& condTable);
	void insertData(std::string tableName, Tuple& data);
	//void deleteData(std::string tableName);
	void deleteData(std::string tableName, vector<Condition>& condTable);
};