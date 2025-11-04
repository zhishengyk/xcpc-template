i64 cycle_count(int n, int m, const vector<vector<int>>& G) {
  i64 res = 0;
  vector<vector<i64>> f((1 << n), vector<i64>(n));
  for (int i = 0; i < n; i++) f[1 << i][i] = 1;
  for (int s = 1; s < (1 << n); s++) {
    for (int i = 0; i < n; i++) {
      if (!f[s][i]) continue;
      for (auto j : G[i]) {
        if ((s & -s) > (1 << j)) continue;
        if (s >> j & 1) {
          if ((s & -s) == (1 << j)) res += f[s][i];
        } else f[s | (1 << j)][j] += f[s][i];
      }
    }
  }
  return (res - m) >> 1;
}