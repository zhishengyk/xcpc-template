template <typename meta>
struct chtholly_tree {
  using iter = map<int, meta>::iterator;
  map<int, meta> data;

  chtholly_tree(int l, int r) {
    data[l] = meta{};
    data[r + 1] = meta{};
  }

  iter split(int p) {
    iter it = prev(data.upper_bound(p));
    if (it->first == p) return it;
    return odt.insert(it, {p, it->second});
  }
  void alloc(int l, int r, const meat& x) {
    iter L = split(l);
    iter R = split(r + 1);
    data.erase(L, R);
    data[l] = x;
  }
  void apply(int l, int r, auto&& call) {
    iter L = split(l);
    iter R = split(r + 1);
    while (L != R) {
      iter P = L++;
      call(P, L);
    }
  }
};