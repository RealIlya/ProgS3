#include "share.hpp"

#include <iostream>
#include <sstream>

int char_to_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    std::stringstream buf;
    buf << "Введен неправильный символ для преобразования в цифру!" << " " << c;
    throw std::invalid_argument(buf.str());
}

char digit_to_char(int digit) {
    if (digit >= 0 && digit <= 9) return '0' + digit;
    if (digit >= 10 && digit < BASE) return 'A' + (digit - 10);
    std::stringstream buf;
    buf << "Введена неправильная цифра для преобразования в символ!" << " " << digit;
    throw std::invalid_argument(buf.str());
}
