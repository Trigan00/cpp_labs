#include <iostream>
#include "valid.h"
#include "main.h"

int runTask(int* isRepeat){
    bool* localRepeat = new (std::nothrow) bool {false};
    while (true)
    {
        int inputSource = getN("Откуда вы хотите считать информацию? Консоль - 1, файл - 2: ");
        if (inputSource == 2) {
            RWFile(inputFile, outputFile);
            break;
        } else if (inputSource == 1) {
            RWConsole(outputFile);
            *localRepeat = true;
            break;
        } else {
            std::cout << "Неверный источник. Введите 1 или 2.\n";
            continue;
        }
    }


    
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
