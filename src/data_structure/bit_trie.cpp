template <int N, int B>
struct bit_trie {
  static constexpr int M = []() -> int {
    int res = 1;
    int siz = 1;
    for (int i = 0; i < B; i++) {
      siz = min(N, siz << 1);
      res += siz;
    }
    return res;
  }();
  int lst;
  int rot[N << 1];
  int cnt[M << 4];
  int son[M << 4][2];

  void clear() {
    memset(cnt, 0, sizeof(cnt[0]) * (lst + 1));
    memset(son, 0, sizeof(son[0]) * (lst + 1));
    memset(rot, 0, sizeof(rot));
    lst = 0;
  };
  int nxt(int& p) {
    return p ? p : p = ++lst;
  }
  void add(int x, int u = 0) {
    u = nxt(rot[u]);
    for (int i = B - 1; i >= 0; i--) cnt[u = nxt(son[u][x >> i & 1])]++;
  }
  void del(int x, int u = 0) {
    u = rot[u];
    for (int i = B - 1; i >= 0; i--) cnt[u = son[u][x >> i & 1]]--;
  }
  void merge(int& u, int v) {
    if (!u | !v) return u |= v, void();
    cnt[u] += cnt[v];
    merge(son[u][0], son[v][0]);
    merge(son[u][1], son[v][1]);
  }
  void split(int& u, int& v, int p, int val, int dep) {
    if (!p) return u = v = 0, void();
    if (dep--) {
      if (val >> dep & 1) {
        u = p, v = ++lst;
        son[v][0] = 0;
        split(son[u][1], son[v][1], son[u][1], val, dep);
      } else {
        v = p, u = ++lst;
        son[u][1] = 0;
        split(son[u][0], son[v][0], son[v][0], val, dep);
      }
      cnt[u] = cnt[son[u][0]] + cnt[son[u][1]];
      cnt[v] = cnt[son[v][0]] + cnt[son[v][1]];
    } else {
      u = p;
      v = 0;
    }
  }
};