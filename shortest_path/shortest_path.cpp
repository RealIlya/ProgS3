#include "shortest_path.h"

using namespace std;

vector<int> Build_path(map<int, int>& Parent, int s, int e) {
  deque<int> res;
  int i = e;
  while (Parent.find(i) != Parent.end() || i != s) {
    res.push_front(i);
    i = Parent[i];
  }
  if (i == s && res.size() > 0) {
    res.push_front(i);
    vector<int> r(res.size());
    int n = 0;
    for (auto j : res) r[n++] = j;
    return r;
  } else
    return vector<int>{};
}

vector<int> shortest_path(const Graph& graph, int start_vertex,
                          int end_vertex) {
  // Return shortest path in the graph from start vertex to end vertex as array
  // of vertices. First item in the result should be start vertex, last - end
  // vertex. Return empty array if there is no path.
  // cout << "---------------------\n";
  map<int, double> Distance;
  map<int, int> Parent;
  auto G = graph.get_vertices();
  for (auto v : G) {
    Distance[v] = numeric_limits<double>::max();
    // cout << v << ' ';
  }
  // cout << '\n';
  Distance[start_vertex] = 0;
  auto Q = graph.get_vertices();
  while (!Q.empty()) {
    double m = numeric_limits<double>::max();
    auto mi = Q.end();
    for (auto i = Q.begin(); i != Q.end(); ++i)
      if (Distance[*i] < m) {
        m = Distance[*i];
        mi = i;
      }
    // cout << *mi << endl;
    int u = *mi;
    if (mi == Q.end()) return vector<int>{};
    Q.erase(mi);
    if (u == end_vertex)
      return Build_path(Parent, start_vertex, end_vertex);
    else {
      for (auto v : graph.get_adjacent_vertices(u)) {
        if (Distance[v] > Distance[u] + graph.edge_weight(v, u)) {
          Distance[v] = Distance[u] + graph.edge_weight(v, u);
          Parent[v] = u;
        }
      }
    }
  }
  return vector<int>{};
}
