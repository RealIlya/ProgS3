#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>

#include "shortest_path.h"

template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}

void dijkstra_time(const Graph &graph, int start, int end) {
  std::vector<int> res;
  double time = measure_time([&]() { res = shortest_path(graph, start, end); });
  std::cout << "dikstra time: " << time << '\n';
}

int getRandNum(int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, max);
  return dist(gen);
}

double getRandD(double max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0, max);
  return dist(gen);
}

Graph randomGraph(int n_vertices) {
  Graph graph;
  for (int i = 0; i < n_vertices; i++) {
    int n = getRandNum(n_vertices);
    if (n == 0) n = 1;
    for (int j = 0; j < i % n; j++) {
      int r = getRandNum(n_vertices);
      while (r == i) r = getRandNum(n_vertices);
      graph.add_edge(i, r, getRandD(20));
    }
  }
  std::set<int> group;
  std::set<int> passed;
  group.insert(0);
  for (int n = 0; n < n_vertices; n++) {
    for (auto i : group)
      for (auto j : graph.get_adjacent_vertices(i))
        if (passed.find(j) == passed.end()) {
          group.insert(j);
          passed.insert(j);
        }
  }
  while (group.size() < n_vertices) {
    for (int i = 0; i < n_vertices; i++) {
      if (group.find(i) == group.end()) {
        graph.add_edge(0, i, getRandD(20));
        group.insert(i);
      }
    }
  }
  return graph;
}

int main() {
  std::vector<int> sizes = {10, 20, 100, 200, 1000, 2000, 10000, 20000};
  std::cout << "---------------------------------" << std::endl;
  for (int size : sizes) {
    Graph graph = randomGraph(size);
    std::cout << "Size:  " << size << '\n';
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "1)";
    dijkstra_time(graph, getRandNum(size), getRandNum(size));
    std::cout << "2)";
    dijkstra_time(graph, getRandNum(size), getRandNum(size));
    std::cout << "3)";
    dijkstra_time(graph, getRandNum(size), getRandNum(size));
    std::cout << "---------------------------------" << std::endl;
  }
  return 0;
}