template <typename meta, int N>
struct segment_tree {
  struct node {
    meta val;
    int son[2];
    node() : val{}, son{} {}
  };
  int lst;
  node data[N << 6];

  void add(int& p, int q, int u, const auto& x, int l, int r) {
    data[p = ++lst] = data[q];
    if (l + 1 == r) return data[p].val.add(x, l, r);
    int m = (l + r) >> 1;
    if (u < m) add(data[p].son[0], data[q].son[0], u, x, l, m);
    else       add(data[p].son[1], data[q].son[1], u, x, m, r);
    data[p].val.pull(data[data[p].son[0]].val, data[data[p].son[1]].val, l, r);
  }
  meta ask(int p, int l, int r, int L, int R) {
    if (!p) return meta{};
    if (L <= l && r <= R) return data[p].val;
    int m = (l + r) >> 1;
    meta res{};
    if (L < m) res = res + ask(data[p].son[0], l, m, L, R);
    if (R > m) res = res + ask(data[p].son[1], m, r, L, R);
    return res;
  }
  meta ask_with_diff(int p, int q, int l, int r, int L, int R) {
    if (!p) return meta{};
    if (L <= l && r <= R) return data[p].val - data[q].val;
    int m = (l + r) >> 1;
    meta res{};
    if (L < m) res = res + ask_with_diff(data[p].son[0], data[q].son[0], l, m, L, R);
    if (R > m) res = res + ask_with_diff(data[p].son[1], data[q].son[1], m, r, L, R);
    return res;
  }
  void split(int p, int& x, int& y, int l, int r, int L, int R) {
    if (!p) return x = y = 0, void();
    if (R <= l || r <= L) return x = 0, y = p, void();
    if (L <= l && r <= R) return x = p, y = 0, void();
    int m = (l + r) >> 1;
    int xl = 0, xr = 0, yl = 0, yr = 0;
    split(data[p].son[0], xl, yl, l, m, L, R);
    split(data[p].son[1], xr, yr, m, r, L, R);
    if (xl || xr) {
      x = ++lst;
      data[x] = data[p];
      data[x].son[0] = xl;
      data[x].son[1] = xr;
      data[x].val.pull(data[data[x].son[0]].val, data[data[x].son[1]].val, l, r);
    } else x = 0;
    if (yl || yr) {
      y = ++lst;
      data[y] = data[p];
      data[y].son[0] = yl;
      data[y].son[1] = yr;
      data[y].val.pull(data[data[y].son[0]].val, data[data[y].son[1]].val, l, r);
    } else y = 0;
  }
  int merge(int x, int y, int l, int r) {
    if (!x | !y) return x | y;
    int p = ++lst;
    if (l + 1 == r) {
      data[p].son[0] = data[p].son[1] = 0;
      data[p].val = data[x].val + data[y].val;
      return p;
    }
    int m = (l + r) >> 1;
    data[p].son[0] = merge(data[x].son[0], data[y].son[0], l, m);
    data[p].son[1] = merge(data[x].son[1], data[y].son[1], m, r);
    data[p].val.pull(data[data[p].son[0]].val, data[data[p].son[1]].val, l, r);
    return p;
  }
};

struct meta {
  meta() {}
  void add(const auto& x, int l, int r) {}
  void pull(meta& lhs, meta& rhs, int l, int r) {}
  void push(meta& lhs, meta& rhs, int l, int r) {}
  friend meta operator+ (const meta& lhs, const meta& rhs) {}
  friend meta operator- (const meta& lhs, const meta& rhs) {}
};