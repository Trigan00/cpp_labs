#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <limits>
#include "valid.h"


uint32_t invertBits(uint32_t number, unsigned int p, unsigned int n) {
    if (p >= 32 || n == 0 || p + n > 32) {
        throw std::out_of_range("Недопустимая позиция или длина для инверсии бита.");
    }

    // Создаем маску из n битов
    uint32_t mask = (1U << n) - 1;
    // Сдвигаем маску на p позиций
    mask <<= p;

    // Инвертируем биты с помощью операции XOR
    return number ^ mask;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Использование: " << argv[0] << " <number> <position> <length>" << std::endl;
        return 1;
    }

    try {
        std::string numberStr = argv[1];
        std::string positionStr = argv[2];
        std::string lengthStr = argv[3];

        if (!isValidHexNumber(numberStr)) {
            throw std::invalid_argument("Число должно быть допустимым шестнадцатеричным значением с префиксом 0x.");
        }
        if (!isValidDecimalNumber(positionStr)) {
            throw std::invalid_argument("Позиция должна быть допустимым десятичным целым числом.");
        }
        if (!isValidDecimalNumber(lengthStr)) {
            throw std::invalid_argument("Длина должна быть допустимым десятичным целым числом.");
        }

        uint32_t number = std::stoul(numberStr, nullptr, 16);
        unsigned int position = std::stoul(positionStr);
        unsigned int length = std::stoul(lengthStr);

        uint32_t result = invertBits(number, position, length);
        std::cout << "Результат: 0x" << std::hex << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
