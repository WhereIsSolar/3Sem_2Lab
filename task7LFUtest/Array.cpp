#include "Array.h"
#include <iostream>
#include <fstream>
#include <algorithm>

const int MIN_CAPACITY = 10;

void initArray(Array &arr, int initialCapacity) {
    arr.capacity = max(initialCapacity, MIN_CAPACITY);
    arr.data = new string[arr.capacity];
    arr.size = 0;
}

void ensureCapacity(Array &arr) {
    if (arr.size >= arr.capacity) {
        int newCap = (arr.capacity > 0) ? arr.capacity * 2 : MIN_CAPACITY;
        string* newData = new string[newCap];
        if (arr.data && arr.size > 0) copy(arr.data, arr.data + arr.size, newData);
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
}

void shrinkCapacity(Array &arr) {
    if (arr.capacity > MIN_CAPACITY && arr.size < arr.capacity / 4) {
        int newCap = max(arr.capacity / 2, MIN_CAPACITY);
        string* newData = new string[newCap];
        if (arr.data && arr.size > 0) copy(arr.data, arr.data + arr.size, newData);
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
}

void addEnd(Array &arr, const string &val) {
    ensureCapacity(arr);
    arr.data[arr.size++] = val;
}

bool addAt(Array &arr, int index, const string &val) {
    if (index < 0 || index > arr.size) return false;
    ensureCapacity(arr);
    for (int i = arr.size; i > index; i--) arr.data[i] = arr.data[i-1];
    arr.data[index] = val;
    arr.size++;
    return true;
}

string get(Array &arr, int index) {
    if (index < 0 || index >= arr.size) throw out_of_range("Index out of range");
    return arr.data[index];
}

bool set(Array &arr, int index, const string &val) {
    if (index < 0 || index >= arr.size) return false;
    arr.data[index] = val;
    return true;
}

bool removeAt(Array &arr, int index) {
    if (index < 0 || index >= arr.size) return false;
    for (int i = index; i < arr.size - 1; i++) arr.data[i] = arr.data[i+1];
    arr.size--;
    shrinkCapacity(arr);
    return true;
}

int length(Array &arr) {
    return arr.size;
}

void readFromFile(Array &arr, const string &filename) {
    if (!arr.data || arr.capacity == 0) initArray(arr);
    ifstream in(filename);
    if (!in.is_open()) return;
    string val;
    while (in >> val) addEnd(arr, val);
    in.close();
}

void writeToFile(Array &arr, const string &filename) {
    ofstream out(filename);
    for (int i = 0; i < arr.size; i++) {
        out << arr.data[i];
        if (i < arr.size - 1) out << " ";
    }
    out.close();
}

void clearArray(Array &arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}
