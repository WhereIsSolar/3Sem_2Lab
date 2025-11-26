#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include "hash.h"
#include "Array.h"

struct LFUNode {
    int key;
    string value;
    int frequency;
    int timestamp;
};

struct LFUCache {
    HashTable keyTable;  // key -> index in nodes array
    Array nodes;         // Array of LFUNode
    int capacity;
    int size;
    int counter;         // global timestamp counter
};

// Инициализация кэша
void initCache(LFUCache &cache, int capacity);

// Добавление/обновление значения по ключу
void set(LFUCache &cache, int key, const string &value);

// Получение значения по ключу
string get(LFUCache &cache, int key);

// Вывод состояния кэша
void printCache(LFUCache &cache);

// Освобождение памяти
void destroyCache(LFUCache &cache);

#endif
