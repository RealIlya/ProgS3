#include <limits>
#include <set>
#include <vector>

#include "graph.h"

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an
/// array of vertices.
std::vector<int> tsp(const Graph &graph);