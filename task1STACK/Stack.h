#pragma once
#include <string>

using namespace std;

struct Stack {
    string* data;
    int size;
    int capacity;
};

void initStack(Stack &s, int capacity = 100);

string Push(Stack &s, const string &val);
string Pop(Stack &s, string &val);

char Push(Stack &s, const char val);

string top(Stack &s);
int length(Stack &s);

void readFromFile(Stack &s, const string &filename);
void writeToFile(Stack &s, const string &filename);

void clearStack(Stack &s);
