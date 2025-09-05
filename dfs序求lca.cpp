#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Lca {
  int n, r, dn, k;
  vector<vector<int>> g;
  vector<int> dfn;
  vector<vector<int>> mi;

  Lca(int n_=0): n(n_), r(1), dn(0), k(1), g(n_+1), dfn(n_+1) {}
  void init(int n_, int r_) { n = n_; r = r_; dn = 0; k = 1; g.assign(n+1, {}); dfn.assign(n+1, 0); }
  void add(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
  int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
  void dfs(int u, int p) { mi[0][dfn[u] = ++dn] = p; for (int v : g[u]) if (v != p) dfs(v, u); }
  void bld() {
    while ((1 << k) <= n) k++;
    mi.assign(k, vector<int>(n + 2));
    dn = 0;
    dfs(r, 0);
    for (int i = 1; i < k; i++)
      for (int j = 1; j + (1 << i) - 1 <= n; j++)
        mi[i][j] = get(mi[i - 1][j], mi[i - 1][j + (1 << (i - 1))]);
  }
  int qry(int u, int v) {
    if (u == v) return u;
    if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
    int len = v - u; ++u;
    int d = __lg(len);
    return get(mi[d][u], mi[d][v - (1 << d) + 1]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, r;
  cin >> n >> m >> r;
  Lca L(n);
  L.r = r;
  for (int i = 2, u, v; i <= n; i++) { cin >> u >> v; L.add(u, v); }
  L.bld();
  for (int i = 1, u, v; i <= m; i++) { cin >> u >> v; cout << L.qry(u, v) << '\n'; }
  return 0;
}

