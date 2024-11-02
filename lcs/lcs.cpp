#include "lcs.h"

using namespace std;

int check(vector<bool> *arr, const string *first, const string *second) {
  bool t = true;
  int i = 0, j = 0, res = 0;
  for (; t && j < second->length() && i < arr->size(); ++i) {
    if (arr->at(i)) {
      res++;
      bool f = false;
      for (; t && j < second->length() && !f; j++) {
        f = first->at(i) == second->at(j);
      }
      if (!f) t = false;
    }
  }
  return (t) ? res : -1;
}

int recursive(vector<bool> *arr, const string *first, const string *second,
              int i) {
  if (i == arr->size()) {
    return check(arr, first, second);
  } else {
    vector<bool> *narr = new vector<bool>(*arr);
    narr->at(i) = true;
    int n1 = recursive(arr, first, second, i + 1),
        n2 = recursive(narr, first, second, i + 1);
    if (n2 > n1) {
      for (int j = i; j < arr->size(); ++j) arr->at(j) = narr->at(j);
    }
    delete narr;
    return max(n1, n2);
  }
}

string brute_force(const string *first, const string *second) {
  string res = "";
  vector<bool> arr(first->length());
  int n = recursive(&arr, first, second, 0);
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i]) res = res + first->at(i);
  }

  return res;
}

string dynAlg(const string *first, const string *second) {
  vector<string *> LCS(first->length() + 1);
  for (int i = 0; i < LCS.size(); i++) {
    LCS[i] = new string[second->length() + 1];
    for (int j = 0; j < second->length() + 1; j++) {
      if (i == 0 || j == 0)
        LCS[i][j] = "";
      else if (first->at(i - 1) == second->at(j - 1))
        LCS[i][j] = LCS[i - 1][j - 1] + first->at(i - 1);
      else
        LCS[i][j] = (LCS[i - 1][j].length() > LCS[i][j - 1].length())
                        ? LCS[i - 1][j]
                        : LCS[i][j - 1];
    }
  }
  string res = "";
  if (first->length() > 0) res = string(LCS[first->length()][second->length()]);
  for (int i = 0; i < LCS.size(); ++i) {
    delete[] LCS[i];
    LCS[i] = nullptr;
  }
  return res;
}

string lcs_slow(const string &first, const string &second) {
  // Return the longest common subsequence (LCS) of the two given strings.
  string res;
  //-------------
  // Brute Force
  res = (first.length() < second.length()) ? brute_force(&first, &second)
                                           : brute_force(&second, &first);
  //-------------
  // Dynamic programming
  // res = (first.length() < second.length()) ? dynAlg(&first, &second)
  //                                         : dynAlg(&second, &first);
  return res;
}

string lcs(const string &first, const string &second) {
  // Return the longest common subsequence (LCS) of the two given strings.
  string res;
  //-------------
  // Brute Force
  // res = (first.length() < second.length()) ? brute_force(&first, &second)
  //                                         : brute_force(&second, &first);
  //-------------
  // Dynamic programming
  res = (first.length() < second.length()) ? dynAlg(&first, &second)
                                           : dynAlg(&second, &first);
  return res;
}
