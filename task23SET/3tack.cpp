#include "set.h"
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int intersectionSize(Set &a, Set &b) {
    int count = 0;
    for (int i = 0; i < a.capacity; i++) {
        if (a.table[i].occupied && !a.table[i].deleted) {
            if (contains(b, a.table[i].key)) {
                count++;
            }
        }
    }
    return count;
}

void createSetFromArray(Set &s, int *elements, int count) {
    initSet(s);
    for (int i = 0; i < count; i++) {
        insert(s, elements[i]);
    }
}

void printSetElements(Set &s) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < s.capacity; i++) {
        if (s.table[i].occupied && !s.table[i].deleted) {
            if (!first) cout << ", ";
            cout << s.table[i].key;
            first = false;
        }
    }
    cout << "}";
}

int main() {
    const int MAX_SETS = 100;
    const int MAX_ELEMENTS = 1000;
    
    Set *sets = new Set[MAX_SETS];
    int **subsets = new int*[MAX_SETS];
    int *subsetSizes = new int[MAX_SETS];
    int setCount = 0;
    
    string line;
    
    cout << "Введите множества (каждое множество на новой строке, числа через пробел):" << endl;
    cout << "Для завершения ввода введите пустую строку" << endl;
    
    // Чтение входных данных
    while (getline(cin, line)) {
        if (line.empty()) break;
        if (setCount >= MAX_SETS) {
            cout << "Достигнуто максимальное количество множеств (" << MAX_SETS << ")" << endl;
            break;
        }
        
        subsets[setCount] = new int[MAX_ELEMENTS];
        int elementCount = 0;
        stringstream ss(line);
        int num;
        
        while (ss >> num && elementCount < MAX_ELEMENTS) {
            subsets[setCount][elementCount] = num;
            elementCount++;
        }
        
        subsetSizes[setCount] = elementCount;
        setCount++;
    }
    
    if (setCount < 2) {
        cout << "Недостаточно множеств для сравнения" << endl;
        
        // Освобождение памяти
        for (int i = 0; i < setCount; i++) {
            delete[] subsets[i];
        }
        delete[] subsets;
        delete[] subsetSizes;
        delete[] sets;
        return 0;
    }
    
    // Создаем множества
    for (int i = 0; i < setCount; i++) {
        createSetFromArray(sets[i], subsets[i], subsetSizes[i]);
    }
    
    // Ищем пару с максимальным пересечением
    int maxIntersection = -1;
    int set1_idx = -1, set2_idx = -1;
    
    for (int i = 0; i < setCount; i++) {
        for (int j = i + 1; j < setCount; j++) {
            int intersection = intersectionSize(sets[i], sets[j]);
            
            if (intersection > maxIntersection) {
                maxIntersection = intersection;
                set1_idx = i;
                set2_idx = j;
            }
        }
    }
    
    // Выводим результат
    cout << "\nРезультат:" << endl;
    cout << "Множества с максимальным пересечением:" << endl;
    cout << "Первое множество: ";
    printSetElements(sets[set1_idx]);
    cout << "\nВторое множество: ";
    printSetElements(sets[set2_idx]);
    cout << "\nКоличество общих элементов: " << maxIntersection << endl;
    
    // Освобождаем память
    for (int i = 0; i < setCount; i++) {
        destroySet(sets[i]);
        delete[] subsets[i];
    }
    delete[] subsets;
    delete[] subsetSizes;
    delete[] sets;
    
    return 0;
}
