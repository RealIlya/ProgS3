#include <iostream>

#include "convert_str.hpp"
#include "opers.hpp"
#include "share.hpp"

int main() {
    std::string num1, num2;
    char op;
    int base;

    while (true) {
        try {
            std::cout << "Введите операцию \n\t> - из десятичной в r-ичную\n\t< - из r-ичной в десятичную\n\t# - калькулятор\n\te - выйти\n>> ";
            std::cin >> op;
            if (op == '>' || op == '<') {
                std::cout << "Введите число >> ";
                std::cin >> num1;
                std::cout << "Введите основание (до " << BASE << ") >> ";
                std::cin >> base;
                std::cout << "Введите точность округления >> ";
                int precision;
                std::cin >> precision;
                std::cout << "Результат: " << (op == '>' ? from_dec_to_n_ric(num1, base, precision) : from_n_ric_to_dec(num1, base, precision)) << std::endl;
            } else if (op == '#') {
                std::cout << "Введите первое число >> ";
                std::cin >> num1;
                std::cout << "Введите второе число >> ";
                std::cin >> num2;
                std::cout << "Введите основание (до " << BASE << ") >> ";
                std::cin >> base;
                std::cout << "Введите операцию (+,-,*) >> ";
                std::cin >> op;

                switch (op) {
                    case '+':
                        std::cout << "Сумма: " << sum(num1, num2, base);
                        break;
                    case '-':
                        std::cout << "Разность: " << subtract(num1, num2, base);
                        break;
                    case '*':
                        std::cout << "Умножение: " << multiply(num1, num2, base);
                        break;
                    default:
                        break;
                }
                std::cout << std::endl;
            } else if (op == 'e')
                exit(EXIT_SUCCESS);
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}