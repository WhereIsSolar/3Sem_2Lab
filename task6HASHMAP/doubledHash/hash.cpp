#include "hash.h"
#include <iostream>
#include <fstream>

using namespace std;

int hash1(int key, int capacity) {
    return key % capacity;
}

int hash2(int key, int capacity) {
    return 1 + (key % (capacity - 1));
}

void rehashTable(HashTable &ht) {
    int oldCapacity = ht.capacity;
    HashNode* oldTable = ht.table;
    
    ht.capacity = ht.capacity * 2 + 1;
    ht.table = new HashNode[ht.capacity];
    ht.size = 0;
    
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].occupied && !oldTable[i].deleted) {
            insert(ht, oldTable[i].key, oldTable[i].value);
        }
    }
    
    delete[] oldTable;
}

// Основные функции
void initTable(HashTable &ht, int initialCapacity) {
    ht.capacity = initialCapacity;
    ht.table = new HashNode[ht.capacity];
    ht.size = 0;
}

bool insert(HashTable &ht, int key, const string &value) {
    // Проверка коэффициента загрузки
    if (static_cast<float>(ht.size) / ht.capacity >= 0.7f) {
        rehashTable(ht);
    }
    
    int h1 = hash1(key, ht.capacity);
    int h2 = hash2(key, ht.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < ht.capacity; attempt++) {
        if (!ht.table[i].occupied || ht.table[i].deleted) {
            ht.table[i].key = key;
            ht.table[i].value = value;
            ht.table[i].occupied = true;
            ht.table[i].deleted = false;
            ht.size++;
            return true;
        }
        // Если ключ уже существует, обновляем значение
        if (ht.table[i].occupied && !ht.table[i].deleted && ht.table[i].key == key) {
            ht.table[i].value = value;
            return true;
        }
        i = (i + h2) % ht.capacity;
    }
    return false;
}

string search(HashTable &ht, int key) {
    int h1 = hash1(key, ht.capacity);
    int h2 = hash2(key, ht.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < ht.capacity; attempt++) {
        if (!ht.table[i].occupied && !ht.table[i].deleted) {
            break;
        }
        if (ht.table[i].occupied && !ht.table[i].deleted && ht.table[i].key == key) {
            return ht.table[i].value;
        }
        i = (i + h2) % ht.capacity;
    }
    return "";
}

bool remove(HashTable &ht, int key) {
    int h1 = hash1(key, ht.capacity);
    int h2 = hash2(key, ht.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < ht.capacity; attempt++) {
        if (!ht.table[i].occupied && !ht.table[i].deleted) {
            break;
        }
        if (ht.table[i].occupied && !ht.table[i].deleted && ht.table[i].key == key) {
            ht.table[i].deleted = true;
            ht.size--;
            return true;
        }
        i = (i + h2) % ht.capacity;
    }
    return false;
}

int getSize(HashTable &ht) {
    return ht.size;
}

bool isEmpty(HashTable &ht) {
    return ht.size == 0;
}

void printTable(HashTable &ht) {
    for (int i = 0; i < ht.capacity; i++) {
        cout << "[" << i << "]: ";
        if (ht.table[i].occupied && !ht.table[i].deleted) {
            cout << ht.table[i].key << " -> " << ht.table[i].value;
        } else if (ht.table[i].deleted) {
            cout << "DELETED";
        } else {
            cout << "EMPTY";
        }
        cout << endl;
    }
}

void readFromFile(HashTable &ht, const string &filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    
    int key;
    string value;
    while (in >> key >> value) {
        insert(ht, key, value);
    }
    in.close();
}

void writeToFile(HashTable &ht, const string &filename) {
    ofstream out(filename);
    for (int i = 0; i < ht.capacity; i++) {
        if (ht.table[i].occupied && !ht.table[i].deleted) {
            out << ht.table[i].key << " " << ht.table[i].value << endl;
        }
    }
    out.close();
}

void clearTable(HashTable &ht) {
    for (int i = 0; i < ht.capacity; i++) {
        ht.table[i].occupied = false;
        ht.table[i].deleted = false;
    }
    ht.size = 0;
}

void destroyTable(HashTable &ht) {
    delete[] ht.table;
    ht.table = nullptr;
    ht.size = 0;
    ht.capacity = 0;
}
