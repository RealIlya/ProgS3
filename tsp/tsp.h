#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "graph.h"

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an
/// array of vertices.
std::vector<int> tsp(const Graph& graph);
std::vector<int> TSP_brute_force(const Graph& graph, int start);
// void BnB(const Graph& G, std::vector<int>& visited, std::vector<int>&
// best_path,
//         double& best_length, int last_vertex);
void BnB(const Graph& G, std::vector<int>& visited, int visited_mask,
         std::vector<int>& best_path, double& best_length);
std::vector<int> TSP_BnB(const Graph& G, int start);
std::vector<int> TSP_Greedy(const Graph& G, int start);
double Length(const Graph& G, const std::vector<int>& path);
