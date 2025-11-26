#include "lfu_cache.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void initCache(LFUCache &cache, int capacity) {
    cache.capacity = capacity;
    cache.size = 0;
    cache.counter = 0;
    initTable(cache.keyTable, capacity * 2);
    initArray(cache.nodes, capacity);
    
    // Инициализируем массив пустыми узлами
    for (int i = 0; i < capacity; i++) {
        LFUNode emptyNode;
        emptyNode.key = -1;
        emptyNode.value = "";
        emptyNode.frequency = 0;
        emptyNode.timestamp = -1;
        addEnd(cache.nodes, "EMPTY"); // Заполняем пустыми значениями
    }
}

int findLFUNode(LFUCache &cache) {
    int minFreq = 1000000;
    int oldestTimestamp = 1000000;
    int lfuIndex = -1;
    
    for (int i = 0; i < cache.capacity; i++) {
        string nodeData = get(cache.nodes, i);
        if (nodeData == "EMPTY") continue;
        
        // Парсим данные узла из строки
        stringstream ss(nodeData);
        int key, freq, ts;
        string value;
        ss >> key >> value >> freq >> ts;
        
        if (freq < minFreq || (freq == minFreq && ts < oldestTimestamp)) {
            minFreq = freq;
            oldestTimestamp = ts;
            lfuIndex = i;
        }
    }
    
    return lfuIndex;
}

void set(LFUCache &cache, int key, const string &value) {
    if (cache.capacity <= 0) return;
    
    cache.counter++;
    
    // Проверяем, есть ли ключ уже в кэше
    string existingIndex = search(cache.keyTable, key);
    if (!existingIndex.empty()) {
        // Ключ уже существует - обновляем значение и частоту
        int index = stoi(existingIndex);
        string nodeData = get(cache.nodes, index);
        
        stringstream ss(nodeData);
        int oldKey, freq, ts;
        string oldValue;
        ss >> oldKey >> oldValue >> freq >> ts;
        
        // Обновляем узел
        freq++;
        stringstream newData;
        newData << key << " " << value << " " << freq << " " << cache.counter;
        set(cache.nodes, index, newData.str());
        return;
    }
    
    // Ключа нет в кэше
    if (cache.size < cache.capacity) {
        // Ищем первую свободную позицию
        int freeIndex = -1;
        for (int i = 0; i < cache.capacity; i++) {
            if (get(cache.nodes, i) == "EMPTY") {
                freeIndex = i;
                break;
            }
        }
        
        if (freeIndex != -1) {
            // Создаем новый узел
            stringstream newData;
            newData << key << " " << value << " " << 1 << " " << cache.counter;
            set(cache.nodes, freeIndex, newData.str());
            insert(cache.keyTable, key, to_string(freeIndex));
            cache.size++;
        }
    } else {
        // Нет места - удаляем LFU узел
        int lfuIndex = findLFUNode(cache);
        if (lfuIndex == -1) return;
        
        // Получаем данные удаляемого узла
        string lfuData = get(cache.nodes, lfuIndex);
        stringstream ss(lfuData);
        int oldKey, oldFreq, oldTs;
        string oldValue;
        ss >> oldKey >> oldValue >> oldFreq >> oldTs;
        
        // Удаляем старый ключ из хэш-таблицы
        remove(cache.keyTable, oldKey);
        
        // Заменяем на новый узел
        stringstream newData;
        newData << key << " " << value << " " << 1 << " " << cache.counter;
        set(cache.nodes, lfuIndex, newData.str());
        insert(cache.keyTable, key, to_string(lfuIndex));
    }
}

string get(LFUCache &cache, int key) {
    if (cache.capacity <= 0) return "-1";
    
    string indexStr = search(cache.keyTable, key);
    if (indexStr.empty()) {
        return "-1"; // Ключ не найден
    }
    
    cache.counter++;
    
    int index = stoi(indexStr);
    string nodeData = get(cache.nodes, index);
    
    // Парсим и обновляем узел
    stringstream ss(nodeData);
    int oldKey, freq, ts;
    string value;
    ss >> oldKey >> value >> freq >> ts;
    
    // Обновляем частоту и timestamp
    freq++;
    stringstream newData;
    newData << key << " " << value << " " << freq << " " << cache.counter;
    set(cache.nodes, index, newData.str());
    
    return value;
}

void printCache(LFUCache &cache) {
    cout << "LFU Cache (size: " << cache.size << "/" << cache.capacity << "):" << endl;
    
    for (int i = 0; i < cache.capacity; i++) {
        string nodeData = get(cache.nodes, i);
        if (nodeData == "EMPTY") {
            cout << "  [" << i << "] EMPTY" << endl;
        } else {
            stringstream ss(nodeData);
            int key, freq, ts;
            string value;
            ss >> key >> value >> freq >> ts;
            cout << "  [" << i << "] Key: " << key 
                 << ", Value: " << value 
                 << ", Freq: " << freq 
                 << ", TS: " << ts << endl;
        }
    }
    
    cout << "Hash Table state:" << endl;
    printTable(cache.keyTable);
}

void destroyCache(LFUCache &cache) {
    destroyTable(cache.keyTable);
    clearArray(cache.nodes);
    cache.size = 0;
    cache.capacity = 0;
    cache.counter = 0;
}
