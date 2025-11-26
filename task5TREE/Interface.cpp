#include "Tree.h"
#include <iostream>
#include <sstream>

using namespace std;

const string DATA_FILE = "rbtree.txt";
static RBTree tree;

void loadTree() {
    clearTree(tree);
    initTree(tree);
    readFromFile(tree, DATA_FILE);
}

void saveTree() {
    writeToFile(tree, DATA_FILE);
}

void processCommand(const string &line) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "INSERT") {
        int val; ss >> val;
        insert(tree, val);
        saveTree();
        cout << "Inserted " << val << "\n";
        return;
    }

    if (cmd == "REMOVE") {
        int val; ss >> val;
        if (remove(tree, val)) { saveTree(); cout << "Removed " << val << "\n"; }
        else cout << "Value not found\n";
        return;
    }

    if (cmd == "FIND") {
        int val; ss >> val;
        if (find(tree, val)) cout << "Found " << val << "\n";
        else cout << "Not found\n";
        return;
    }

    if (cmd == "PRINT") {
        cout << "Tree structure (R:red, B:black):\n";
        printTree(tree); // визуально
        return;
    }

    if (cmd == "INORDER") {
        inorderPrint(tree); // сортированный вывод
        return;
    }

    if (cmd == "CLEAR") {
        clearTree(tree);
        saveTree();
        cout << "Tree cleared\n";
        return;
    }

    cout << "Unknown command: " << cmd << "\n";
}

int main() {
    initTree(tree);
    loadTree();

    cout << "Red-Black Tree CLI. Commands:\n"
              << "  INSERT <val>  - add element\n"
              << "  REMOVE <val>  - remove element\n"
              << "  FIND <val>    - search element\n"
              << "  PRINT         - show tree structure\n"
              << "  INORDER       - show sorted values\n"
              << "  CLEAR         - clear tree\n"
              << "  EXIT          - quit\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(line);
    }

    clearTree(tree);
    return 0;
}
