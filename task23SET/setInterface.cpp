#include "set.h"
#include <iostream>
#include <sstream>

using namespace std;

const string DATA_FILE = "set.txt";

void loadSet(Set &s) {
    clearSet(s);
    readFromFile(s, DATA_FILE);
}

void saveSet(Set &s) {
    writeToFile(s, DATA_FILE);
}

void processCommand(Set &s, const string &line) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "PRINT") { 
        printSet(s); 
        return; 
    }
    
    if (cmd == "CLEAR") {
        clearSet(s);
        saveSet(s);
        cout << "Set cleared.\n";
        return;
    }

    if (cmd == "ADD") {
        int key;
        if (ss >> key) {
            if (insert(s, key)) {
                saveSet(s);
                cout << "Added " << key << " to set.\n";
            } else {
                cout << "Element " << key << " already exists in set.\n";
            }
        } else {
            cout << "Invalid key.\n";
        }
        return;
    }

    if (cmd == "REMOVE") {
        int key;
        if (ss >> key) {
            if (remove(s, key)) {
                saveSet(s);
                cout << "Removed " << key << " from set.\n";
            } else {
                cout << "Element " << key << " not found in set.\n";
            }
        } else {
            cout << "Invalid key.\n";
        }
        return;
    }

    if (cmd == "CONTAINS") {
        int key;
        if (ss >> key) {
            if (contains(s, key)) {
                cout << "Set contains " << key << ".\n";
            } else {
                cout << "Set does not contain " << key << ".\n";
            }
        } else {
            cout << "Invalid key.\n";
        }
        return;
    }

    if (cmd == "SIZE") {
        cout << "Set size: " << getSize(s) << "\n";
        return;
    }

    if (cmd == "ISEMPTY") {
        if (isEmpty(s)) {
            cout << "Set is empty.\n";
        } else {
            cout << "Set is not empty.\n";
        }
        return;
    }

    cout << "Unknown command: " << cmd << "\n";
}

int main() {
    Set s;
    initSet(s);
    loadSet(s);

    cout << "Set CLI. Available commands:\n"
         << "  ADD <key>        - add element to set\n"
         << "  REMOVE <key>     - remove element from set\n"
         << "  CONTAINS <key>   - check if element exists\n"
         << "  SIZE             - get set size\n"
         << "  ISEMPTY          - check if set is empty\n"
         << "  CLEAR            - clear set\n"
         << "  PRINT            - print set elements\n"
         << "  EXIT             - quit program\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(s, line);
    }

    destroySet(s);
    return 0;
}
