#ifndef CUCKOO_HASH_H
#define CUCKOO_HASH_H

#include <string>

using namespace std;

struct CuckooNode {
    int key;
    string value;
    bool occupied;
    
    CuckooNode() : key(0), value(""), occupied(false) {}
};

struct CuckooHashTable {
    CuckooNode* table1;
    CuckooNode* table2;
    int size;
    int capacity;
};

void initCuckooTable(CuckooHashTable &cht, int initialCapacity = 11);
bool insert(CuckooHashTable &cht, int key, const string &value);
string search(CuckooHashTable &cht, int key);
bool remove(CuckooHashTable &cht, int key);
int getCuckooSize(CuckooHashTable &cht);
bool isCuckooEmpty(CuckooHashTable &cht);
void printCuckooTable(CuckooHashTable &cht);
void clearCuckooTable(CuckooHashTable &cht);
void destroyCuckooTable(CuckooHashTable &cht);
void readFromFile(CuckooHashTable &cht, const string &filename);
void writeToFile(CuckooHashTable &cht, const string &filename);

#endif
