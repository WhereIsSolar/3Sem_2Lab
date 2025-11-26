#include <iostream>
#include <sstream>
#include <string>
#include "CuckooHash.h"

const string DATA_FILE = "hash_table.txt";

void loadTable(CuckooHashTable &cht) {
    readFromFile(cht, DATA_FILE);
}

void saveTable(CuckooHashTable &cht) {
    writeToFile(cht, DATA_FILE);
}

void processCommand(CuckooHashTable &cht, const string &commandLine) {
    stringstream ss(commandLine);
    string cmd;
    ss >> cmd;

    if (cmd == "PRINT") {
        printCuckooTable(cht);
        return;
    }

    if (cmd == "CLEAR") {
        clearCuckooTable(cht);
        saveTable(cht);
        cout << "Table cleared.\n";
        return;
    }

    if (cmd == "INSERT") {
        int key; string value;
        ss >> key >> value;
        if (insert(cht, key, value)) {
            saveTable(cht);
            cout << "Inserted " << key << " -> " << value << "\n";
        } else {
            cout << "Insert failed\n";
        }
        return;
    }

    if (cmd == "SEARCH") {
        int key; ss >> key;
        string result = search(cht, key);
        if (!result.empty()) {
            cout << "Found: " << result << "\n";
        } else {
            cout << "Not found\n";
        }
        return;
    }

    if (cmd == "REMOVE") {
        int key; ss >> key;
        if (remove(cht, key)) {
            saveTable(cht);
            cout << "Removed\n";
        } else {
            cout << "Not found\n";
        }
        return;
    }

    cout << "Unknown command\n";
}

int main() {
    CuckooHashTable cht;
    initCuckooTable(cht);
    loadTable(cht);

    cout << "Cuckoo Hash Table CLI\n"
         << "INSERT key value\n"
         << "SEARCH key\n" 
         << "REMOVE key\n"
         << "CLEAR\n"
         << "PRINT\n"
         << "EXIT\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(cht, line);
    }

    destroyCuckooTable(cht);
    return 0;
}
