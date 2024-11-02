#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#include "activities.h"

template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}

void fast(const std::vector<Activity> &vec) {
  double time = measure_time([&]() { get_max_activities(vec); });
  std::cout << "fast: " << time << '\n';
}

void slow(const std::vector<Activity> &vec) {
  double time = measure_time([&]() { get_max_activities_slow(vec); });
  std::cout << "slow: " << time << '\n';
}

Activity myrandom() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 10000);
  int n = dist(gen);
  std::uniform_int_distribution<> t(0, 50);
  return Activity(n, n + t(gen));
}

int main() {
  std::vector<unsigned int> sizes = {5, 10, 15, 20, 25};
  std::cout << "---------------------------------" << std::endl;

  for (unsigned int size : sizes) {
    std::vector<Activity> src(size);
    std::generate(src.begin(), src.end(), [=]() {
      return myrandom();
    });  // заполнение элементов для поиска
    std::cout << "Size: " << size << '\n';
    std::cout << std::fixed << std::setprecision(8);
    slow(src);
    fast(src);
    //  for (auto i : src) std::cout << '{' << i.start << ' ' << i.finish << "}
    //  "; std::cout << '\n';
    std::cout << "---------------------------------" << std::endl;
  }

  return 0;
}