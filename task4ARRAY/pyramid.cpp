#include <iostream>
#include "Array.h"

using namespace std;

struct Block {
    long long width;
    long long height;
};

Block parseBlock(const string& blockStr) {
    size_t pos = blockStr.find(' ');
    Block b;
    b.width = stoll(blockStr.substr(0, pos));
    b.height = stoll(blockStr.substr(pos + 1));
    return b;
}

long long calculatePyramidHeight(Array& blocks, int baseIndex) {
    // Получаем базовый блок
    string baseStr = blocks.data[baseIndex];
    Block baseBlock = parseBlock(baseStr);
    long long height = baseBlock.height;
    
    // Проходим по всем блокам и добавляем те, что можно поставить сверху
    for (int i = 0; i < blocks.size; i++) {
        if (i == baseIndex) continue;
        
        string currentStr = blocks.data[i];
        Block currentBlock = parseBlock(currentStr);
        if (currentBlock.width < baseBlock.width) {
            height += currentBlock.height;
        }
    }
    
    return height;
}

long long findMaxPyramidHeight(Array& blocks) {
    long long maxHeight = 0;
    
    for (int i = 0; i < blocks.size; i++) {
        long long currentHeight = calculatePyramidHeight(blocks, i);
        if (currentHeight > maxHeight) {
            maxHeight = currentHeight;
        }
    }
    
    return maxHeight;
}

void readBlocks(Array& blocks, int n) {
    for (int i = 0; i < n; i++) {
        long long w, h;
        cin >> w >> h;
        string blockStr = to_string(w) + " " + to_string(h);
        addEnd(blocks, blockStr);
    }
}

int main() {
    int n;
    cin >> n;
    
    Array blocks;
    initArray(blocks, n);
    
    readBlocks(blocks, n);
    
    long long maxHeight = findMaxPyramidHeight(blocks);
    cout << maxHeight << endl;
    
    clearArray(blocks);
    return 0;
}
