struct query_tree {
  vector<vector<int>> data;

  query_tree(int n) : data(4 << __lg(n + 1)) {}

  inline int lson(int p) { return p << 1; }
  inline int rson(int p) { return p << 1 | 1; }
  void add(int L, int R, int x, int r, int p = 1, int l = 1) {
    if (L <= l && r <= R) return data[p].push_back(x);
    int m = (l + r) >> 1;
    if (L < m) add(L, R, x, m, lson(p), l);
    if (R > m) add(L, R, x, r, rson(p), m);
  }
  void ask(auto&& _add, auto&& _del, auto&& call, int r, int p = 1, int l = 1) {
    _add(data[p]);
    if (l + 1 == r) {
      call(l);
    } else {
      int m = (l + r) >> 1;
      ask(_add, _del, call, m, lson(p), l);
      ask(_add, _del, call, r, rson(p), m);
    }
    _del(data[p]);
  }
};