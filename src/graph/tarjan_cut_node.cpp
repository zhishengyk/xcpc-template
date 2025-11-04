auto tarjan_cut_node(int n, const auto& G) {
  vector<int> dfn(n + 1);
  vector<int> low(n + 1);
  vector<int> cut(n + 1);
  int timer = 0, root = 0;
  const auto tarjan = [&](auto&& self, int u) -> void {
    int cnt_son = 0;
    dfn[u] = low[u] = ++timer;
    for (auto to : G[u]) {
      if (!dfn[to.v]) {
        ++cnt_son;
        self(self, to.v);
        low[u] = min(low[u], low[to.v]);
        if (low[to.v] >= dfn[u] && u != root)
          cut[u] = 1;
      } else {
        low[u] = min(low[u], dfn[to.v]);
      }
    }
    if (cnt_son >= 2 && u == root)
      cut[u] = 1;
  };
  for (int u = 1; u <= n; u++)
    if (!dfn[u]) tarjan(tarjan, root = u);
  return move(cut);
}