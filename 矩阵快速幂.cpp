template <typename meta, int N>
struct matrix {
  static inline meta init[N][N];
  static inline meta unit[N][N];
  meta data[N][N];

  void clear() { memcpy(data, init, sizeof(init)); }
  void reset() { memcpy(data, unit, sizeof(unit)); }
  constexpr matrix pow(unsigned long long  b) const {
    matrix res{};
    res.reset();
    for (matrix a{*this}; b; b >>= 1, a = a * a)
      if (b & 1) res = a * res;
    return res;
  }
  friend matrix operator* (const matrix& l, const matrix& r) {
    matrix res{};
    res.clear();
    for (int i = 0; i < N; i++)
      for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
          res[i][j] = res[i][j] + l[i][k] * r[k][j];
    return res;
  }
  friend matrix operator+ (const matrix& l, const matrix& r) {
    matrix res{};
    res.clear();
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        res[i][j] = l[i][j] + r[i][j];
    return res;
  }
  meta* operator[] (int x) { return data[x]; }
  const meta* operator[] (int x) const { return data[x]; }
};