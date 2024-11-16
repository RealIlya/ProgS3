#pragma once

#include <limits>
#include <set>
#include <vector>

#include "graph.h"

// Return minimal spanning tree for the (connected) graph as array of edges.
std::vector<std::pair<int, int>> min_spanning_tree(const Graph &graph);
