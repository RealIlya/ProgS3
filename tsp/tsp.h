#include <algorithm>
#include <bitset>
#include <chrono>
#include <ctime>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <thread>
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
std::vector<int> Transform(const std::vector<int>& path, int A, int B, int C,
                           int D);
std::vector<int> TSP_LS(const Graph& graph);
std::vector<int> geneticAlgorithm(const Graph& graph, int N, int populationSize,
                                  double pm, int generations);
std::vector<int> TSP_GA(const Graph& graph, size_t populationSize,
                        size_t numBest, double mutationRate,
                        size_t numGenerations, size_t maxIterations);