#include "opers.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "share.hpp"

std::string sum_strings(const std::string& num1, const std::string& num2, int base, int& extra) {
    std::string result;
    int max_length = std::max(num1.length(), num2.length());

#ifdef DEBUG
    std::cout << "\t| sum strings - num1: " << num1 << "\t| sum strings - num2: " << num2 << std::endl;
#endif

    for (int i = max_length - 1; i >= 0; i--) {
        int digit1 = char_to_digit(num1[i]);
        int digit2 = char_to_digit(num2[i]);

        if (digit1 >= base || digit2 >= base) {
            throw std::invalid_argument("Введена неправильная цифра для выбранного основания!");
        }
        int sum = digit1 + digit2 + extra;
        extra = sum / base;
        result = digit_to_char(sum % base) + result;
    }

    return result;
}

std::string sum(const std::string& num1, const std::string& num2, int base) {
    // разделяем целую и дробную части по точке
    size_t dot1 = num1.find('.');
    size_t dot2 = num2.find('.');

    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string float1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);

    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string float2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);

    // добавим нули справа для дробной части
    int float_length = std::max(float1.length(), float2.length());
    float1.append(float_length - float1.length(), '0');
    float2.append(float_length - float2.length(), '0');

    int extra = 0;
    std::string float_result = sum_strings(float1, float2, base, extra);

    // добавим нули слева для целой части
    int int_length = std::max(int1.length(), int2.length());
    int1.insert(int1.begin(), int_length - int1.length(), '0');
    int2.insert(int2.begin(), int_length - int2.length(), '0');

    std::string int_result = sum_strings(int1, int2, base, extra);

    // если появился новый разряд в числе, добавляем его
    if (extra > 0)
        int_result = digit_to_char(extra) + int_result;

    return int_result + (float_result.empty() ? "" : "." + float_result);
}

std::string subtract_strings(const std::string& num1, const std::string& num2, int base, int& borrow) {
    std::string result;
    int max_length = std::max(num1.length(), num2.length());

#ifdef DEBUG
    std::cout << "\t| subtract strings - num1: " << num1 << "\t| subtract strings - num2: " << num2 << std::endl;
#endif

    for (int i = max_length - 1; i >= 0; i--) {
        int digit1 = char_to_digit(num1[i]);
        int digit2 = char_to_digit(num2[i]);
        if (digit1 >= base || digit2 >= base) {
            throw std::invalid_argument("Введена неправильная цифра для выбранного основания!");
        }

        int sub = digit1 - digit2 - borrow;
        if (sub < 0) {
            sub += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += digit_to_char(sub);
    }

    // удаляем ведущие нули
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// 0 - equal , 1/2 - first greater/less
int compare(std::string& num1, std::string& num2) {
    int res = 0;
    for (size_t i = 0; i < num1.length() && res == 0; ++i) {
        if (num1[i] > num2[i])
            res = 1;
        else if (num1[i] < num2[i])
            res = 2;
    }
    return res;
}

std::string subtract(const std::string& num1, const std::string& num2,
                     int base) {
    bool minus = false;
    // разделяем целую и дробную части по точке
    size_t dot1 = num1.find('.');
    size_t dot2 = num2.find('.');

    std::string int1 = (dot1 == std::string::npos) ? num1 : num1.substr(0, dot1);
    std::string float1 = (dot1 == std::string::npos) ? "" : num1.substr(dot1 + 1);

    std::string int2 = (dot2 == std::string::npos) ? num2 : num2.substr(0, dot2);
    std::string float2 = (dot2 == std::string::npos) ? "" : num2.substr(dot2 + 1);

    // дополняем дробные части нулями справа
    size_t max_float_length = std::max(float1.length(), float2.length());
    float1.append(max_float_length - float1.length(), '0');
    float2.append(max_float_length - float2.length(), '0');
    int borrow = 0;

    // дополняем целые части нулями слева
    size_t max_int_length = std::max(int1.length(), int2.length());
    int1.insert(int1.begin(), max_int_length - int1.length(), '0');
    int2.insert(int2.begin(), max_int_length - int2.length(), '0');

    // вычитаем целые части, учитывая заём из дробной части
    if (compare(int1, int2) == 2 ||
        (compare(int1, int2) == 0 && compare(float1, float2) == 2)) {
        std::swap(int1, int2);
        std::swap(float1, float2);
        minus = true;
    }
    std::string float_result = subtract_strings(float1, float2, base, borrow);
    std::string int_result = subtract_strings(int1, int2, base, borrow);

    return ((minus) ? "-" : "") + int_result +
           (float_result.empty() ? "" : "." + float_result);
}

std::string multiply_strings(const std::string& num1, const std::string& num2, int base) {
#ifdef DEBUG
    std::cout << "multiply strings" << std::endl;
#endif

    std::string result = "0";

#ifdef DEBUG
    std::cout << "\t| num1: " << num1 << "\t| num2: " << num2;
#endif

    // умножаем каждую цифру множителя на множимое
    for (int i = num2.length() - 1; i >= 0; i--) {
        int digit2 = char_to_digit(num2[i]);
        if (digit2 >= base) {
            throw std::invalid_argument("Введена неправильная цифра для выбранного основания!");
        }

        // буфер для промежуточного результата
        std::string current_result;
        int extra = 0;

        // умножаем на текущую цифру множимого
        for (int j = num1.length() - 1; j >= 0; j--) {
            int digit1 = char_to_digit(num1[j]);
            if (digit1 >= base) {
                throw std::invalid_argument("Введена неправильная цифра для выбранного основания!");
            }

            int product = digit1 * digit2 + extra;
            extra = product / base;
            current_result = digit_to_char(product % base) + current_result;
        }

        // если появился новый десяток в числе, добавляем его
        if (extra > 0)
            current_result = digit_to_char(extra) + current_result;

#ifdef DEBUG
        std::cout << "\t| current result: " << current_result;
#endif

        // добавляем нули в конец для текущего результата
        current_result.append(num2.length() - 1 - i, '0');

#ifdef DEBUG
        std::cout << "\t| current result: " << current_result << std::endl;
#endif

        // Складываем текущий результат с общим результатом
        if (!current_result.empty()) {
            int extra1 = 0;
            result.insert(result.begin(), abs(current_result.length() - result.length()), '0');
            result = sum_strings(result, current_result, base, extra1);
            if (extra1 > 0)
                result = digit_to_char(extra1) + result;
        }
    }

    return result;
}

std::string multiply(const std::string& num1, const std::string& num2, int base) {
    // удаляем десятичные точки и определяем количество десятичных знаков
    std::string m1 = num1, m2 = num2;
    int decimal_places = 0;

    size_t dot_pos = m1.find('.');
    if (dot_pos != std::string::npos) {
        decimal_places += m1.length() - dot_pos - 1;
        m1.erase(dot_pos, 1);
    }

    dot_pos = m2.find('.');
    if (dot_pos != std::string::npos) {
        decimal_places += m2.length() - dot_pos - 1;
        m2.erase(dot_pos, 1);
    }

    // умножаем числа без точки
    std::string int_result = multiply_strings(m1, m2, base);
#ifdef DEBUG
    std::cout << "\t| int result: " << int_result;
#endif

    // восстанавливаем десятичную точку
    if (decimal_places > 0) {
        int_result.insert(int_result.end() - decimal_places, '.');
    }

    return int_result.empty() ? "0" : int_result;
}