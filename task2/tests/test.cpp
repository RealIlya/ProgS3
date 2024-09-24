#include <iostream>

#include "../include/catch_amalgamated.hpp"
#include "../src/converter.hpp"

TEST_CASE("Ex 5") {
    SECTION("To eight-bytes") {
        REQUIRE(floating_to_hex_eight_bytes_number("-474.875") == "C07DAE0000000000");  //
        REQUIRE(floating_to_hex_eight_bytes_number("203.688") == "40697604189374BC");   //
        REQUIRE(floating_to_hex_eight_bytes_number("-53.7344") == "C04ADE00D1B71759");
        REQUIRE(floating_to_hex_eight_bytes_number("345.516") == "4075984189374BC7");  //

        REQUIRE(floating_to_hex_eight_bytes_number("-123.5") == "C05EE00000000000");
    }
    SECTION("To four-bytes") {
        REQUIRE(floating_to_hex_four_bytes_number("-474.875") == "C3ED7000");  //
        REQUIRE(floating_to_hex_four_bytes_number("203.688") == "434BB020");   //
        REQUIRE(floating_to_hex_four_bytes_number("-53.7344") == "C256F006");  //
        REQUIRE(floating_to_hex_four_bytes_number("345.516") == "43ACC20C");   //

        REQUIRE(floating_to_hex_four_bytes_number("-123.5") == "C2F70000");
    }
}

int main(int argc, char* argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
}

// -53.7344
// 1100 0000 0100 1010 1101 1110 0000 0000 1101 0001 1011 0111 0001 0111 0101 1001
// 1100 0000 0100 1010 1101 1110 0000 0100 0001 1000 1001 0011 0111 0100 1011 1100

// 345.516
// 0100000001110101100110000100000110001001001101110100101111000111  4075984189374BC7
// 0100 0000 0111 0101 1001 1000 0100 0001 1000 1001 0011 0111 0100 1011 1100 0110  4075984189374BC616

// four-bytes

// 203.688
// 0100 0011 0100 1011 1011 0000 0010 0000 110001001
// 0100 0011 0100 1011 1011 0000 0010 0000  434BB020

// -53.7344
// 1100 0010 0101 0110 1111 0000 0000 0110
// 1100 0010 0101 0110 1111 0000 0010 0000