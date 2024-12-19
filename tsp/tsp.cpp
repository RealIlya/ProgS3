#include "tsp.h"

using namespace std;

std::vector<int> TSP_brute_force(const Graph& graph, int start_vertex) {
  std::vector<int> vertices = graph.get_vertices();
  vertices.erase(std::remove(vertices.begin(), vertices.end(), start_vertex),
                 vertices.end());
  std::vector<int> best_path;
  double min_distance = std::numeric_limits<double>::max();
  // Генерируем все перестановки вершин
  do {
    std::vector<int> current_path = {start_vertex};
    double current_distance = 0.0;
    int prev_vertex = start_vertex;
    for (int vertex : vertices) {
      if (graph.has_edge(prev_vertex, vertex)) {
        current_distance += graph.edge_weight(prev_vertex, vertex);
        current_path.push_back(vertex);
        prev_vertex = vertex;
      } else {
        current_distance = std::numeric_limits<double>::max();
        break;
      }
    }
    if (current_distance != std::numeric_limits<double>::max() &&
        graph.has_edge(prev_vertex, start_vertex)) {
      current_distance += graph.edge_weight(prev_vertex, start_vertex);
      if (current_distance < min_distance) {
        min_distance = current_distance;
        best_path = current_path;
      }
    }
  } while (std::next_permutation(vertices.begin(), vertices.end()));
  return best_path;
}

vector<int> tsp(const Graph& graph) {
  // Return the shortest (with a minimal total weight) tour as an array of
  // vertices. Return empty array if there is no tour.

  // Делаем орграф неорграфом
  Graph comp(graph);
  vector<int> vetrices = comp.get_vertices();
  for (auto& i : vetrices) {
    auto edges = comp.get_adjacent_edges(i);
    for (auto& j : edges) {
      comp.add_edge(j.first, i, j.second);
    }
  }
  vector<int> result;

  // vector<int> bestPath = TSP_GA(graph, P, N, MaxIt, Pm);
  if (!comp.get_vertices().empty()) result = TSP_Greedy(comp, 0);
  return result.size() > 1 ? result : vector<int>{};
}

double Length(const Graph& G, const std::vector<int>& path) {
  if (path.size() < 2) return std::numeric_limits<double>::max();
  double length = 0.0;
  for (size_t i = 0; i < path.size() - 1; ++i) {
    length += G.edge_weight(path[i], path[i + 1]);
  }
  length += G.edge_weight(path.back(), path.front());
  return length;
}

// Пользовательская хеш-функция для std::pair<int, int>
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

using State = std::pair<int, int>;  // (current_vertex, visited_mask)
std::unordered_map<State, double, pair_hash> memo;

double LowerBound(const Graph& G, int current_vertex, int visited_mask) {
  State state = {current_vertex, visited_mask};
  if (memo.find(state) != memo.end()) {
    return memo[state];
  }

  double bound = 0.0;
  int n = G.get_vertices().size();

  for (int v = 0; v < n; ++v) {
    if ((visited_mask & (1 << v)) == 0) {
      double min1 = std::numeric_limits<double>::max();
      double min2 = std::numeric_limits<double>::max();
      for (const auto& edge : G.get_adjacent_edges(v)) {
        if (edge.first == current_vertex) min1 = edge.second;
        /*if (edge.second < min1) {
          min2 = min1;
          min1 = edge.second;
        }*/
        else if (edge.second < min2) {
          min2 = edge.second;
        }
      }
      bound += min1 + min2;
    }
  }

  memo[state] = bound / 2.0;
  return memo[state];
}

std::vector<int> TSP_BnB(const Graph& G, int start) {
  std::vector<int> visited = {start};
  std::vector<int> best_path = TSP_Greedy(G, start);
  int visited_mask = (1 << start);
  double best_length = Length(G, best_path);
  // std::numeric_limits<double>::max();
  BnB(G, visited, visited_mask, best_path, best_length);
  return best_path;
}

void BnB(const Graph& G, std::vector<int>& visited, int visited_mask,
         std::vector<int>& best_path, double& best_length) {
  if (visited.size() == G.get_vertices().size()) {
    double length = Length(G, visited);
    if (length < best_length) {
      best_length = length;
      best_path = visited;
    }
    return;
  }

  int n = G.get_vertices().size();
  for (int v = 0; v < n; ++v) {
    if ((visited_mask & (1 << v)) == 0) {
      int new_visited_mask = visited_mask | (1 << v);
      double lower_bound = LowerBound(G, v, new_visited_mask);
      if (lower_bound < best_length) {
        visited.push_back(v);
        BnB(G, visited, new_visited_mask, best_path, best_length);
        visited.pop_back();
      }
    }
  }
}

