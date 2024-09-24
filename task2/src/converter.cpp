#include "converter.hpp"

#include <cmath>
#include <iostream>

#include "convert_str.hpp"

#define EB 64
#define FB 32

#define EB_ORDER 11
#define FB_ORDER 8

std::string floating_to_hex_n_bytes_number(std::string floating, const int bits_order_count, const int bits_count) {
#ifdef DEBUG
    std::cout << "floating_to_hex_n_bytes_number" << std::endl;
#endif

    char sign = '0';
    if (floating[0] == '-') {
        floating.erase(floating.begin());
        sign = '1';
    }

    std::string number_bin = from_dec_to_n_ric(floating, 2, -1);
    size_t dot_pos = number_bin.find('.');

    size_t order = dot_pos - 1;
    size_t offset_order = order + (size_t(std::pow(2, bits_order_count - 1)) - 1);  // вместо возведения в степень используем битовый сдвиг влево

#ifdef DEBUG
    std::cout << "\t| number bin: " << number_bin << "\t| offset order: " << offset_order << std::endl;
#endif

    std::string offset_order_bin = from_dec_to_n_ric(std::to_string(offset_order), 2, 0);

#ifdef DEBUG
    std::cout << "\t| dot pos: " << dot_pos << "\t| order: " << order << "\t| offset order bin: " << offset_order_bin;
#endif

    std::string mantissa = number_bin.substr(1, dot_pos - 1) + number_bin.substr(dot_pos + 1);
    if (mantissa.length() >= size_t(bits_count))
        mantissa = mantissa.substr(0, bits_count - 1 - bits_order_count);
    else
        mantissa.append(bits_count - 1 - bits_order_count - mantissa.length(), '0');

#ifdef DEBUG
    std::cout << "\t| mantissa: " << mantissa << std::endl;
#endif

    std::string res = sign + offset_order_bin + mantissa;

#ifdef DEBUG
    std::cout << "\t| res: " << res << std::endl;
#endif

    return from_binary_to_hex(res);
}

std::string floating_to_hex_eight_bytes_number(const std::string &floating) {
    return floating_to_hex_n_bytes_number(floating, EB_ORDER, EB);
}

std::string floating_to_hex_four_bytes_number(const std::string &floating) {
    return floating_to_hex_n_bytes_number(floating, FB_ORDER, FB);
}

std::string hex_n_bytes_number_to_floating(std::string hex, const int bits_order_count, const int bits_count) {
#ifdef DEBUG
    std::cout << "hex_n_bytes_number_to_floating" << std::endl;
#endif

    std::string binary = from_hex_to_binary(hex);

#ifdef DEBUG
    std::cout << "\t| binary: " << binary << "\n";
#endif

    bool negative = false;
    if (binary[0] == '1') {
        negative = true;
    }

    std::string offset_order_bin = binary.substr(1, bits_order_count);
    std::string mantissa = binary.substr(bits_order_count + 1);

    size_t offset_order = std::stoull(from_n_ric_to_dec(offset_order_bin, 2, 0));
    long long order = offset_order - (size_t(std::pow(2, bits_order_count - 1)) - 1);
    std::string number_bin = "1" + mantissa.substr(0, offset_order);

    size_t dot_pos;
    if (order < 0LL) {
        dot_pos = 1;
        number_bin.insert(number_bin.begin(), std::abs(static_cast<long long>(order)), '0');

    } else {
        dot_pos = order + 1;
    }
    number_bin.insert(number_bin.begin() + dot_pos, '.');

    number_bin.append(bits_count - number_bin.length(), '0');

#ifdef DEBUG
    std::cout << "\t| offset order: " << offset_order << "\t| offset order bin: " << offset_order_bin << "\t| mantissa: " << mantissa << "\n\t| number bin: " << number_bin << std::endl;
#endif

    std::string res = (negative ? "-" : "") + from_n_ric_to_dec(number_bin, 2, -1);

#ifdef DEBUG
    std::cout << "\t| res: " << res << std::endl;
#endif

    return res;
}

std::string hex_eight_bytes_number_to_floating(const std::string &hex) {
    return hex_n_bytes_number_to_floating(hex, EB_ORDER, EB);
}

std::string hex_four_bytes_number_to_floating(const std::string &hex) {
    return hex_n_bytes_number_to_floating(hex, FB_ORDER, FB);
}