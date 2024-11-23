#include "tsp.h"

using namespace std;

double pathWeight(const Graph& graph, vector<int>* path) {
  double weight = 0;
  for (int i = 0; i < path->size(); i++) {
    int f = -1, s = -1, c = i + 1;
    if (i == path->size() - 1) c = 0;
    for (int j = 0; j < path->size() && (f == -1 || s == -1); j++) {
      if (path->at(j) == i) f = j;
      if (path->at(j) == c) s = j;
    }
    weight += graph.edge_weight(f, s);
  }
  return weight;
}

bool recursiveAlg(const Graph& graph, vector<int>* v, int vertex,
                  vector<vector<int>*>& Permutations) {
  vector<int> paths = graph.get_adjacent_vertices(vertex);
  vector<int> V(*v);
  bool first = true, has_vertices = false;
  int count = V[vertex] + 1;
  for (int i = 0; i < paths.size(); i++) {
    if (V[paths[i]] == -1) {
      has_vertices = true;
      if (!first) {
        vector<int>* tmp = new vector<int>(V);
        tmp->at(paths[i]) = count;
        if (count == tmp->size() - 1)
          Permutations.push_back(tmp);
        else {
          bool t = recursiveAlg(graph, tmp, paths[i], Permutations);
          if (!t) delete tmp;
        }
      } else {
        v->at(paths[i]) = count;
        if (count == v->size() - 1)
          Permutations.push_back(v);
        else
          recursiveAlg(graph, v, paths[i], Permutations);
        first = false;
      }
    }
  }
  return has_vertices;
}

vector<int> TSP(const Graph& graph, int start) {
  vector<vector<int>*> Permutations;
  vector<int> G = graph.get_vertices();
  vector<int>* v = new vector<int>(G.size());
  for (auto& i : *v) i = -1;
  v->at(start) = 0;
  recursiveAlg(graph, v, start, Permutations);
  double mn = numeric_limits<double>::max(), mi = -1;
  for (int i = 0; i < Permutations.size(); i++) {
    double pw = pathWeight(graph, Permutations[i]);
    if (pw < mn) {
      mn = pw;
      mi = i;
    }
  }
  vector<int> result;
  if (mi != -1) result = vector<int>(*Permutations[mi]);
  for (auto i : Permutations) delete i;
  return result;
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
  // Your implementation here.
  vector<int> result;
  if (!comp.get_vertices().empty()) result = TSP(comp, 0);
  return result;
}
