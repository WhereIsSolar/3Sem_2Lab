#include "lfu_cache.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void initCache(LFUCache &cache, int capacity) {
    // Конструктор уже все инициализировал
    // Оставил данную функцию т.к. делал по образу и подобию прошлых АСД
}

int findLFUNode(LFUCache &cache) {
    int minFreq = 1000000;
    int oldestTimestamp = 1000000;
    int lfuIndex = -1;
    
    for (int i = 0; i < cache.capacity; i++) {
        string nodeData = get(cache.nodes, i);
        if (nodeData == "EMPTY") continue;
        
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
    
    string existingIndex = search(cache.keyTable, key);
    if (!existingIndex.empty()) {
        int index = stoi(existingIndex);
        string nodeData = get(cache.nodes, index);
        
        stringstream ss(nodeData);
        int oldKey, freq, ts;
        string oldValue;
        ss >> oldKey >> oldValue >> freq >> ts;
        
        freq++;
        stringstream newData;
        newData << key << " " << value << " " << freq << " " << cache.counter;
        set(cache.nodes, index, newData.str());
        return;
    }
    
    if (cache.size < cache.capacity) {
        int freeIndex = -1;
        for (int i = 0; i < cache.capacity; i++) {
            if (get(cache.nodes, i) == "EMPTY") {
                freeIndex = i;
                break;
            }
        }
        
        if (freeIndex != -1) {
            stringstream newData;
            newData << key << " " << value << " " << 1 << " " << cache.counter;
            set(cache.nodes, freeIndex, newData.str());
            insert(cache.keyTable, key, to_string(freeIndex));
            cache.size++;
        }
    } else {
        int lfuIndex = findLFUNode(cache);
        if (lfuIndex == -1) return;
        
        string lfuData = get(cache.nodes, lfuIndex);
        stringstream ss(lfuData);
        int oldKey, oldFreq, oldTs;
        string oldValue;
        ss >> oldKey >> oldValue >> oldFreq >> oldTs;
        
        remove(cache.keyTable, oldKey);
        
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
        return "-1";
    }
    
    cache.counter++;
    
    int index = stoi(indexStr);
    string nodeData = get(cache.nodes, index);
    
    stringstream ss(nodeData);
    int oldKey, freq, ts;
    string value;
    ss >> oldKey >> value >> freq >> ts;
    
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
