auto tarjan_vbcc(int n, const auto& G) {
  vector<int> dfn(n + 1);
  vector<int> low(n + 1);
  vector<vector<int>> vbcc;
  int timer = 0;
  const auto tarjan = [&](auto&& self, int u, int preid) -> void {
    static vector<int> stk;
    dfn[u] = low[u] = ++timer;
    for (auto to : G[u]) {
      if (to.id == preid) continue;
      if (!dfn[to.v]) {
        stk.push_back(to.id);
        self(self, to.v, to.id);
        low[u] = min(low[u], low[to.v]);
        if (low[to.v] >= dfn[u]) {
          vbcc.push_back({});
          while (!stk.empty()) {
            auto p = stk.back();
            stk.pop_back();
            vbcc.back().push_back(p);
            if (p == to.id) break;
          }
        }
      } else if (dfn[to.v] < dfn[u]) {
        stk.push_back(to.id);
        low[u] = min(low[u], dfn[to.v]);
      }
    }
  };
  for (int u = 1; u <= n; u++)
    if (!dfn[u]) tarjan(tarjan, u, -1);
  return move(vbcc);
}