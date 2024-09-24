#include "convert_str.hpp"

#include <cmath>
#include <iostream>

#include "share.hpp"

std::string from_dec_to_n_ric(std::string num, int r, int precision) {
    if ((std::stod(num) < 0) || (r <= 0) || (precision < -1))
        throw std::logic_error("Arguments are invalid!");

    std::string res;
    int int_part = std::stod(num);
    double float_part = std::stod(num) - int_part;

    while (int_part) {
        res = digit_to_char(int_part % r) + res;
        int_part /= r;
    }

    if (precision > 0 || precision == -1) res += '.';

    int int_rest;
    for (int i = 0; (i < precision) || ((precision == -1) && (float_part != 0.0)); i++) {
        float_part *= r;
#ifdef DEBUG
        std::cout << std::showpoint << "#" << i + 1 << "\t|" << float_part << "\t|";
#endif
        int_rest = (int)float_part;
        float_part -= int_rest;
        res += digit_to_char(int_rest);
#ifdef DEBUG
        std::cout << float_part << "\t| int: " << int_rest << "\t||" << int_rest << "\t" << res << std::endl;
#endif
    }
    return res;
}

std::string from_n_ric_to_dec(std::string num, int r, int precision) {
    if ((std::stod(num) < 0) || (r <= 0) || (precision < -1))
        throw std::logic_error("Arguments are invalid!");

    double res = 0.0;
    size_t b = num.find('.');
    int dot_pos = (int)(b == std::string::npos ? num.length() : b);
#ifdef DEBUG
    std::cout << "dot pos: " << dot_pos << std::endl;
#endif

    for (int i = 0; i < (int)num.length(); i++) {
        if (num[i] == '.') continue;

        int digit = char_to_digit(num[i]);
        int pos = dot_pos - i - (i < dot_pos);
        res += digit * pow(r, pos);
#ifdef DEBUG
        std::cout << "#" << i << "\t| res: " << res << "\t| digit: " << digit << "\t| pos: " << pos << std::endl;
#endif
    }

    std::string res_str = std::to_string(res);

    if (precision == -1) {
        dot_pos = res_str.find('.');
        for (int i = int(res_str.length()) - 1; i >= 0; i--) {
            if (res_str[i] == '0' && res_str[i - 1] != '0' && res_str[i - 1] != '.') {
                std::cout << "\t\t\t\t" << res_str << " " << i << std::endl;
                precision = i - dot_pos - 1;
            }
        }
    }

    char buf[res_str.length() + precision];
    std::sprintf(buf, "%.*f", precision, res);
    return buf;
}