#include "Stack.h"
#include <iostream>
#include <sstream>

const string DATA_FILE = "stack.txt";

static Stack stackInstance;

void loadStack() {
    clearStack(stackInstance);
    initStack(stackInstance);
    readFromFile(stackInstance, DATA_FILE);
}

void saveStack() {
    writeToFile(stackInstance, DATA_FILE);
}

void printStack(Stack &s) {
    for (int i = 0; i < s.size; ++i) {
        cout << s.data[i];
        if (i + 1 < s.size) cout << " ";
    }
    cout << endl;
}

void processCommand(const string &line) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "PUSH") {
        string val; ss >> val;
        Push(stackInstance, val);
        saveStack();
        cout << "Pushed " << val << "\n";
        return;
    }

    if (cmd == "POP") {
        string val;
        if (Pop(stackInstance, val) != "") {
            saveStack();
            cout << "Popped " << val << "\n";
        } else {
            cout << "Stack empty\n";
        }
        return;
    }

    if (cmd == "TOP") {
        if (length(stackInstance) > 0) cout << "Top = " << top(stackInstance) << "\n";
        else cout << "Stack empty\n";
        return;
    }

    if (cmd == "LENGTH") {
        cout << "Length = " << length(stackInstance) << "\n";
        return;
    }

    if (cmd == "CLEAR") {
        clearStack(stackInstance);
        initStack(stackInstance);
        saveStack();
        cout << "Stack cleared\n";
        return;
    }

    if (cmd == "PRINT") {
        printStack(stackInstance);
        return;
    }

    cout << "Unknown command: " << cmd << "\n";
}

int main() {
    initStack(stackInstance);
    loadStack();

    cout << "Stack CLI. Functions:\n"
              << "  PUSH <val>   - push value\n"
              << "  POP          - pop value\n"
              << "  TOP          - show top\n"
              << "  LENGTH       - show length\n"
              << "  PRINT        - print stack (bottom..top)\n"
              << "  CLEAR        - clear stack\n"
              << "  EXIT         - quit\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(line);
    }

    clearStack(stackInstance);
    return 0;
}
