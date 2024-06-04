#include <cstdint>
#include <stdexcept>

bool isValidHexNumber(const std::string& str) {
    if(str.length() <= 2) return false;
    if (str.empty() || (str.length() > 2 && str.substr(0, 2) != "0x" && str.substr(0, 2) != "0X")) {
        return false;
    }
    for (size_t i = 2; i < str.length(); ++i) {
        if (!isxdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidDecimalNumber(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}