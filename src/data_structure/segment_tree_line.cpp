template <typename meta, auto comp>
struct segment_tree {
  using type = typename meta::type;
  vector<meta> data;

  segment_tree(int n) : data(4 << __lg(n + 1)) {}

  inline int lson(int p) { return p << 1; }
  inline int rson(int p) { return p << 1 | 1; }
  void push(meta line, int r, int p = 1, int l = 1) {
    int m = (l + r) >> 1;
    if (comp(f[p], line, m)) swap(f[p], line);
    if (l + 1 == r) return;
    if (comp(f[p], line, l)) push(line, m, lson(p), l);
    if (comp(f[p], line, r)) push(line, r, rson(p), m);
  }
  void add(meta line, int L, int R, int r, int p = 1, int l = 1) {
    if (L <= l && r <= R) return push(line, r, p, l);
    int m = (l + r) >> 1;
    if (L < m) add(line, L, R, m, lson(p), l);
    if (R > m) add(line, L, R, r, rson(p), m);
  }
  type ask_max(int u, int r, int p = 1, int l = 1) {
    if (l + 1 == r) return data[p](u);
    int m = (l + r) >> 1;
    type res = type{};
    if (u < m) res = max(res, ask_max(u, m, lson(p), l));
    else       res = max(res, ask_max(u, r, rson(p), m));
    return res;
  }
  type ask_min(int u, int r, int p = 1, int l = 1) {
    if (l + 1 == r) return data[p](u);
    int m = (l + r) >> 1;
    type res = type{};
    if (u < m) res = min(res, ask_min(u, m, lson(p), l));
    else       res = min(res, ask_min(u, r, rson(p), m));
    return res;
  }
};

template <typename T>
struct meta {
  using type = T;
  T k, b;
  meta() : k{}, b{} {}
  constexpr T operator() (int x) const {
    return k * x + b;
  }
};