template <typename meta, auto comp>
struct sparse_table {
  vector<meta> data[20];

  void build(int n, auto&& call) {
    for (int i = 0; i <= __lg(n); i++)
      data[i].assign(n - (1 << i) + 2, meta{});
    for (int i = 1; i <= n; i++)
      data[0][i] = call(i);
    for (int k = 1; k <= __lg(n); k++) {
      for (int i = 1; i + (1 << k) - 1 <= n; i++) {
        data[k][i] = comp(data[k - 1][i], data[k - 1][i + (1 << (k - 1))]);
      }
    }
  }
  meta ask(int l, int r) {
    int k = __lg(r - l + 1);
    return comp(data[k][l], data[k][r - (1 << k) + 1]);
  }
};