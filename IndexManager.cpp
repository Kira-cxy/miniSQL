#include <iostream>
#include <fstream>
#include "IndexManager.h"
#include "BpTree.h"
#include "RecordManager.h"
#include "Catalog.h"

using namespace std;

void IndexManager::createIndex(const Attribute &attr, std::string indexName, TableStruct &table) {
    BpTree index(table, indexName, attr);
    vector<Condition> nullCon;
    vector<Tuple> tuples;
    RecordManager rm;
    rm.selectFromTable(table, nullCon, tuples);
	names[table.tableName] = indexName;
    int i;
    for (i = 0; i < table.attrs.size(); i++)
        if (table.attrs[i].attrName == attr.attrName) {
            table.attrs[i].isIndex = 1;
            break;
        }
    for (vector<Tuple>::iterator it = tuples.begin(); it < tuples.end(); it++) {
        Tuple &temp = *it;
        if (it == tuples.begin())
            index.initialize(temp.data[i], 0);
        else
            index.insert(temp.data[i], it - tuples.begin());
    }
}

void IndexManager::dropIndex(std::string indexName) {
    vector<Condition> nullCon;
    vector<Tuple> tuples;
    string filename("./data/" + indexName + ".index");
    BpTree index(indexName);
    TableStruct &table = cm.getTable(index.tableName);
    rm.selectFromTable(table, nullCon, tuples);
    int i;
    for (i = 0; i < table.attrs.size(); i++)
        table.attrs[i].isIndex = 0;
    remove(filename.c_str());
}

int IndexManager::exactSearchWithIndex(std::string indexName, Data *value) {
    BpTree index(indexName);
    if (index.size == 0)
        return -1;
    else
        return index.find(value);
}

vector<int> IndexManager::rangeSearchWithIndex(std::string indexName, Data *down, Data *up) {
    BpTree index(indexName);
    if (index.size == 0)
        return vector<int>();
    else
        return index.range(down, up);
}

void IndexManager::insertNew(string indexName, Data *value, int addr) {
    BpTree index(indexName);
    if (index.size == 0)
        index.initialize(value, addr);
    else
        index.insert(value, addr);
}

void IndexManager::deleteOld(string indexName, Data *value) {
    BpTree index(indexName);
    if (index.size == 0)
        ;
    else
        index.deleteData(value);
}