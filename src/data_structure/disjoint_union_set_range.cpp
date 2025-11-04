struct disjoint_union_set {
  vector<int> data[20];

  disjoint_union_set(int n) {
    for (int i = 0; i <= __lg(n); i++) data[i].assign(n - (1 << i) + 2, -1);
  }

  int find(int k, int x) {
    return data[k][x] < 0 ? x : data[k][x] = find(k, data[k][x]);
  }
  bool merge(int k, int x, int y) {
    if (x = find(k, x), y = find(k, y); x == y) return false;
    if (data[k][x] < data[k][y]) data[k][x] += data[k][y], data[k][y] = x;
    else                         data[k][y] += data[k][x], data[k][x] = y;
    return true;
  }
  void merge_range(int k, int x, int y, auto&& call) {
    if (find(k, x) == find(k, y)) return;
    if (k == 0) {
      call(find(0, x), find(0, y));
    } else {
      merge(k - 1, x, y, call);
      merge(k - 1, x + (1 << (k - 1)), y + (1 << (k - 1)), call);
    }
    merge(k, u, v);
  }
};