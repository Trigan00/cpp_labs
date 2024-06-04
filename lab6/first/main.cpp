#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <limits>
#include "valid.h"


uint32_t insertByte(uint32_t number, uint8_t byte, unsigned int position) {
    if (position > 31) {
        throw std::out_of_range("Позиция должна быть в диапазоне от 0 до 31");
    }

    unsigned int shift = position % 32;
    uint32_t mask = ~(0xFF << shift);
    uint32_t shiftedByte = static_cast<uint32_t>(byte) << shift;

    if (shift > 24) {
        unsigned int overflowBits = shift - 24;
        uint32_t overflowMask = ~(0xFF >> (8 - overflowBits));
        uint32_t overflowBitsInNumber = byte >> (8 - overflowBits);
        number = (number & overflowMask) | overflowBitsInNumber;
    }

    number = (number & mask) | shiftedByte;
    return number;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Использование: " << argv[0] << " <number> <byte> <position>" << std::endl;
        return 1;
    }

    try {
        std::string numberStr = argv[1];
        std::string byteStr = argv[2];
        std::string positionStr = argv[3];

        if (!isValidHexNumber(numberStr) ) { //isValidDecimalNumber
            throw std::invalid_argument("Некорректное число");
        }
        if (!isValidHexNumber(byteStr) || std::stoul(byteStr, nullptr, 16) > 0xFF) { //isValidDecimalNumber
            throw std::invalid_argument("Некорректный байт");
        }
        if (!isValidDecimalNumber(positionStr)) {
            throw std::invalid_argument("Позиция должна быть допустимым десятичным целым числом.");
        }

        uint32_t number = std::stoul(numberStr, nullptr, 16);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byteStr, nullptr, 16));
        unsigned int position = std::stoul(positionStr);

        uint32_t result = insertByte(number, byte, position);
        std::cout << "Результат: 0x" << std::hex << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
