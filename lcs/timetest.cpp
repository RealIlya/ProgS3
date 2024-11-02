#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#include "lcs.h"

template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}

std::string fast_lcs_time(const std::string& first, const std::string& second) {
  std::string res = "";
  double time = measure_time([&]() { res = lcs(first, second); });
  std::cout << "fast lcs: " << time << '\n';
  return res;
}

std::string brute_force_lcs_time(const std::string& first,
                                 const std::string& second) {
  std::string res = "";
  double time = measure_time([&]() { res = lcs_slow(first, second); });
  std::cout << "slow lcs: " << time << '\n';
  return res;
}

unsigned long myrandom() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> t(0, 1);
  int n1 = 65, n2 = 90;
  if (t(gen) == 1) n1 += 32, n2 += 32;
  std::uniform_int_distribution<> dist(n1, n2);
  return dist(gen);
}

int main() {
  std::vector<std::pair<size_t, size_t>> sizes = {
      {10, 10}, {10, 100}, {10, 1000}, {10, 10000}, {15, 15},
      {20, 20}, {25, 25},  {25, 100},  {25, 10000}};
  std::cout << "---------------------------------" << std::endl;

  for (std::pair<int, int> size : sizes) {
    std::string first(size.first, '1');
    std::generate(first.begin(), first.end(), [=]() {
      return myrandom();
    });  // заполнение элементов для поиска
    std::string second(size.second, '2');
    std::generate(second.begin(), second.end(), [=]() {
      return myrandom();
    });  // заполнение элементов для поиска
    std::cout << "First size:  " << size.first << '\n';
    std::cout << "Second size: " << size.second << '\n';
    std::cout << std::fixed << std::setprecision(8);
    std::string fans = brute_force_lcs_time(first, second);
    std::string sans = fast_lcs_time(first, second);
    bool eq = fans.length() == sans.length();
    for (int i = 0; eq && i < fans.length(); ++i) eq = fans[i] == sans[i];
    std::cout << "Equal answer: " << eq << '\n';
    std::cout << "---------------------------------" << std::endl;
  }

  return 0;
}