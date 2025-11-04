struct disjoint_union_set {
  vector<int> set;
  vector<array<int, 2>> stk;

  disjoint_union_set(int n) : set(n + 1, -1), stk{} {}

  int find(int x) {
    while (~set[x]) x = set[x];
    return x;
  }
  bool merge(int x, int y) {
    if (x = find(x), y = find(y); x == y) return false;
    if (set[x] < set[y]) stk.push_back({y, set[y]}), set[x] += set[y], set[y] = x;
    else                 stk.push_back({x, set[x]}), set[y] += set[x], set[x] = y;
    return true;
  }
  void rollback() {
    auto [u, s] = stk.back();
    stk.pop_back();
    set[set[u]] -= s;
    set[u] = s;
  }
};