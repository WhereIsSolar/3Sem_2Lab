#include "Stack.h"
#include <fstream>
#include <iostream>
#include <string>

static const int MIN_CAPACITY = 4;

void initStack(Stack &s, int capacity) {
    if (capacity < MIN_CAPACITY) capacity = MIN_CAPACITY;
    s.data = new string[capacity];
    s.size = 0;
    s.capacity = capacity;
}

static void growIfNeeded(Stack &s) {
    if (s.size < s.capacity) return;
    int newCap = s.capacity * 2;
    string* newData = new string[newCap];
    for (int i = 0; i < s.size; ++i) newData[i] = s.data[i];
    delete[] s.data;
    s.data = newData;
    s.capacity = newCap;
}

static void shrinkIfNeeded(Stack &s) {
    if (s.capacity <= MIN_CAPACITY) return;
    if (s.size * 4 >= s.capacity) return;
    int newCap = s.capacity / 2;
    if (newCap < MIN_CAPACITY) newCap = MIN_CAPACITY;
    string* newData = new string[newCap];
    for (int i = 0; i < s.size; ++i) newData[i] = s.data[i];
    delete[] s.data;
    s.data = newData;
    s.capacity = newCap;
}

string Push(Stack &s, const string &val) {
    growIfNeeded(s);
    s.data[s.size++] = val;
    return val;
}

char Push(Stack &s, const char val) {
    growIfNeeded(s);
    s.data[s.size++] = val;
    cout << val << " PUSHED"<< endl;
    return val;
}


string Pop(Stack &s, string &val) {
    if (s.size == 0) return "There Are no value!\n";
    val = s.data[--s.size];
    shrinkIfNeeded(s);
    cout << val << " POPED" << endl;
    return val;
}

string top(Stack &s) {
    if (s.size == 0) return string();
    return s.data[s.size - 1];
}

int length(Stack &s) {
    return s.size;
}

void readFromFile(Stack &s, const string &filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    string val;
    while (in >> val) Push(s, val);
    in.close();
}

void writeToFile(Stack &s, const string &filename) {
    ofstream out(filename);
    for (int i = 0; i < s.size; ++i) {
        out << s.data[i];
        if (i + 1 < s.size) out << " ";
    }
    out.close();
}

void clearStack(Stack &s) {
    delete[] s.data;
    s.data = nullptr;
    s.size = 0;
    s.capacity = 0;
}
