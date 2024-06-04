#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "valid.h"

int readFromFile(const char* filename) {
    std::ifstream inputFile(filename); // Открываем файл для чтения
    if (!inputFile) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return -1;
    }

    // int lineCount = 0;
    // char ch;
    // while (inputFile.get(ch)) {
    //     if (ch == '\n') {
    //         ++lineCount;
    //     }
    // }

    // if (ch != '\n' && lineCount > 0) {
    //     ++lineCount;
    // }

    // if (lineCount != 1){
    //     std::cout << "Ошибка: В файле должна быть одна строка." << lineCount << std::endl;
    //     return -1;
    // } #TODO если больше одной строки тоже работает 

    const int bufferSize = 256;
    char buffer[bufferSize];
    
    inputFile.getline(buffer, bufferSize); // Считываем строку из файла

    inputFile.close(); // Закрываем файл

    if (isValidInteger(buffer)) {
            // Преобразуем массив в число и выводим его
            int n;
            std::istringstream(buffer) >> n;
            if (n > 0) {
                return n;
            }
            else std::cout << "Ошибка: Должно быть больше 0" << std::endl;
    } else {
        std::cout << "Ошибка! Введите корректное целое число." << std::endl;
    }

    return -1;
}


void readFromConsole(int* number) {
    int n = getN("Введитие натуральное число: ");
    *number = n;
}

void writeToConsole(const int number) {
    std::cout << "Результат выполнения программы: " << number << std::endl;
}

int writeToFile(const char* filename, const int number) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return 1;
    }

    outFile << number;

    outFile.close();

    return 0;
}