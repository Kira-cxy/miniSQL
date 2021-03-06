//
// Created by Kira on 2017/6/10.
//

#ifndef MINISQL_BUFFERUNIT_H
#define MINISQL_BUFFERUNIT_H

#include <vector>
#include <string>
#include <cstring>

using namespace std;

class BufferDataBlock {
public:
    char *data;
    bool visited;
    bool dirty;
    int indexInFile; // 文件中第几个block
    size_t size;     // data的大小

    BufferDataBlock(size_t size) : visited(false), dirty(false), indexInFile(-1) {
        // 需要delete
        data = new char[size];
        this->size = size;
    }

    BufferDataBlock(const BufferDataBlock &block) : visited(block.visited), dirty(block.dirty),
                                                    indexInFile(block.indexInFile), size(block.size) {
        data = new char[block.size];
        memcpy(data, block.data, block.size);
    };

    ~BufferDataBlock() {
        delete[] data;
    }
};

// 管理一张表的所有buffer
class BufferUnit {
private:
    // 以下两个vector为映射关系
    vector<int> blockIndexInBuffer; // 他的size就是文件有几个block
    vector<BufferDataBlock> blocks;

    size_t blockSize;
    size_t blockNum;
    size_t fileSize;

public:
    string fileName;

private:
    int getAvailableBlock();
public:
    bool readBlock(int blockIndexInFile, char *outBuffer);
    bool writeBlock(int blockIndexInFile, char const *inBuffer);
    bool deleteLastBlock();
    bool enlargeFile();
    // 这里fileSize是0有问题吗？
    BufferUnit(const string &tableName, size_t blockSize, size_t blockNum, size_t fileSize);

    ~BufferUnit();
};

#endif //MINISQL_BUFFERUNIT_H
