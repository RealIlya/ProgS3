#pragma once

#include <string>

std::string floating_to_hex_eight_bytes_number(const std::string &floating);

std::string floating_to_hex_four_bytes_number(const std::string &floating);

std::string hex_eight_bytes_number_to_floating(const std::string &hex);

std::string hex_four_bytes_number_to_floating(const std::string &hex);