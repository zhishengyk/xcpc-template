// minimal includes for standalone linting; other compilation units may provide wider includes
#include <vector>
#include <utility>

long long count_triangles_undirected_edges(int n, const std::vector<std::pair<int, int>>& edges) {
  std::vector<int> degree(n + 1, 0);
  for (const std::pair<int, int>& e : edges) {
    int u = e.first;
    int v = e.second;
    if (u == v) continue;
    if (1 <= u && u <= n) degree[u]++;
    if (1 <= v && v <= n) degree[v]++;
  }

  std::vector<std::vector<int>> forward(n + 1);
  for (const std::pair<int, int>& e : edges) {
    int u = e.first;
    int v = e.second;
    if (u == v) continue;
    if (u < 1 || u > n || v < 1 || v > n) continue;
    if (degree[u] < degree[v] || (degree[u] == degree[v] && u < v)) {
      forward[u].push_back(v);
    } else {
      forward[v].push_back(u);
    }
  }

  std::vector<int> tag(n + 1, 0);
  int currentMark = 0;
  long long triangles = 0;

  for (int u = 1; u <= n; u++) {
    ++currentMark;
    for (int v : forward[u]) tag[v] = currentMark;
    for (int v : forward[u]) {
      for (int w : forward[v]) {
        if (tag[w] == currentMark) triangles++;
      }
    }
  }
  return triangles;
}

long long count_triangles_undirected_adj(int n, const std::vector<std::vector<int>>& G, bool one_indexed = true) {
  std::vector<std::pair<int, int>> edges;
  edges.reserve(static_cast<size_t>(n) * 2);
  if (one_indexed) {
    for (int u = 1; u <= n; u++) {
      for (int v : G[u]) if (u < v) edges.emplace_back(u, v);
    }
  } else {
    for (int u = 0; u < n; u++) {
      for (int v : G[u]) if (u < v) edges.emplace_back(u + 1, v + 1);
    }
  }
  return count_triangles_undirected_edges(n, edges);
}
