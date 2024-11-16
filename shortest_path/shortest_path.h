#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

#include "graph.h"

/// Return shortest path from start to end as array of vertices.
std::vector<int> shortest_path(const Graph &graph, int start_vertex,
                               int end_vertex);