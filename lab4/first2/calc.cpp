#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>
#include "valid.h"
#include <cstring>

int output(const char* outputFile, char* line, int n){
    while (true)
    {
        int outputDestination = getN("Куда вы хотите записать информацию? Консоль - 1, файл - 2: ");
        if (outputDestination == 2) {
            std::ofstream outFile(outputFile);

            if (!outFile.is_open()) {
                std::cout << "Ошибка открытия файла.\n";
                return 1;
            }

            for (int i = 0; i < n; ++i){
                outFile << line[i];
            }
            outFile.close();
            std::cout << "Информация записана в файл" << std::endl;
            break;
        } else if (outputDestination == 1) {
            std::cout << "Результат выполнения программы:\n";
            for (int i = 0; i < n; ++i){
                std::cout << line[i];
            }
            std::cout << std::endl;
            break;
        } else {
            std::cout << "Неверное место назначения. Введите 1 или 2.\n";
            continue;
        }
    }
    return 0;
}

int RWFile(const char* inputFile, const char* outputFile) {

    std::ifstream inFile(inputFile);

    if (!inFile.is_open()) {
        std::cout << "Ошибка открытия файла.\n";
        return 1;
    }

    bool isEmpty {true}; 
    char* buffer = new char[bufferSize];
    bool isLine {false};
    
    int pos {0};
    char* result;

    while (inFile.getline(buffer, bufferSize)) {
        if (buffer[0] != '\0') {
            if (isLine){
                std::cout << "Ошибка: Введите одну строку" << std::endl;
                exit(1);
            }
            isEmpty = false;
            int fileSize = strlen(buffer);
            isLine = true;

            result = new char[fileSize];
            bool insideBrackets {false};
            for (int i = 0; i < fileSize; ++i) {
                if (insideBrackets && buffer[i] == '('){
                    std::cout << "Внутри скобок не должно быть скобок" << std::endl;
                    exit(1);
                }
                if (buffer[i] == '(') {
                    insideBrackets = true;
                } else if (buffer[i] == ')') {
                    insideBrackets = false;
                } else if (!insideBrackets) {
                    result[pos++] = buffer[i];
                }
            }
        }
    }

    inFile.close();
    if (isEmpty) {
        std::cout << "Ошибка: Файл не может быть пустым." << std::endl;
        exit(1);
    }

    output(outputFile, result, pos);

    delete buffer;

    return 0;
}

int RWConsole(const char* outputFile){
    int capacity = 0;
    int length = 0;
    char* buffer = new char[capacity];

    char ch;
    std::cout << "Введите строку: ";
    while (std::cin.get(ch) && ch != '\n') {
        buffer[length++] = ch;
        if (length == capacity) {
            capacity *= 2;
            char* temp = new char[capacity];
            std::copy(buffer, buffer + length, temp);
            delete[] buffer;
            buffer = temp;
        }
    }
    buffer[length] = '\0';

    if (length == 0){
        std::cout << "Ошибка: строка не может быть пустой." << std::endl;
        exit(1);
    }    

    char* result = new char[length];;
    int pos {0};
    bool insideBrackets {false};
    for (int i = 0; i < length; ++i) {
        if (insideBrackets && buffer[i] == '('){
            std::cout << "Внутри скобок не должно быть скобок" << std::endl;
            exit(1);
        }
        if (buffer[i] == '(') {
            insideBrackets = true;
        } else if (buffer[i] == ')') {
            insideBrackets = false;
        } else if (!insideBrackets) {
            result[pos++] = buffer[i];
        }
    }
    output(outputFile, result, pos);

    delete buffer;

    return 0;
}

