#include <iostream>
#include <sstream>

bool isValidInteger(const char* input) {
    // Проверяем каждый символ в массиве
    for (const char* ptr = input; *ptr != '\0'; ++ptr) {
        // Если текущий символ не является цифрой
        if (!isdigit(*ptr)) {
            return false;
        }
    }
    
    // Преобразуем массив в число и обратно, чтобы проверить, нет ли в нем лишних символов (например, нулей перед числом)
    std::istringstream iss(input);
    int number;
    iss >> number;
    std::ostringstream oss;
    oss << number;
    return oss.str() == input; // Если строка из числа равна введенной строке, значит в строке нет лишних символов
}

int getN(const char* str){
    const int bufferSize = 256;
    char input[bufferSize];
    
    // Цикл продолжается, пока не будет введено корректное целое число
    while (true) {
        std::cout << str;
        std::cin.getline(input, bufferSize);
        
        // Проверяем, является ли введенный массив корректным целым числом
        if (isValidInteger(input)) {
            // Преобразуем массив в число и выводим его
            int number;
            std::istringstream(input) >> number;
            if (number >= 0) return number;
        } else {
            std::cout << "Ошибка! Введите корректное целое число." << std::endl;
        }
    }
    
}
