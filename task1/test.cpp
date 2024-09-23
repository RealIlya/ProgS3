#include "catch_amalgamated.hpp"

#ifdef LEVEL0
#include "level1/convert_str.hpp"
#endif

#ifdef LEVEL1
#include "level1/opers.hpp"
#endif

// #ifdef LEVEL0
TEST_CASE("Level 0 test case") {
    SECTION("From 10 to 2, 8, 16, 3") {
        SECTION("to bin") {
            REQUIRE(from_dec_to_n_ric("457", 2, 0) == "111001001");
            REQUIRE(from_dec_to_n_ric("356", 2, 0) == "101100100");
            REQUIRE(from_dec_to_n_ric("85.71875", 2, 5) == "1010101.10111");
            REQUIRE(from_dec_to_n_ric("688.21875", 2, 5) == "1010110000.00111");
            REQUIRE(from_dec_to_n_ric("724.3125", 2, 4) == "1011010100.0101");
        }
        SECTION("to oct") {
            REQUIRE(from_dec_to_n_ric("457", 8, 0) == "711");
            REQUIRE(from_dec_to_n_ric("356", 8, 0) == "544");
            REQUIRE(from_dec_to_n_ric("85.71875", 8, 2) == "125.56");
            REQUIRE(from_dec_to_n_ric("688.21875", 8, 2) == "1260.16");
            REQUIRE(from_dec_to_n_ric("724.3125", 8, 2) == "1324.24");
        }
        SECTION("to hex") {
            REQUIRE(from_dec_to_n_ric("457", 16, 0) == "1C9");
            REQUIRE(from_dec_to_n_ric("356", 16, 0) == "164");
            REQUIRE(from_dec_to_n_ric("85.71875", 16, 2) == "55.B8");
            REQUIRE(from_dec_to_n_ric("688.21875", 16, 2) == "2B0.38");
            REQUIRE(from_dec_to_n_ric("724.3125", 16, 1) == "2D4.5");
        }
        SECTION("to 3") {
            REQUIRE(from_dec_to_n_ric("123", 3, 0) == "11120");
        }
    }
    SECTION("From 2, 8, 16, 3 to 10") {
        SECTION("from bin") {
            REQUIRE(from_n_ric_to_dec("11000101", 2, 0) == "197");
            REQUIRE(from_n_ric_to_dec("100010001.011", 2, 3) == "273.375");
        }
        SECTION("from oct") {
            REQUIRE(from_n_ric_to_dec("134.22", 8, 5) == "92.28125");
        }
        SECTION("from hex") {
            REQUIRE(from_n_ric_to_dec("51.88", 16, 5) == "81.53125");
        }
        SECTION("from 3") {
            REQUIRE(from_n_ric_to_dec("11120", 3, 0) == "123");
        }
    }
}
// #endif

#ifdef LEVEL1
TEST_CASE("Level 1 test case") {
    SECTION("Sums of 2, 8, 16") {
        SECTION("bin") {
            REQUIRE(sum("101101101.111", "1110011.111", 2) == "111100001.110");
            REQUIRE(subtract("111101001.01", "11111.11", 2) == "111001001.10");

            REQUIRE(sum("111.01", "10.1", 2) == "1001.11");
        }
        SECTION("oct") {
            REQUIRE(sum("566.7", "424.5", 8) == "1213.4");
            REQUIRE(subtract("533.7", "72.3", 8) == "441.4");
        }
        SECTION("hex") {
            REQUIRE(sum("76.8", "BD.A", 16) == "134.2");
            REQUIRE(subtract("176.4", "15A.4", 16) == "1C.0");
        }
        SECTION("3") {
            REQUIRE(sum("122.1", "100.2", 3) == "1000.0");
            REQUIRE(sum("100.002", "1.01", 3) == "101.012");
            REQUIRE(sum("102.022", "1.01", 3) == "110.102");
            REQUIRE(subtract("200.02", "1.1", 3) == "121.22");
        }
        SECTION("4") {
            REQUIRE(sum("233.1", "100.3", 4) == "1000.0");
            REQUIRE(sum("233", "100.3", 4) == "333.3");
        }
        SECTION("32") {
            REQUIRE(sum("AAA", "BBB", 32) == "LLL");
            REQUIRE(sum("AV.2", "B401.003", 32) == "B4B0.203");
        }
    }
    SECTION("Multiply of 2, 8, 16") {
        SECTION("bin") {
            REQUIRE(multiply("101100101.1", "111011001.01", 2) == "101001010011100010.111");
        }
        SECTION("oct") {
            REQUIRE(multiply("540.4", "675.0", 8) == "462276.40");
        }
        SECTION("hex") {
            REQUIRE(multiply("6E.0", "13.2", 16) == "837.C0");
        }
        SECTION("floating") {
            REQUIRE(multiply("0.01", "7", 10) == "0.07");
            REQUIRE(multiply("7", "0.01", 10) == "0.07");
        }
    }
}
#endif

int main(int argc, char* argv[]) {
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}