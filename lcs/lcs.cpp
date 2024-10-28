#include "lcs.h"

using namespace std;

bool contains(string str, string chars) {
  int i = 0, j = 0, c = 0;
  for (; i < chars.length();) {
    for (; j < str.length(); ++j) {
      if (chars[i] == str[j]) {
        c++;
        i++;
      }
    }
  }
}

string brute_force(const string &first, const string &second) {
  set<string> res;
  for (int i = 0; i < first.length(); ++i) {
    string sub;
    for (int j = i; j < first.length(); ++j) {
      int r = 1 + j - i;
      sub = first.substr(i, r);
      bool t;
      if (contains(second, sub))
      // for (int k = 0; k < second.length() + 1 - r; ++k) {
      //   t = true;
      //   for (int l = 0; l < r; ++l) {
      //     if (sub[l] != second[k + l]) t = false;
      //   }
      //   if (t) res.insert(sub);
      // }
    }
  }
  string ret = (res.begin() != res.end()) ? *res.begin() : "";
  for (auto it = res.rbegin(); it != res.rend(); it++)
    if (ret.length() < (*it).length()) ret = *it;
  return ret;
}

string lcs(const string &first, const string &second) {
  // Return the longest common subsequence (LCS) of the two given strings.
  string res;
  // Your implementation here.
  res = (first.length() < second.length()) ? brute_force(first, second)
                                           : brute_force(second, first);
  return res;
}
