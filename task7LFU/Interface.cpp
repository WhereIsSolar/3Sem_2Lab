#include <iostream>
#include <sstream>
#include <string>
#include "lfu_cache.h"

using namespace std;

void processCommand(LFUCache& cache, const string& commandLine) {
    stringstream ss(commandLine);
    string cmd;
    ss >> cmd;

    if (cmd == "PRINT") {
        printCache(cache);
        return;
    }

    if (cmd == "SET") {
        int key; 
        string value;
        ss >> key >> value;
        if (ss.fail()) {
            cout << "Usage: SET <key> <value>" << endl;
            return;
        }
        set(cache, key, value);
        cout << "SET(" << key << "," << value << ")" << endl;
        return;
    }

    if (cmd == "GET") {
        int key;
        ss >> key;
        if (ss.fail()) {
            cout << "Usage: GET <key>" << endl;
            return;
        }
        string result = get(cache, key);
        cout << "GET(" << key << ") = " << result << endl;
        return;
    }

    if (cmd == "SIZE") {
        cout << "Size: " << cache.size << "/" << cache.capacity << endl;
        return;
    }

    cout << "Unknown command: " << cmd << endl;
}

int main() {
    int capacity;
    cout << "Enter cache capacity: ";
    cin >> capacity;
    cin.ignore();
    
    LFUCache cache;
    initCache(cache, capacity);
    
    cout << "=== LFU Cache CLI ===" << endl;
    cout << "Commands:" << endl;
    cout << "  SET <key> <value>  - set key-value pair" << endl;
    cout << "  GET <key>          - get value by key" << endl;
    cout << "  SIZE               - show current size" << endl;
    cout << "  PRINT              - print cache state" << endl;
    cout << "  EXIT               - quit program" << endl;

    string line;
    while (true) {
        cout << "LFU> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(cache, line);
    }

    destroyCache(cache);
    
    return 0;
}
