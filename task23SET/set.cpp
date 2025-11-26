#include "set.h"
#include <iostream>
#include <fstream>

using namespace std;

int hash1(int key, int capacity) {
    return key % capacity;
}

int hash2(int key, int capacity) {
    return 1 + (key % (capacity - 1));
}

void rehashSet(Set &s) {
    int oldCapacity = s.capacity;
    SetNode* oldTable = s.table;
    
    s.capacity = s.capacity * 2 + 1;
    s.table = new SetNode[s.capacity];
    s.size = 0;
    
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].occupied && !oldTable[i].deleted) {
            insert(s, oldTable[i].key);
        }
    }
    
    delete[] oldTable;
}

// Основные функции
void initSet(Set &s, int initialCapacity) {
    s.capacity = initialCapacity;
    s.table = new SetNode[s.capacity];
    s.size = 0;
}

bool insert(Set &s, int key) {
    // Проверка коэффициента загрузки
    if (static_cast<float>(s.size) / s.capacity >= 0.7f) {
        rehashSet(s);
    }
    
    int h1 = hash1(key, s.capacity);
    int h2 = hash2(key, s.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < s.capacity; attempt++) {
        if (!s.table[i].occupied || s.table[i].deleted) {
            s.table[i].key = key;
            s.table[i].occupied = true;
            s.table[i].deleted = false;
            s.size++;
            return true;
        }
        // Если ключ уже существует
        if (s.table[i].occupied && !s.table[i].deleted && s.table[i].key == key) {
            return false; // Элемент уже есть в множестве
        }
        i = (i + h2) % s.capacity;
    }
    return false;
}

bool contains(Set &s, int key) {
    int h1 = hash1(key, s.capacity);
    int h2 = hash2(key, s.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < s.capacity; attempt++) {
        if (!s.table[i].occupied && !s.table[i].deleted) {
            break;
        }
        if (s.table[i].occupied && !s.table[i].deleted && s.table[i].key == key) {
            return true;
        }
        i = (i + h2) % s.capacity;
    }
    return false;
}

bool remove(Set &s, int key) {
    int h1 = hash1(key, s.capacity);
    int h2 = hash2(key, s.capacity);
    int i = h1;
    
    for (int attempt = 0; attempt < s.capacity; attempt++) {
        if (!s.table[i].occupied && !s.table[i].deleted) {
            break;
        }
        if (s.table[i].occupied && !s.table[i].deleted && s.table[i].key == key) {
            s.table[i].deleted = true;
            s.size--;
            return true;
        }
        i = (i + h2) % s.capacity;
    }
    return false;
}

int getSize(Set &s) {
    return s.size;
}

bool isEmpty(Set &s) {
    return s.size == 0;
}

void printSet(Set &s) {
    cout << "Set elements: ";
    bool first = true;
    for (int i = 0; i < s.capacity; i++) {
        if (s.table[i].occupied && !s.table[i].deleted) {
            if (!first) cout << ", ";
            cout << s.table[i].key;
            first = false;
        }
    }
    if (first) cout << "empty";
    cout << endl;
}

void readFromFile(Set &s, const string &filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    
    int key;
    while (in >> key) {
        insert(s, key);
    }
    in.close();
}

void writeToFile(Set &s, const string &filename) {
    ofstream out(filename);
    for (int i = 0; i < s.capacity; i++) {
        if (s.table[i].occupied && !s.table[i].deleted) {
            out << s.table[i].key << endl;
        }
    }
    out.close();
}

void clearSet(Set &s) {
    for (int i = 0; i < s.capacity; i++) {
        s.table[i].occupied = false;
        s.table[i].deleted = false;
    }
    s.size = 0;
}

void destroySet(Set &s) {
    delete[] s.table;
    s.table = nullptr;
    s.size = 0;
    s.capacity = 0;
}
