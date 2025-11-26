#include <iostream>
#include <sstream>
#include <string>
#include "hash.h"

const string DATA_FILE = "hashtable.txt";

void loadTable(HashTable &ht) {
    clearTable(ht);
    readFromFile(ht, DATA_FILE);
}

void saveTable(HashTable &ht) {
    writeToFile(ht, DATA_FILE);
}

void processCommand(HashTable &ht, const string &commandLine) {
    stringstream ss(commandLine);
    string cmd;
    ss >> cmd;

    if (cmd == "PRINT") {
        printTable(ht);
        return;
    }

    if (cmd == "HCLEAR") {
        clearTable(ht);
        saveTable(ht);
        cout << "HashTable cleared.\n";
        return;
    }

    if (cmd == "HINSERT") {
        int key; string value;
        ss >> key >> value;
        if (insert(ht, key, value)) {
            saveTable(ht);
            cout << "Inserted key " << key << " with value '" << value << "'.\n";
        } else {
            cout << "Failed to insert key " << key << ".\n";
        }
        return;
    }

    if (cmd == "HSEARCH") {
        int key; ss >> key;
        string result = search(ht, key);
        if (!result.empty()) {
            cout << "Key " << key << " = '" << result << "'\n";
        } else {
            cout << "Key " << key << " not found.\n";
        }
        return;
    }

    if (cmd == "HREMOVE") {
        int key; ss >> key;
        if (remove(ht, key)) {
            saveTable(ht);
            cout << "Removed key " << key << ".\n";
        } else {
            cout << "Key " << key << " not found.\n";
        }
        return;
    }

    if (cmd == "HSIZE") {
        cout << "Size: " << getSize(ht) << "\n";
        return;
    }

    if (cmd == "HEMPTY") {
        cout << "Table is " << (isEmpty(ht) ? "empty" : "not empty") << "\n";
        return;
    }

    if (cmd == "HSTATS") {
        cout << "Size: " << getSize(ht) << "/" << ht.capacity 
             << " (load factor: " << (static_cast<float>(getSize(ht)) / ht.capacity * 100) << "%)\n";
        return;
    }

    cout << "Unknown command: " << cmd << "\n";
}

int main() {
    HashTable ht;
    initTable(ht);
    loadTable(ht);

    cout << "HashTable CLI. Functions:\n"
              << "  HINSERT <key> <value>     - insert key-value pair\n"
              << "  HSEARCH <key>             - search value by key\n"
              << "  HREMOVE <key>             - remove key-value pair\n"
              << "  HSIZE                     - get current size\n"
              << "  HEMPTY                    - check if table is empty\n"
              << "  HSTATS                    - show table statistics\n"
              << "  HCLEAR                    - clear table\n"
              << "  PRINT                     - print entire table\n"
              << "  EXIT                      - quit\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(ht, line);
    }

    destroyTable(ht);
    return 0;
}
