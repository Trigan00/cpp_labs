#include <iostream>
// #include <algorithm>
#include "files.h"
#include "valid.h"
#include "inout.h"

int runTask(int* isRepeat){
    char* readData {nullptr};
    int fileSize;
    bool* localRepeat = new (std::nothrow) bool {false};

    while (true)
    {
        int inputSource = getN("Откуда вы хотите считать информацию? Консоль - 1, файл - 2: ");
        if (inputSource == 2) {
            readFromFile(inputFile, readData, fileSize);
            break;
        } else if (inputSource == 1) {
            readFromConsole(readData, fileSize);
            *localRepeat = true;
            break;
        } else {
            std::cout << "Неверный источник. Введите 1 или 2.\n";
            continue;
        }
    }

    bool insideBrackets {false};
    int pos {0};
    char* result = new char[fileSize];

    for (int i = 0; i < fileSize; ++i) {
        if (readData[i] == '(') {
            insideBrackets = true;
        } else if (readData[i] == ')') {
            insideBrackets = false;
        } else if (!insideBrackets) {
            result[pos++] = readData[i];
        }
    }

    
    while (true)
    {
        int outputDestination = getN("Куда вы хотите записать информацию? Консоль - 1, файл - 2: ");
        if (outputDestination == 2) {
            writeToFile(outputFile, result, pos);
            break;
        } else if (outputDestination == 1) {
            writeToConsole(result, pos);
            break;
        } else {
            std::cout << "Неверное место назначения. Введите 1 или 2.\n";
            continue;
        }
    }

    delete[] readData;
    delete[] result;
    // delete[] output;
    
    if (*localRepeat){
        while (true)
        {
            int n = getN("Хотите повторить? Да - 1, Нет - 2: ");
            if(n == 1) {
                *isRepeat = 1;
                break;
            }
            else if(n == 2){
                *isRepeat = 2;
                break;
            }
            else {
                std::cout << "Ошибка ввода. Введите 1 или 2.\n";
                continue;
            }
        }
        
    }
    else *isRepeat = 2;
    
    delete localRepeat;
    return 0;
}

int main() {
    int* isRepeat;
    do
    {
        runTask(isRepeat);
    } while (*isRepeat == 1);
    isRepeat = nullptr;
    return 0;
}
