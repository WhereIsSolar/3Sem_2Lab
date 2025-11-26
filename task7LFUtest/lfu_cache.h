#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include "hash.h"
#include "Array.h"

struct LFUNode {
    int key;
    string value;
    int frequency;
    int timestamp;
    
    LFUNode() : key(-1), value(""), frequency(0), timestamp(-1) {}
};

struct LFUCache {
    HashTable keyTable;
    Array nodes;
    int capacity;
    int size;
    int counter;
    
    // КОНСТРУКТОР с инициализацией емкости
    LFUCache(int cap) {
        capacity = cap;
        size = 0;
        counter = 0;
        initTable(keyTable, capacity * 2);
        initArray(nodes, capacity);
        
        // Инициализируем массив пустыми узлами
        for (int i = 0; i < capacity; i++) {
            addEnd(nodes, "EMPTY");
        }
    }
};

// Инициализация кэша (теперь через конструктор)
void initCache(LFUCache &cache, int capacity);

void set(LFUCache &cache, int key, const string &value);
string get(LFUCache &cache, int key);
void printCache(LFUCache &cache);
void destroyCache(LFUCache &cache);

#endif
