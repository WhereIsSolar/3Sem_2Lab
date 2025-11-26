#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

struct HashNode {
    int key;
    string value;
    bool occupied;
    bool deleted;
    
    HashNode() : key(0), value(""), occupied(false), deleted(false) {}
};

struct HashTable {
    HashNode* table;
    int size;
    int capacity;
};

// Инициализация таблицы
void initTable(HashTable &ht, int initialCapacity = 11);

// Добавление элемента
bool insert(HashTable &ht, int key, const string &value);

// Поиск элемента
string search(HashTable &ht, int key);

// Удаление элемента
bool remove(HashTable &ht, int key);

// Получение количества элементов
int getSize(HashTable &ht);

// Проверка на пустоту
bool isEmpty(HashTable &ht);

// Вывод таблицы
void printTable(HashTable &ht);

// Чтение из файла
void readFromFile(HashTable &ht, const string &filename);

// Запись в файл
void writeToFile(HashTable &ht, const string &filename);

// Очистка таблицы
void clearTable(HashTable &ht);

// Освобождение памяти
void destroyTable(HashTable &ht);

#endif