vector<int> TSP_Greedy(const Graph& G, int start) {
  int current = start;
  vector<int> path = {current};
  while (path.size() != G.get_vertices().size()) {
    int next = -1;
    double min_weight = std::numeric_limits<double>::max();
    for (int v : G.get_vertices()) {
      if (std::find(path.begin(), path.end(), v) == path.end()) {
        double weight = G.edge_weight(current, v);
        if (weight < min_weight) {
          min_weight = weight;
          next = v;
        }
      }
    }
    path.push_back(next);
    current = next;
  }
  return path;
}

vector<int> TwoOptImprove(const Graph& graph, const vector<int>& path) {
  int n = path.size();
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 2; j < n; ++j) {
      int oldWeight = graph.edge_weight(path[i], path[i + 1]) +
                      graph.edge_weight(path[j], path[(j + 1) % n]);
      int newWeight = graph.edge_weight(path[i], path[j]) +
                      graph.edge_weight(path[i + 1], path[(j + 1) % n]);
      if (newWeight < oldWeight) {
        return Transform(path, i, i + 1, j, (j + 1) % n);
      }
    }
  }
  return path;
}

vector<int> Transform(const vector<int>& path, int A, int B, int C, int D) {
  vector<int> newPath;
  for (int i = 0; i <= A; ++i) {
    newPath.push_back(path[i]);
  }
  for (int i = C; i >= B; --i) {
    newPath.push_back(path[i]);
  }
  for (int i = D; i < path.size(); ++i) {
    newPath.push_back(path[i]);
  }
  return newPath;
}

vector<int> TSP_LS(const Graph& graph) {
  int numVertices = graph.get_vertices().size();
  vector<int> currentPath = TSP_Greedy(graph, 0);
  while (true) {
    vector<int> improvedPath = TwoOptImprove(graph, currentPath);
    if (Length(graph, improvedPath) < Length(graph, currentPath)) {
      currentPath = improvedPath;
    } else {
      return currentPath;
    }
  }
}

// Genetic algorithm-----------

double random(double min, double max) {
  random_device rd;
  mt19937 g(rd());
  return uniform_real_distribution<double>(min, max)(g);
}

int random(int min, int max) {
  random_device rd;
  mt19937 g(rd());
  return uniform_int_distribution<int>(min, max)(g);
}

void crossoverER(const Graph& graph, const vector<int>& parent1,
                 const vector<int>& parent2, vector<int>& child) {
  int n = graph.get_vertices().size();
  vector<int> edge_counts(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j : graph.get_adjacent_vertices(i)) {
      if (find(parent1.begin(), parent1.end(), j) != parent1.end() ||
          find(parent2.begin(), parent2.end(), j) != parent2.end()) {
        ++edge_counts[j];
      }
    }
  }

  int current = parent1[random(0, n - 1)];
  child.push_back(current);
  set<int> visited;
  visited.insert(current);

  while (child.size() < n) {
    int min_edges = numeric_limits<int>::max();
    int next = -1;

    for (int i : graph.get_adjacent_vertices(current)) {
      if (visited.find(i) == visited.end() && edge_counts[i] < min_edges) {
        min_edges = edge_counts[i];
        next = i;
      }
    }

    if (next == -1) {
      do {
        current = random(0, n - 1);
      } while (visited.find(current) != visited.end());
    } else {
      current = next;
    }

    child.push_back(current);
    visited.insert(current);
  }
}

void SUS(int N, const vector<double>& fitness, vector<int>& chosen) {
  vector<double> cumsum(fitness.size() + 1);
  partial_sum(fitness.begin(), fitness.end(), cumsum.begin() + 1);
  double F = cumsum.back();
  double Dist = F / N;
  double Start = random(0.0, Dist);
  int k = 0;
  for (int i = 0; i < N; ++i) {
    double point = Start + Dist * i;
    k = lower_bound(cumsum.begin(), cumsum.end(), point) - cumsum.begin();
    chosen[i] = k - 1;
  }
}

//------------------------------------------------------------------------------

// Функция для генерации случайного маршрута
vector<int> generateRandomPath(size_t numCities) {
  vector<int> path(numCities);
  for (size_t i = 0; i < numCities; ++i) {
    path[i] = i;
  }
  random_device rd;
  mt19937 g(rd());
  shuffle(path.begin(), path.end(), g);
  return path;
}

