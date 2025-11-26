#include "Tree.h"
#include <iostream>
#include <cmath>
using namespace std;

static int checkBalanceRec(RBNode* node, bool& balanced) {
    if (!node || !balanced) {
        return 0;  // Пустое поддерево имеет высоту 0
    }
    
    // Рекурсивно проверяем левое и правое поддеревья
    int leftHeight = checkBalanceRec(node->left, balanced);
    int rightHeight = checkBalanceRec(node->right, balanced);
    
    // условие АВЛ-баланса
    if (abs(leftHeight - rightHeight) > 1) {
        balanced = false;  
    }
    
    // Возвращаем высоту текущего поддерева
    return max(leftHeight, rightHeight) + 1;
}

bool isAVLBalanced(RBTree &tree) {
    bool balanced = true;  // Изначально предполагаем, что дерево сбалансировано
    checkBalanceRec(tree.root, balanced);
    return balanced;
}

void processAVLCheck() {
    RBTree tree;
    initTree(tree);
    
    cout << "Введите последовательность чисел (завершите 0):" << endl;
    
    int val;
    while (cin >> val && val != 0) {
        // Вставляем только уникальные значения
        if (!find(tree, val)) {
            insert(tree, val);
        }
    }
    
    // Проверяем АВЛ-баланс
    if (isAVLBalanced(tree)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    clearTree(tree);
}

int main() {
    processAVLCheck();
    return 0;
}
