struct LCA {
  int n;
  vector<int> dfn;
  vector<int> data[20];

  LCA(int n, int root, const auto& G) : dfn(n + 1) {
    for (int i = 0; i <= __lg(n); i++)
      data[i].assign(n - (1 << i) + 2, 0);
    int t = 0;
    const auto dfs = [&](auto&& self, int u, int p) -> void {
      data[0][dfn[u] = ++t] = p;
      for (auto v : G[u]) if (v != p) self(self, v, u);
    };
    dfs(dfs, root, 0);
    for (int k = 1; k <= __lg(n); k++) {
      for (int i = 1; i + (1 << k) - 1 <= n; i++) {
        data[k][i] = cmp(data[k - 1][i], data[k - 1][i + (1 << (k - 1))]);
      }
    }
  }

  int cmp(int l, int r) {
    return dfn[l] < dfn[r] ? l : r;
  }
  int ask(int u, int v) {
    if (u == v) return u;
    u = dfn[u], v = dfn[v];
    if(u < v) swap(u, v);
    int k = __lg(u - v);
    return cmp(data[k][v + 1], data[k][u - (1 << k) + 1]);
  }
};