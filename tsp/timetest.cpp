#include "tsp.h"

template <typename Func>
double measure_time(Func func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double>(end - start);
  return time.count();
}

double bru_time(const Graph &graph) {
  std::vector<int> res;
  double time = measure_time([&]() { res = TSP_brute_force(graph, 0); });
  std::cout << "brutsp time: " << time;
  return Length(graph, res);
}

double gre_time(const Graph &graph) {
  std::vector<int> res;
  double time = measure_time([&]() { res = TSP_Greedy(graph, 0); });
  std::cout << "gretsp time: " << time;
  return Length(graph, res);
}

double bnb_time(const Graph &graph) {
  std::vector<int> res;
  double time = measure_time([&]() { res = TSP_BnB(graph, 0); });
  std::cout << "bnbtsp time: " << time;
  return Length(graph, res);
}

double loc_time(const Graph &graph) {
  std::vector<int> res;
  double time = measure_time([&]() { res = TSP_LS(graph); });
  std::cout << "loctsp time: " << time;
  return Length(graph, res);
}

double gen_time(const Graph &graph) {
  std::vector<int> res;
  // Параметры алгоритма
  int P = 100;  // Число хромосом в поколении
  int N = 25;   // Число родителей для скрещивания
  int MaxGen = 100;  // Максимальное число генераций
  int MaxIt = 1;  // Максимальное число итераций 2opt
  double Pm = 0.25;  // Вероятность мутации
  double time =
      measure_time([&]() { res = TSP_GA(graph, P, N, Pm, MaxGen, MaxIt); });
  std::cout << "gentsp time: " << time;
  return Length(graph, res);
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
    for (int j = 0; j < i % 5; j++) {
      int r = getRandNum(n_vertices);
      while (r == i) r = getRandNum(n_vertices);
      graph.add_edge(i, r, getRandD(20));
    }
  }
  int count_edges = 0;
  for (auto i : graph.get_vertices()) {
    count_edges += graph.get_adjacent_vertices(i).size();
  }
  if (count_edges < n_vertices * (n_vertices - 1) / 2) {
    for (int i = 0; i < n_vertices - 1; i++) {
      for (int j = i + 1; j < n_vertices; j++) {
        if (!graph.has_edge(i, j)) graph.add_edge(i, j, getRandD(20));
      }
    }
  }
  std::vector<int> vetrices = graph.get_vertices();
  for (auto &i : vetrices) {
    auto edges = graph.get_adjacent_edges(i);
    for (auto &j : edges) {
      graph.add_edge(j.first, i, j.second);
    }
  }
  /*std::set<int> group;
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
  }*/
  return graph;
}

// Генератор случайного числа в диапазоне [min, max]
double random_double(double min, double max) {
  static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
  std::uniform_real_distribution<double> dist(min, max);
  return dist(rng);
}

// Функция генерации случайного полного графа с n вершинами и весами ребер в
// диапазоне [min_weight, max_weight]
void generate_random_complete_graph(Graph *G, int n, double min_weight = 1.0,
                                    double max_weight = 10.0) {
  for (int i = 0; i < n; ++i) {
    G->add_vertex(i);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        double weight = random_double(min_weight, max_weight);
        G->add_edge(i, j, weight);
        G->add_edge(j, i, weight);
      }
    }
  }
}

int main() {
  std::vector<int> sizes = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  //{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  std::cout << "---------------------------------" << std::endl;
  Graph *graph;
  for (int size : sizes) {
    graph = new Graph();
    generate_random_complete_graph(graph, size);
    std::cout << "Size:  " << size << '\n';
    double len;
    std::cout << std::fixed << std::setprecision(8);
    // std::cout << "1)";
    // double len = bru_time(*graph);
    // std::cout << " length: " << len << '\n';
    // std::cout << "2)";
    // len = bnb_time(*graph);
    // std::cout << " length: " << len << '\n';
    std::cout << "3)";
    len = gre_time(*graph);
    std::cout << " length: " << len << "\n4)";
    len = loc_time(*graph);
    std::cout << " length: " << len << "\n5)";
    len = gen_time(*graph);
    std::cout << " length: " << len << "\n";
    std::cout << "---------------------------------" << std::endl;
    delete graph;
  }
  return 0;
}