// Функция для отбора лучших маршрутов
void selectBestPaths(const Graph& graph, const vector<vector<int>>& population,
                     size_t numBest, vector<int>& chosen) {
  vector<pair<double, int>> rankedPopulation(population.size());
  for (int i = 0; i < population.size(); ++i) {
    rankedPopulation[i] = make_pair(Length(graph, population[i]), i);
  }
  nth_element(rankedPopulation.begin(), rankedPopulation.begin() + numBest,
              rankedPopulation.end());
  for (size_t i = 0; i < numBest; ++i) {
    chosen[i] = rankedPopulation[i].second;
  }
}

// Функция для скрещивания двух маршрутов
void crossover(const vector<int>& parent1, const vector<int>& parent2,
               vector<int>& child) {
  size_t numCities = parent1.size();
  random_device rd;
  mt19937 g(rd());
  uniform_int_distribution<> dis(0, numCities - 1);
  size_t start = min(dis(g), dis(g));
  size_t end = max(dis(g), dis(g));
  bitset<1000> visited;
  for (auto& i : child) i = -1;
  for (size_t i = start; i <= end; ++i) {
    child[i] = parent1[i];
    visited[parent1[i]] = true;
  }
  size_t pos = 0;
  for (size_t i = 0; i < numCities; ++i) {
    // if (find(child.begin(), child.end(), parent2[i]) == child.end()) {
    if (!visited[parent2[i]]) {
      while (child[pos] != -1) {
        ++pos;
      }
      child[pos] = parent2[i];
      visited[parent2[i]] = true;
    }
  }
}
/*vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2)
{ size_t numCities = parent1.size(); random_device rd; mt19937 g(rd());
  uniform_int_distribution<> dis(0, numCities - 1);

  // Генерация случайного сегмента
  size_t start = min(dis(g), dis(g));
  size_t end = max(dis(g), dis(g));

  vector<int> child(numCities, -1);
  bitset<1000>
      used;  // Предполагается, что количество городов не превышает 1000

  // Копирование сегмента из parent1 в child
  for (size_t i = start; i <= end; ++i) {
    child[i] = parent1[i];
    used[parent1[i]] = true;
  }

  // Заполнение оставшихся позиций
  size_t pos = 0;
  for (size_t i = 0; i < numCities; ++i) {
    if (!used[parent2[i]]) {
      while (pos < numCities && child[pos] != -1) {
        ++pos;
      }
      child[pos] = parent2[i];
      used[parent2[i]] = true;
    }
  }

  return child;
}*/

// Функция для частичной оптимизации 2-opt
void partialTwoOptOptimization(const Graph& graph, vector<int>& path,
                               size_t maxIterations) {
  size_t numCities = path.size();
  bool improved = true;
  size_t iteration = 0;
  while (improved && iteration < maxIterations) {
    improved = false;
    for (size_t i = 1; i < numCities - 1; ++i) {
      for (size_t j = i + 1; j < numCities; ++j) {
        double currentDist =
            graph.edge_weight(path[i - 1], path[i]) +
            graph.edge_weight(path[j], path[(j + 1) % numCities]);
        double newDist = graph.edge_weight(path[i - 1], path[j]) +
                         graph.edge_weight(path[i], path[(j + 1) % numCities]);
        if (newDist < currentDist) {
          reverse(path.begin() + i, path.begin() + j + 1);
          improved = true;
          //++iteration;
        }
      }
    }
    ++iteration;
  }
}

// Функция для мутации маршрута с использованием частичной оптимизации 2-opt
void mutateWithPartialTwoOpt(const Graph& graph, vector<int>& path,
                             size_t maxIterations) {
  random_device rd;
  mt19937 g(rd());
  uniform_int_distribution<> dis(0, path.size() - 1);
  size_t index1 = dis(g);
  size_t index2 = dis(g);
  swap(path[index1], path[index2]);
  partialTwoOptOptimization(graph, path, maxIterations);
}

vector<double> parallelCalculateLengths(const Graph& graph,
                                        const vector<vector<int>>& population) {
  vector<future<double>> futures;
  for (const auto& path : population) {
    futures.push_back(async(launch::async,
                            [&graph, &path]() { return Length(graph, path); }));
  }
  vector<double> lengths(population.size());
  for (size_t i = 0; i < futures.size(); ++i) {
    lengths[i] = futures[i].get();
  }
  return lengths;
}

