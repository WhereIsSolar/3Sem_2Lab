#pragma once
#include <string>

using namespace std;

struct Array {
    string* data;
    int size;
    int capacity;
};

void initArray(Array &arr, int initialCapacity = 10);

void addEnd(Array &arr, const string &val);
bool addAt(Array &arr, int index, const string &val);

string get(Array &arr, int index);
bool set(Array &arr, int index, const string &val);

bool removeAt(Array &arr, int index);

int length(Array &arr);

void readFromFile(Array &arr, const string &filename);
void writeToFile(Array &arr, const string &filename);

void clearArray(Array &arr);
