#include "converter.hpp"

#include <cmath>
#include <iostream>

#include "convert_str.hpp"

#define EB 64
#define FB 32

#define EB_ORDER 11
#define FB_ORDER 8

std::string floating_to_hex_n_bytes_number(std::string number, const int bites_order_count, const int bits_count) {
#ifdef DEBUG
    std::cout << "floating_to_hex_eight_bytes_number" << std::endl;
#endif

    char sign = '0';
    if (number[0] == '-') {
        number.erase(number.begin());
        sign = '1';
    }

    std::string number_bin = from_dec_to_n_ric(number, 2, -1);
    size_t dot_pos = number_bin.find('.');

    size_t order = dot_pos - 1;
    size_t offset_order = order + (int(std::pow(2, bites_order_count - 1)) - 1);  // вместо возведения в степень используем битовый сдвиг влево

#ifdef DEBUG
    std::cout << "\t| offset order: " << offset_order << std::endl;
#endif

    std::string offset_order_bin = from_dec_to_n_ric(std::to_string(offset_order), 2, 0);

#ifdef DEBUG
    std::cout << "\t| dot pos: " << dot_pos << "\t| order: " << order << "\t| offset order bin: " << offset_order_bin;
#endif

    std::string mantissa = number_bin.substr(1, dot_pos - 1) + number_bin.substr(dot_pos + 1);
    if (mantissa.length() >= size_t(bits_count)) {
        mantissa = mantissa.substr(0, bits_count - 1 - bites_order_count);
    } else
        mantissa.append(bits_count - 1 - bites_order_count - mantissa.length(), '0');

#ifdef DEBUG
    std::cout << "\t| mantissa: " << mantissa;
#endif

    std::string res = sign + offset_order_bin + mantissa;

#ifdef DEBUG
    std::cout << "\n\t| res: " << res << std::endl;
#endif

    return from_binary_to_hex(res);
}

std::string floating_to_hex_eight_bytes_number(const std::string &number) {
    return floating_to_hex_n_bytes_number(number, EB_ORDER, EB);
}

std::string floating_to_hex_four_bytes_number(const std::string &number) {
    return floating_to_hex_n_bytes_number(number, FB_ORDER, FB);
}

std::string hex_eight_bytes_number_to_floating(std::string number);

std::string hex_four_bytes_number_to_floating(std::string number);