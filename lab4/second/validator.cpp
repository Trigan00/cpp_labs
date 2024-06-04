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

int getN(std::string str){
    const int bufferSize = 256;
    char input[bufferSize];
    
    // Цикл продолжается, пока не будет введено корректное целое число
    while (true) {
        std::cout << str;
        std::cin.getline(input, bufferSize);
        
        // Проверяем, является ли введенный массив корректным целым числом
        if (isValidInteger(input)) {
            // Преобразуем массив в число и выводим его
            int n;
            std::istringstream(input) >> n;
            if (n > 0) {
                return n;
            }else std::cout << "Ошибка: Должно быть больше 0" << std::endl;
        } else {
            std::cout << "Ошибка! Введите корректное число." << std::endl;
        }
    }
    
}


// int getN(std::string str){
//     while (true){
//         std::cout << str;
//         int n;
//         std::cin >> n; //#TODO Не работает _____1 и 001
//         if (std::cin.peek() != '\n') {
//             std::cout << "Ошибка ввода!" << std::endl;
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
//             continue;
//         }
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         if (n > 0) return n;
//         else std::cout << "Ошибка: Должно быть больше 0" << std::endl;

//     }
// }


