#include <iostream>
#include "hash.h"

// Функция для преобразования числа в римскую цифру
string intToRoman(int num) {
    // Создаем хэш-таблицу для хранения соответствий
    HashTable romanMap;
    initTable(romanMap, 13);
    
    // Заполняем таблицу основными значениями
    insert(romanMap, 1, "I");
    insert(romanMap, 4, "IV");
    insert(romanMap, 5, "V");
    insert(romanMap, 9, "IX");
    insert(romanMap, 10, "X");
    insert(romanMap, 40, "XL");
    insert(romanMap, 50, "L");
    insert(romanMap, 90, "XC");
    insert(romanMap, 100, "C");
    insert(romanMap, 400, "CD");
    insert(romanMap, 500, "D");
    insert(romanMap, 900, "CM");
    insert(romanMap, 1000, "M");
    
    // Массив значений в порядке убывания
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    int size = 13;
    
    string result = "";
    int remaining = num;
    
    // Проходим по всем значениям от большего к меньшему
    for (int i = 0; i < size && remaining > 0; i++) {
        int value = values[i];
        
        // Пока текущее значение помещается в оставшееся число
        while (remaining >= value) {
            // Ищем римскую цифру в хэш-таблице
            string roman = search(romanMap, value);
            if (!roman.empty()) {
                result += roman;
                remaining -= value;
            } else {
                break;
            }
        }
    }
    
    destroyTable(romanMap);
    return result;
}

int main() {
    int number;
    cout << "Введите целое число: ";
    cin >> number;
    
    if (number <= 0) {
        cout << "Число должно быть положительным" << endl;
        return 1;
    }
    
    string roman = intToRoman(number);
    cout << "Римская цифра: " << roman << endl;
    
    return 0;
}
