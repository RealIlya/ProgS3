#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "closest_pair.h"

/*template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}*/

bool cmp(int a, int b) { return a < b; }

std::pair<Point, Point> brute_force_time(const std::vector<Point>& src_arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<Point, Point> result = brute_force(src_arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(end - start);
    std::cout << time.count() << std::endl;
    return result;
}

std::pair<Point, Point> div_conq_time(std::vector<Point>& src_arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<Point, Point> result = divide_and_conquer(src_arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(end - start);
    std::cout << time.count() << std::endl;
    return result;
}

double myrandom(long p) {
    return ((double)std::rand() * RAND_MAX + (double)std::rand()) / p;
}

int main() {
    std::srand(std::time(NULL));
    std::vector<int> sizes = {1000000, 10000000};
    std::cout << "---------------------------------" << std::endl;

    for (int size : sizes) {
        int M = 2000;
        std::vector<double> src_arr(size * 2);
        std::generate(src_arr.begin(), src_arr.end(), [=]() {
            return myrandom(M);
        });  // заполнение элементов для поиска
        std::vector<Point> arr(size);
        for (int i = 0; i < size; ++i)
            arr[i] = Point(src_arr[i], src_arr[i + size]);
        // std::cout << "Array size: " << size << std::endl;
        std::cout << std::fixed << std::setprecision(8);
        // for (auto i : arr) std::cout << i << ' ';
        // std::cout << '\n';
        std::pair<Point, Point> bres = brute_force_time(arr);
        // std::pair<Point, Point> dres = div_conq_time(arr);
        // bool eq = false;
        // eq = (bres.first == dres.first && bres.second == dres.second) ||
        //      (bres.first == dres.second && bres.second == dres.first);
        // std::cout << "OK: " << eq << std::endl;
        // std::cout << "---------------------------------" << std::endl;
    }

    return 0;
}