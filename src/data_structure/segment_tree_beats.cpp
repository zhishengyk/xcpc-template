template <typename meta>
struct segment_tree {
  vector<meta> data;

  segment_tree(int n) : data(4 << __lg(n + 1)) {}

  inline int lson(int p) { return p << 1; }
  inline int rson(int p) { return p << 1 | 1; }
  void build(auto&& call, int r, int p = 1, int l = 1) {
    if (l + 1 == r) return data[p] = call(l), void();
    int m = (l + r) >> 1;
    build(call, m, lson(p), l);
    build(call, r, rson(p), m);
    data[p].pull(data[lson(p)], data[rson(p)], l, r);
  }
  void add(int L, int R, const auto& x, int r, int p = 1, int l = 1) {
    if (L <= l && r <= R) return data[p].add(x, l, r);
    data[p].push(data[lson(p)], data[rson(p)], l, r);
    int m = (l + r) >> 1;
    if (L < m) add(L, R, x, m, lson(p), l);
    if (R > m) add(L, R, x, r, rson(p), m);
    data[p].pull(data[lson(p)], data[rson(p)], l, r);
  }
  void upd(int L, int R, const auto& x, int r, int p = 1, int l = 1) {
    if (L <= l && r <= R && data[p].upd(x, l, r)) return;
    data[p].push(data[lson(p)], data[rson(p)], l, r);
    int m = (l + r) >> 1;
    if (L < m) upd(L, R, x, m, lson(p), l);
    if (R > m) upd(L, R, x, r, rson(p), m);
    data[p].pull(data[lson(p)], data[rson(p)], l, r);
  }
  meta ask(int L, int R, int r, int p = 1, int l = 1) {
    if (R <= l || r <= L) return meta{};
    if (L <= l && r <= R) return data[p];
    data[p].push(data[lson(p)], data[rson(p)], l, r);
    int m = (l + r) >> 1;
    return ask(L, R, m, lson(p), l) + ask(L, R, r, rson(p), m);
  }
};

struct meta {
  meta() {}
  static meta merge(const meta& lhs, const meta& rhs) {}
  void add(const auto& x, int l, int r) {}
  bool upd(const auto& x, int l, int r) {}
  void pull(meta& lhs, meta& rhs, int l, int r) {}
  void push(meta& lhs, meta& rhs, int l, int r) {}
  friend meta operator+ (const meta& lhs, const meta& rhs) {}
};

/*
  区间 +，区间 max 操作示例
    1. a[i] <- a[i] + x
    2. a[i] <- max(a[i], x)
  min_num: 最小值
  sec_num: 次小值
  min_cnt: 最小值出现次数
  tag: 加法标记
*/

struct meta {
  static constexpr int INF = 1e9;

  int min_num;
  int sec_num;
  int min_cnt;
  int sum;
  int tag;

  meta()
    : min_num(INF), sec_num(INF), min_cnt(0), sum(0),   tag(0) {}
  meta(int val)
    : min_num(val), sec_num(INF), min_cnt(1), sum(val), tag(0) {}
  
  static meta merge(const meta& lhs, const meta& rhs) {
    if (lhs.min_num == INF) return rhs;
    if (rhs.min_num == INF) return lhs;

    meta res{};
    res.sum = lhs.sum + rhs.sum;

    if (lhs.min_num < rhs.min_num) {
      res.min_num = lhs.min_num;
      res.min_cnt = lhs.min_cnt;
      res.sec_num = min(lhs.sec_num, rhs.min_num);
      return res;
    }
    
    if (lhs.min_num > rhs.min_num) {
      res.min_num = rhs.min_num;
      res.min_cnt = rhs.min_cnt;
      res.sec_num = min(lhs.min_num, rhs.sec_num);
      return res;
    }
    
    res.min_num = lhs.min_num;
    res.min_cnt = lhs.min_cnt + rhs.min_cnt;
    res.sec_num = min(lhs.sec_num, rhs.sec_num);
    
    return res;
  }
  void add(const auto& x, int l, int r) {
    min_num += x;
    sec_num += x;
    sum += x * (r - l);
    tag += x;
  }
  bool upd(const auto& x, int l, int r) {
    if (x <= min_num) return true;
    if (x <  sec_num) {
      sum += (x - min_num) * min_cnt;
      min_num = x;
      return true;
    }
    return l + 1 == r;
  }
  void pull(meta& lhs, meta& rhs, int l, int r) {
    *this = merge(lhs, rhs);
  }
  void push(meta& lhs, meta& rhs, int l, int r) {
    int m = (l + r) >> 1;
    lhs.add(tag, l, m);
    rhs.add(tag, m, r);
    lhs.upd(min_num, l, m);
    rhs.upd(min_num, m, r);
    tag = 0;
  }
  friend meta operator+ (const meta& lhs, const meta& rhs) {
    return merge(lhs, rhs);
  }
};