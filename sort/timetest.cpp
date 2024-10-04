#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "sort.h"

template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}

bool cmp(int a, int b) { return a < b; }

void std_qsort_time(const std::vector<int>& src_arr) {
  std::vector<int> sorted_arr = src_arr;

  double time = measure_time(
      [&]() { std::sort(sorted_arr.begin(), sorted_arr.end(), cmp); });
  std::cout << "std quicksort: " << time << std::endl;
}

void our_qsort_time(const std::vector<int>& src_arr) {
  std::vector<int> sorted_arr = src_arr;

  double time = measure_time([&]() { sort(sorted_arr); });
  std::cout << "our quicksort: " << time << std::endl;
}

unsigned long myrandom(long p) {
  return long(std::rand() * RAND_MAX + std::rand()) % p;
}

int main() {
  std::srand(std::time(NULL));
  std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
  std::cout << "---------------------------------" << std::endl;

  for (int size : sizes) {
    int M = 20000000;
    std::vector<int> src_arr(size);
    std::generate(src_arr.begin(), src_arr.end(), [=]() {
      return myrandom(M);
    });  // заполнение элементов для поиска

    std::cout << "Array size: " << size << std::endl;
    std::cout << std::fixed << std::setprecision(8);
    std::vector<int> std_arr = src_arr;
    std::vector<int> our_arr = src_arr;
    std_qsort_time(std_arr);
    our_qsort_time(our_arr);
    bool eq = true;
    for (int i = 0; eq && i < size; ++i) eq = std_arr[i] == our_arr[i];
    std::cout << "Sorted: " << eq;
    std::cout << "---------------------------------" << std::endl;
  }

  return 0;
}