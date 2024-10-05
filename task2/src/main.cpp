#include <iostream>

#include "converter.hpp"

int main() {
    int mode;
    std::cout << "Выберите режим (1 - число в 4 байта, 2 - число в 8 байт, 3 - 4 байта в число, 4 - 8 байт в число): ";
    std::cin >> mode;
    std::string number;

    if (mode == 1) {
        std::cout << "Введите число: ";
        std::cin >> number;
        std::cout << floating_to_hex_four_bytes_number(number) << std::endl;
    } else if (mode == 2) {
        std::cout << "Введите число: ";
        std::cin >> number;
        std::cout << floating_to_hex_eight_bytes_number(number) << std::endl;
    } else if (mode == 3) {
        std::cout << "Введите 4-байтное представление числа: ";
        std::cin >> number;
        std::cout << hex_four_bytes_number_to_floating(number) << std::endl;
    } else if (mode == 4) {
        std::cout << "Введите 8-байтное представление числа: ";
        std::cin >> number;
        std::cout << hex_eight_bytes_number_to_floating(number) << std::endl;
    }

    return 0;
}