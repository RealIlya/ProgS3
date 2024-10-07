#include "convert_str.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
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

    if (res.empty()) res = "0";

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

std::string from_n_ric_to_dec(std::string num, int r, int precision) {
    if ((std::stod(num) < 0) || (r <= 0) || (precision < -1))
        throw std::logic_error("Arguments are invalid!");

    double res = 0.0;
    size_t b = num.find('.');
    int dot_pos = (int)(b == std::string::npos ? num.length() : b);

#ifdef DEBUG
    std::cout << "dot pos: " << dot_pos << std::setprecision(20) << std::endl;
#endif

    for (int i = 0; i < (int)num.length(); i++) {
        if (num[i] == '.') continue;

        int digit = char_to_digit(num[i]);
        int pos = dot_pos - i - (i < dot_pos);
        res += digit * std::pow(r, pos);
#ifdef DEBUG
        std::cout << "#" << i << "\t| res: " << res << "\t| digit: " << digit << "\t| pos: " << pos << std::endl;
#endif
    }

#ifdef DEBUG
    std::cout << "\t| precision: " << precision << std::endl;
#endif

    std::string res_str;
    std::ostringstream oss;
    oss << std::fixed;
    if (precision == -1) {
        oss << std::setprecision(std::numeric_limits<double>::digits10 + 1) << res;  // Устанавливаем максимальную точность
        std::string str = oss.str();                                                 // Получаем строку

        // Удаляем лишние нули в конце
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        // Удаляем точку, если она осталась в конце
        if (str.back() == '.') {
            str.pop_back();
        }
        res_str = str;
    } else {
        oss << std::setprecision(precision) << res;
        res_str = oss.str();
    }

#ifdef DEBUG
    std::cout << "\t| res str: " << res_str << std::endl;
#endif

    return res_str;
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

std::string from_hex_to_binary(const std::string& hex) {
    std::unordered_map<char, std::string> hex_to_binary_map = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

    std::string binary;
    for (char c : hex)
        binary += hex_to_binary_map[std::toupper(c)];

    return binary;
}