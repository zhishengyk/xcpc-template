template <typename meta>
struct qpow_block {
  static constexpr int N[4] = {0, 16, 32, 48};
  static constexpr int B = 1 << 16;
  static constexpr int M = B - 1;
  meta data[4][B + 1];
  
  qpow_block(auto x) {
    meta base{x};
    for (int k = 0; k < 4; k++) {
      data[k][0] = 1;
      for (int i = 1; i <= B; i++)
        data[k][i] = data[k][i - 1] * base;
      base = data[k][B];
    }
  }

  meta ask(u64 n) const {
    meta res{1};
    for (int k = 0; k < 4; k++)
      res *= data[k][(n >> N[k]) & M];
    return res;
  }
};