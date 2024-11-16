#include "min_spanning_tree.h"

using namespace std;

vector<pair<int, int>> min_spanning_tree(const Graph &graph) {
  // Return minimal spanning tree (MST) for the graph as array of edges.
  // Each edge is represented by its two vertices.
  // Order of edges in result and vertices in edges doesn't matter.
  // Return empty array if MST doesn't exist.

  vector<pair<int, int>> result;
  // Prim algorithm
  int s = 0;
  map<int, double> MinWeight;
  map<int, int> Parent;
  vector<int> vertices = graph.get_vertices();
  set<int> Q;
  for (auto i : vertices) {
    MinWeight[i] = numeric_limits<double>::max();
    Q.insert(i);
  }
  MinWeight[s] = 0;
  while (!Q.empty()) {
    double m = numeric_limits<double>::max();
    auto mi = Q.end();
    for (auto i = Q.begin(); i != Q.end(); ++i)
      if (MinWeight[*i] < m) {
        m = MinWeight[*i];
        mi = i;
      }
    int u = *mi;
    if (mi != Q.end()) {
      Q.erase(mi);
      for (auto v : graph.get_adjacent_vertices(u)) {
        double w = graph.edge_weight(u, v);
        if (Q.find(v) != Q.end() && MinWeight[v] > w) {
          MinWeight[v] = w;
          Parent[v] = u;
        }
      }
    }
  }
  for (auto i : vertices)
    if (i != Parent[i]) result.push_back(make_pair(i, Parent[i]));
  // Your implementation here.
  return result;
}
