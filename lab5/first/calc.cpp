#include <iostream>
#include <fstream>
#include "valid.h"

bool checkCondition(const std::string& str, int i, int j) {
    return (i < j && str[i] == str[i+1] && str[j] == str[j+1]);
}

int checkAll(const std::string& str, const char* outputFile){
    int spaceCount {0};

    bool isU {false};

    bool isS {false};
    bool isH {false};
    bool isI {false};
    bool isN {false};
    bool isA {false};

    bool isNO {false};

    bool isSameChar {false};

    bool isIJ {false};

    int i {0};
    for (char c : str) {
        if (c == '!') break;

        if (c == ' ') spaceCount++;

        if (c == 'u') isU = true;

        if (c == 's') isS = true;
        if (c == 'h') isH = true;
        if (c == 'i') isI = true;
        if (c == 'n') isN = true;
        if (c == 'a') isA = true;

        if ((str[i] == 'n' && str[i+1] == 'o') ||
            (str[i] == 'o' && str[i+1] == 'n')) {
            isNO = true;
        }

        if (str[i] == str[i+1]) isSameChar = true;

        i++;
        
    }

    for (int i = 1; i < str.length() - 1; ++i) {
        if (str[i] == '!') break;
        for (int j = i + 2; j < str.length() - 1; ++j) {
            if (str[j] == '!') break;
            if (checkCondition(str, i, j)) {
                isIJ = true;
            }
        }
    }

    while (true)
    {
        int outputDestination = getN("Куда вы хотите записать информацию? Консоль - 1, файл - 2: ");
        if (outputDestination == 2) {
            std::string filePath;
            std::cout << "Укажите файл для вывода данных (нажмите Enter для использования " << outputFile << "): ";
            getline(std::cin, filePath);

            if (filePath.empty()) {
                filePath = outputFile;
            }
            std::ofstream file(filePath);

            if (!file.is_open()) {
                std::cerr << "Ошибка: Файл не найден или не удалось открыть файл." << std::endl;
                continue;
            }
            
            file << "Кол-во пробелов: " << spaceCount << std::endl;
            file << "Есть u: " << (isU ? "Да" : "Нет") << std::endl;
            file << "Имеются все буквы входящие в слово shina: " << (isS && isH && isI && isN && isA ? "Да" : "Нет") << std::endl;
            file << "Имеется пара соседствующих букв no или on: " << (isNO ? "Да" : "Нет") << std::endl;
            file << "Имеется пара соседствующих одинаковых символов: " << (isSameChar ? "Да" : "Нет") << std::endl;
            file << "Существуют такие i и j: " << (isIJ ? "Да" : "Нет") << std::endl;

            file.close();
            std::cout << "Информация записана в файл" << std::endl;
            break;
        } else if (outputDestination == 1) {
            std::cout << "Кол-во пробелов: " << spaceCount << std::endl;
            std::cout << "Есть u: " << (isU ? "Да" : "Нет") << std::endl;
            std::cout << "Имеются все буквы входящие в слово shina: " << (isS && isH && isI && isN && isA ? "Да" : "Нет") << std::endl;
            std::cout << "Имеется пара соседствующих букв no или on: " << (isNO ? "Да" : "Нет") << std::endl;
            std::cout << "Имеется пара соседствующих одинаковых символов: " << (isSameChar ? "Да" : "Нет") << std::endl;
            std::cout << "Существуют такие i и j: " << (isIJ ? "Да" : "Нет") << std::endl;
            break;
        } else {
            std::cout << "Неверное место назначения. Введите 1 или 2.\n";
            continue;
        }
    }
    
    return 0;
}


int RWFile(const char* inputFile, const char* outputFile) {

    std::string filePath;
    std::cout << "Укажите файл для ввода исходных данных для работы программы (нажмите Enter для использования " << inputFile << "): ";
    getline(std::cin, filePath);

    if (filePath.empty()) {
        filePath = inputFile;
    }
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Ошибка: Файл не найден или не удалось открыть файл." << std::endl;
        return 1;
    }

    std::string line;
    std::string resultLine;
    bool nonEmptyLineFound {false};
    bool isLine {false};

    while (std::getline(file, line)) {
        if (!line.empty()) {
            if (isLine){
                std::cout << "Ошибка: Введите одну строку" << std::endl;
                exit(1);
            }
            resultLine = line;
            nonEmptyLineFound = true;
            isLine = true;
        }
    }

    if (!nonEmptyLineFound) {
        std::cerr << "Ошибка: все строки в файле пустые!" << std::endl;
        exit(1);
    }

    checkAll(resultLine, outputFile);
    

    file.close();
    
    // output(outputFile, numCols, means);
    

    return 0;
}

int RWConsole(const char* outputFile){
    
    std::string userInput;

    while (true) {
        std::cout << "Введите строку: ";
        std::getline(std::cin, userInput);

        if (userInput.empty()) {
            std::cout << "Ошибка: строка не может быть пустой." << std::endl;
            continue;
        }
        break;
    }

    checkAll(userInput, outputFile);

    return 0;
}
