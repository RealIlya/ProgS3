#pragma once

#include <iostream>

std::string from_dec_to_n_ric(const std::string& num, int r, int precision);

std::string from_n_ric_to_dec(std::string num, int r, int precision);

std::string from_binary_to_hex(const std::string& binary);

std::string from_hex_to_binary(const std::string& hex);