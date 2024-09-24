#include "convert_str.hpp"

#include <cmath>
#include <iostream>
#include <unordered_map>

#include "share.hpp"

std::string from_dec_to_n_ric(const std::string& num, int r, int precision) {
    if ((std::stod(num) < 0) || (r <= 0) || (precision < -1))
        throw std::logic_error("Arguments are invalid!");

#ifdef DEBUG
    std::cout << "num: " << num << std::endl;
#endif

    std::string res;
    int int_part = std::stod(num);
    double float_part = std::stod(num) - int_part;

#ifdef DEBUG
    std::cout << "\tstart the int part counting\n";
    int k = 0;
#endif

    while (int_part) {
        res = digit_to_char(int_part % r) + res;

#ifdef DEBUG
        std::cout << std::showpoint << "\t#" << ++k << "\t| int part: " << int_part << "\t\t| int part % r: " << int_part % r << "\t=\t" << res << std::endl;
#endif

        int_part /= r;
    }

    if (precision > 0 || precision == -1) res += '.';

#ifdef DEBUG
    std::cout << "\tend the int part counting\n"
              << "\tstart the float part counting\n";
#endif

    int int_rest;
    for (int i = 0; (i < precision) || ((precision == -1) && (float_part != 0.0)); i++) {
#ifdef DEBUG
        std::cout << std::showpoint << "\t#" << i + 1 << "\t| float part: " << float_part;
#endif

        float_part *= r;

        int_rest = (int)float_part;
        float_part -= int_rest;
        res += digit_to_char(int_rest);

#ifdef DEBUG
        std::cout << "\t| " << float_part << "\t| int: " << int_rest << "\t=\t" << res << std::endl;
#endif
    }

#ifdef DEBUG
    std::cout << "\tend the float part counting\n";
#endif

    return res;
}

std::string from_binary_to_hex(const std::string& binary) {
    std::unordered_map<std::string, char> binary_to_hex_map = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};

    int len = binary.length();

    int padding = (4 - (len % 4)) % 4;
    std::string padded = std::string(padding, '0') + binary;

    std::string hex;
    for (size_t i = 0; i < padded.length(); i += 4) {
        std::string four_bits = padded.substr(i, 4);
        hex += binary_to_hex_map[four_bits];
    }

    return hex;
}