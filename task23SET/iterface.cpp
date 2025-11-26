#include "hash.h"
#include <iostream>

using namespace std;

int main() {
    HashTable ht;
    initTable(ht);
    
    // Вставка элементов
    insert(ht, 1, "one");
    insert(ht, 2, "two");
    insert(ht, 3, "three");
    insert(ht, 15, "fifteen");
    insert(ht, 25, "twenty-five");
    
    // Поиск элементов
    cout << "Search 2: " << search(ht, 2) << endl;
    cout << "Search 15: " << search(ht, 15) << endl;
    cout << "Search 5: " << search(ht, 5) << endl;
    
    // Удаление элемента
    remove(ht, 2);
    cout << "After removing 2: " << search(ht, 2) << endl;
    
    // Вывод состояния таблицы
    cout << "\nTable contents:" << endl;
    printTable(ht);
    
    cout << "Size: " << getSize(ht) << endl;
    cout << "Is empty: " << (isEmpty(ht) ? "true" : "false") << endl;
    
    // Запись в файл и чтение из файла
    writeToFile(ht, "hash_table.txt");
    
    HashTable ht2;
    initTable(ht2);
    readFromFile(ht2, "hash_table.txt");
    cout << "\nTable from file:" << endl;
    printTable(ht2);
    
    // Очистка
    clearTable(ht);
    destroyTable(ht);
    destroyTable(ht2);
    
    return 0;
}
