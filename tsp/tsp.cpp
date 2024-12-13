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
  if (!comp.get_vertices().empty()) result = TSP_BnB(comp, 0);
  // TSP_brute_force(comp, 0);  // TSP_Greedy(comp, 0);
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

/*double LowerBound(const Graph& G, const std::vector<int>& visited,
                  int last_vertex) {
  double bound = 0.0;
  if (visited.size() > 1) {
    bound += G.edge_weight(visited.back(), last_vertex);
  }
  for (int v : G.get_vertices()) {
    if (std::find(visited.begin(), visited.end(), v) == visited.end()) {
      double min1 = std::numeric_limits<double>::max();
      double min2 = std::numeric_limits<double>::max();
      for (const auto& edge : G.get_adjacent_edges(v)) {
        if (edge.second < min1) {
          min2 = min1;
          min1 = edge.second;
        } else if (edge.second < min2) {
          min2 = edge.second;
        }
      }
      bound += min1 + min2;
    }
  }
  return bound / 2.0;
}
std::vector<int> TSP_BnB(const Graph& G, int start) {
  std::vector<int> best_path = TSP_Greedy(G, start);
  std::vector<int> visited = {start};
  double best_length = Length(G, best_path);

  BnB(G, visited, best_path, best_length, start);
  return best_path;
}

void BnB(const Graph& G, std::vector<int>& visited, std::vector<int>& best_path,
         double& best_length, int last_vertex) {
  if (visited.size() == G.get_vertices().size()) {
    double length = Length(G, visited);
    if (length < best_length) {
      best_length = length;
      best_path = visited;
    }
    return;
  }

  for (int v : G.get_vertices()) {
    if (std::find(visited.begin(), visited.end(), v) == visited.end()) {
      // std::vector<int> v_next = visited;
      // v_next.push_back(v);
      visited.push_back(v);
      if (LowerBound(G, visited, last_vertex) < best_length) {
        BnB(G, visited, best_path, best_length, v);
      }
      visited.pop_back();
    }
  }
}*/

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