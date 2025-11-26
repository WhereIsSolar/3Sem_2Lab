#include <iostream>
#include <sstream>
#include "Array.h"

const string DATA_FILE = "array.txt";

void loadArray(Array &arr) {
    clearArray(arr);
    initArray(arr);
    readFromFile(arr, DATA_FILE);
}

void saveArray(Array &arr) {
    writeToFile(arr, DATA_FILE);
}

void printArray(Array &arr) {
    for (int i = 0; i < arr.size; i++) cout << arr.data[i] << (i < arr.size - 1 ? " " : "");
    cout << endl;
}

void processCommand(Array &arr, const string &commandLine) {
    stringstream ss(commandLine);
    string cmd;
    ss >> cmd;

    if (cmd == "PRINT") {
        printArray(arr);
        return;
    }

    if (cmd == "ACLEAR") {
        clearArray(arr);
        initArray(arr);
        saveArray(arr);
        cout << "Array cleared.\n";
        return;
    }

    if (cmd == "AADDEND") {
        string val; ss >> val;
        addEnd(arr, val);
        saveArray(arr);
        cout << "Added " << val << " to end.\n";
        return;
    }

    if (cmd == "AADD") {
        int index; string val; ss >> index >> val;
        if (addAt(arr, index, val)) {
            saveArray(arr);
            cout << "Inserted " << val << " at index " << index << ".\n";
        } else cout << "Index out of range.\n";
        return;
    }

    if (cmd == "AGET") {
        int index; ss >> index;
        try {
            cout << "Array[" << index << "] = " << get(arr, index) << "\n";
        } catch (...) {
            cout << "Index out of range.\n";
        }
        return;
    }

    if (cmd == "ASET") {
        int index; string val; ss >> index >> val;
        if (set(arr, index, val)) {
            saveArray(arr);
            cout << "Set index " << index << " = " << val << "\n";
        } else cout << "Index out of range.\n";
        return;
    }

    if (cmd == "AREM") {
        int index; ss >> index;
        if (removeAt(arr, index)) {
            saveArray(arr);
            cout << "Removed element at index " << index << ".\n";
        } else cout << "Index out of range.\n";
        return;
    }

    cout << "Unknown command: " << cmd << "\n";
}

int main() {
    Array arr;
    initArray(arr);
    loadArray(arr);

    cout << "Array CLI. Functions:\n"
              << "  AADDEND <val>       - add to end\n"
              << "  AADD <index> <val>  - add at index\n"
              << "  AGET <index>        - get value at index\n"
              << "  ASET <index> <val>  - set value at index\n"
              << "  AREM <index>        - remove element at index\n"
              << "  ACLEAR              - clear array\n"
              << "  PRINT               - print array\n"
              << "  EXIT                - quit\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(arr, line);
    }

    clearArray(arr);
    return 0;
}
