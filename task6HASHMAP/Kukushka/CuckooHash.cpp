#include "CuckooHash.h"
#include <iostream>
#include <fstream>

using namespace std;

int hash1(int key, int capacity) {
    return key % capacity;
}

int hash2(int key, int capacity) {
    return (key / capacity) % capacity;
}

void rehashCuckooTable(CuckooHashTable &cht) {
    int oldCapacity = cht.capacity;
    CuckooNode* oldTable1 = cht.table1;
    CuckooNode* oldTable2 = cht.table2;
    
    cht.capacity = cht.capacity * 2 + 1;
    cht.table1 = new CuckooNode[cht.capacity];
    cht.table2 = new CuckooNode[cht.capacity];
    cht.size = 0;
    
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable1[i].occupied) {
            insert(cht, oldTable1[i].key, oldTable1[i].value);
        }
        if (oldTable2[i].occupied) {
            insert(cht, oldTable2[i].key, oldTable2[i].value);
        }
    }
    
    delete[] oldTable1;
    delete[] oldTable2;
}

bool insertHelper(CuckooHashTable &cht, int key, const string &value, int tableNum, int depth) {
    if (depth > cht.capacity) {
        return false;
    }
    
    if (tableNum == 1) {
        int pos = hash1(key, cht.capacity);
        if (!cht.table1[pos].occupied) {
            cht.table1[pos].key = key;
            cht.table1[pos].value = value;
            cht.table1[pos].occupied = true;
            return true;
        } else {
            int displacedKey = cht.table1[pos].key;
            string displacedValue = cht.table1[pos].value;
            cht.table1[pos].key = key;
            cht.table1[pos].value = value;
            return insertHelper(cht, displacedKey, displacedValue, 2, depth + 1);
        }
    } else {
        int pos = hash2(key, cht.capacity);
        if (!cht.table2[pos].occupied) {
            cht.table2[pos].key = key;
            cht.table2[pos].value = value;
            cht.table2[pos].occupied = true;
            return true;
        } else {
            int displacedKey = cht.table2[pos].key;
            string displacedValue = cht.table2[pos].value;
            cht.table2[pos].key = key;
            cht.table2[pos].value = value;
            return insertHelper(cht, displacedKey, displacedValue, 1, depth + 1);
        }
    }
}

void initCuckooTable(CuckooHashTable &cht, int initialCapacity) {
    cht.capacity = initialCapacity;
    cht.table1 = new CuckooNode[cht.capacity];
    cht.table2 = new CuckooNode[cht.capacity];
    cht.size = 0;
}

bool insert(CuckooHashTable &cht, int key, const string &value) {
    if (search(cht, key) != "") {
        return false;
    }
    
    if (static_cast<float>(cht.size) / (cht.capacity * 2) >= 0.5f) {
        rehashCuckooTable(cht);
    }
    
    if (insertHelper(cht, key, value, 1, 0)) {
        cht.size++;
        return true;
    } else {
        rehashCuckooTable(cht);
        if (insertHelper(cht, key, value, 1, 0)) {
            cht.size++;
            return true;
        }
    }
    return false;
}

string search(CuckooHashTable &cht, int key) {
    int pos1 = hash1(key, cht.capacity);
    if (cht.table1[pos1].occupied && cht.table1[pos1].key == key) {
        return cht.table1[pos1].value;
    }
    
    int pos2 = hash2(key, cht.capacity);
    if (cht.table2[pos2].occupied && cht.table2[pos2].key == key) {
        return cht.table2[pos2].value;
    }
    
    return "";
}

bool remove(CuckooHashTable &cht, int key) {
    int pos1 = hash1(key, cht.capacity);
    if (cht.table1[pos1].occupied && cht.table1[pos1].key == key) {
        cht.table1[pos1].occupied = false;
        cht.size--;
        return true;
    }
    
    int pos2 = hash2(key, cht.capacity);
    if (cht.table2[pos2].occupied && cht.table2[pos2].key == key) {
        cht.table2[pos2].occupied = false;
        cht.size--;
        return true;
    }
    
    return false;
}

int getCuckooSize(CuckooHashTable &cht) {
    return cht.size;
}

bool isCuckooEmpty(CuckooHashTable &cht) {
    return cht.size == 0;
}

void printCuckooTable(CuckooHashTable &cht) {
    cout << "Table 1:" << endl;
    for (int i = 0; i < cht.capacity; i++) {
        cout << "[" << i << "]: ";
        if (cht.table1[i].occupied) {
            cout << cht.table1[i].key << " -> " << cht.table1[i].value;
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
    
    cout << "Table 2:" << endl;
    for (int i = 0; i < cht.capacity; i++) {
        cout << "[" << i << "]: ";
        if (cht.table2[i].occupied) {
            cout << cht.table2[i].key << " -> " << cht.table2[i].value;
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}

void clearCuckooTable(CuckooHashTable &cht) {
    for (int i = 0; i < cht.capacity; i++) {
        cht.table1[i].occupied = false;
        cht.table2[i].occupied = false;
    }
    cht.size = 0;
}

void destroyCuckooTable(CuckooHashTable &cht) {
    delete[] cht.table1;
    delete[] cht.table2;
    cht.table1 = nullptr;
    cht.table2 = nullptr;
    cht.size = 0;
    cht.capacity = 0;
}

void readFromFile(CuckooHashTable &cht, const string &filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    
    int key;
    string value;
    while (in >> key >> value) {
        insert(cht, key, value);
    }
    in.close();
}

void writeToFile(CuckooHashTable &cht, const string &filename) {
    ofstream out(filename);
    for (int i = 0; i < cht.capacity; i++) {
        if (cht.table1[i].occupied) {
            out << cht.table1[i].key << " " << cht.table1[i].value << endl;
        }
        if (cht.table2[i].occupied) {
            out << cht.table2[i].key << " " << cht.table2[i].value << endl;
        }
    }
    out.close();
}
