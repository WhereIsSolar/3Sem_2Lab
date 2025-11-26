#ifndef SET_H
#define SET_H

#include <string>

using namespace std;

struct SetNode {
    int key;
    bool occupied;
    bool deleted;
    
    SetNode() : key(0), occupied(false), deleted(false) {}
};

struct Set {
    SetNode* table;
    int size;
    int capacity;
};

void initSet(Set &s, int initialCapacity = 11);
bool insert(Set &s, int key);
bool contains(Set &s, int key);
bool remove(Set &s, int key);
int getSize(Set &s);
bool isEmpty(Set &s);
void printSet(Set &s);
void readFromFile(Set &s, const string &filename);
void writeToFile(Set &s, const string &filename);
void clearSet(Set &s);
void destroySet(Set &s);

#endif
