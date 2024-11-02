#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"
#include "lcs.h"

int main(int argc, char* argv[]) {
  int result = Catch::Session().run(argc, argv);
  return result;
}

// using namespace std;
//
// int main() {
//   string res = lcs("z1artunx", "yz21rx");
//   cout << res << '\n' << (res == "z1rx");
//   return 0;
// }