template <typename meta>
struct fenwick_tree {
  int n;
  vector<meta> data;

  fenwick_tree(int _n) : n(_n), data(_n + 1) {}

  void add(int u, const meta& x) {
    for (int i = u; i <= n; i += i & -i) data[i] += x;
  }
  meta ask(int u, meta res = meta{}) {
    for (int i = u; ~i; i &= i - 1) res += data[i];
    return res;
  }
};