void parallelMutate(const Graph& graph, vector<vector<int>>& population,
                    double mutationRate, size_t maxIterations, size_t start,
                    size_t end) {
  random_device rd;
  mt19937 g(rd());
  uniform_real_distribution<> dis(0.0, 1.0);
  for (size_t i = start; i < end; ++i) {
    if (dis(g) < mutationRate) {
      mutateWithPartialTwoOpt(graph, population[i], maxIterations);
    }
  }
}

/*vector<int> TSP_GA(const Graph& graph, size_t populationSize, size_t numBest,
                   double mutationRate, size_t numGenerations,
                   size_t maxIterations) {
  size_t numCities = graph.get_vertices().size();
  vector<vector<int>> population;
  for (size_t i = 0; i < populationSize; ++i) {
    population.push_back(generateRandomPath(numCities));
  }
  vector<int> chosen(numBest);

  for (size_t generation = 0; generation < numGenerations; ++generation) {
    vector<double> lengths = parallelCalculateLengths(graph, population);
    vector<pair<double, int>> rankedPopulation(populationSize);
    for (int i = 0; i < populationSize; ++i) {
      rankedPopulation[i] = make_pair(lengths[i], i);
    }
    nth_element(rankedPopulation.begin(), rankedPopulation.begin() + numBest,
                rankedPopulation.end());
    for (size_t i = 0; i < numBest; ++i) {
      chosen[i] = rankedPopulation[i].second;
    }

    vector<vector<int>> newPopulation;
    // Сохраняем лучших особей (элитизм)
    for (size_t i = 0; i < numBest; ++i) {
      newPopulation.push_back(population[chosen[i]]);
    }

    // Определяем количество потоков
    size_t numThreads = thread::hardware_concurrency();
    vector<future<void>> futures;
    size_t chunkSize = (populationSize - numBest) / numThreads;

    for (size_t t = 0; t < numThreads; ++t) {
      size_t start = numBest + t * chunkSize;
      size_t end = (t == numThreads - 1) ? populationSize : start + chunkSize;
      futures.push_back(async(launch::async, parallelMutate, ref(graph),
                              ref(newPopulation), mutationRate, maxIterations,
                              start, end));
    }

    for (auto& f : futures) {
      f.get();
    }

    population = newPopulation;
  }

  vector<double> finalLengths = parallelCalculateLengths(graph, population);
  int bestIndex = 0;
  double minLength = finalLengths[0];
  for (size_t i = 1; i < populationSize; ++i) {
    if (finalLengths[i] < minLength) {
      minLength = finalLengths[i];
      bestIndex = i;
    }
  }
  return population[bestIndex];
}*/

vector<int> TSP_GA(const Graph& graph, size_t populationSize, size_t numBest,
                   double mutationRate, size_t numGenerations,
                   size_t maxIterations) {
  // size_t numCities = 5;
  // size_t populationSize = 100;
  // size_t numGenerations = 1000;
  // size_t numBest = 10;
  // double mutationRate = 0.01;
  size_t numCities = graph.get_vertices().size();
  vector<vector<int>> population;
  for (size_t i = 0; i < populationSize; ++i) {
    population.push_back(generateRandomPath(numCities));
  }
  vector<int> chosen(numBest);
  vector<int> child(numCities);
  for (size_t generation = 0; generation < numGenerations; ++generation) {
    selectBestPaths(graph, population, numBest, chosen);
    // Создание новой популяции путем скрещивания лучших маршрутов
    vector<vector<int>> newPopulation;
    for (size_t i = 0; i < populationSize; ++i) {
      size_t parent1Index = rand() % numBest;
      size_t parent2Index = rand() % numBest;
      crossover(population[chosen[parent1Index]],
                population[chosen[parent2Index]], child);
      //// Мутация нового маршрута
      // if (random(0.0, 1.0) < mutationRate) {
      //   mutateWithPartialTwoOpt(graph, child, maxIterations);
      // }

      newPopulation.push_back(child);
    }
    size_t numThreads = thread::hardware_concurrency();
    vector<future<void>> futures;
    size_t chunkSize = (populationSize - numBest) / numThreads;

    for (size_t t = 0; t < numThreads; ++t) {
      size_t start = numBest + t * chunkSize;
      size_t end = (t == numThreads - 1) ? populationSize : start + chunkSize;
      futures.push_back(async(launch::async, parallelMutate, ref(graph),
                              ref(newPopulation), mutationRate, maxIterations,
                              start, end));
    }

    for (auto& f : futures) {
      f.get();
    }

    population = newPopulation;
  }

  // Выбор лучшего маршрута из последней популяции
  selectBestPaths(graph, population, 1, chosen);
  return population[chosen[0]];
}