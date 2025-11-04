template <typename meta>
struct segment_tree {
  vector<meta> data;

  segment_tree(int n) : data(4 << __lg(n + 1)) {}

  inline int lson(int p) { return p << 1; }
  inline int rson(int p) { return p << 1 | 1; }
  void build(auto&& call, int r, int p = 1, int l = 1) {
    if (l + 1 == r) return data[p] = call(l), void();
    int m = (l + r) >> 1;
    build(call, m, lson(p), l);
    build(call, r, rson(p), m);
    data[p].pull(data[lson(p)], data[rson(p)], l, r);
  }
  void add(int L, int R, const auto& x, int r, int p = 1, int l = 1) {
    if (L <= l && r <= R) return data[p].add(x, l, r);
    data[p].push(data[lson(p)], data[rson(p)], l, r);
    int m = (l + r) >> 1;
    if (L < m) add(L, R, x, m, lson(p), l);
    if (R > m) add(L, R, x, r, rson(p), m);
    data[p].pull(data[lson(p)], data[rson(p)], l, r);
  }
  meta ask(int L, int R, int r, int p = 1, int l = 1) {
    if (R <= l || r <= L) return meta{};
    if (L <= l && r <= R) return data[p];
    data[p].push(data[lson(p)], data[rson(p)], l, r);
    int m = (l + r) >> 1;
    return ask(L, R, m, lson(p), l) + ask(L, R, r, rson(p), m);
  }
};

struct meta {
  meta() {}
  void add(const auto& x, int l, int r) {}
  void pull(meta& lhs, meta& rhs, int l, int r) {}
  void push(meta& lhs, meta& rhs, int l, int r) {}
  friend meta operator+ (const meta& lhs, const meta& rhs) {}
};