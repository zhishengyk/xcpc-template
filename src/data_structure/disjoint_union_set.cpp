struct disjoint_union_set {
  vector<int> data;

  disjoint_union_set(int _n) : data(_n + 1, -1) {}

  int find(int x) {
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }
  bool merge(int x, int y) {
    if (x = find(x), y = find(y); x == y) return false;
    if (data[x] < data[y]) data[x] += data[y], data[y] = x;
    else                   data[y] += data[x], data[x] = y;
    return true;
  }
};