#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <int B>
struct xor_space {
  int cnt;
  int zro;
  i64 data[B];
  int time[B];
  
  constexpr xor_space() { reset(); }

  constexpr void reset() {
    cnt = 0;
    zro = 0;
    fill(data, data + B,  0);
    fill(time, time + B, -1);
  }
  bool add(i64 x, int t) {
    for (int i = B - 1; i >= 0 && x; i--) {
      if (!(x >> i & 1)) continue;
      if (!data[i]) return data[i] = x, time[i] = t, cnt++, true;
      if (time[i] < t) {
        swap(data[i], x);
        swap(time[i], t);
      }
      x ^= data[i];
    }
    zro = t;
    return false;
  }
  i64 ask_max(int l = 0, i64 x = 0) {
    for (int i = B - 1; i >= 0; i--) {
      if (time[i] < l) continue;
      if ((x ^ data[i]) > x) x ^= data[i];
    }
    return x;
  }
  i64 ask_min(int l = 0, i64 x = 0) {
    for (int i = B - 1; i >= 0; i--) {
      if (time[i] < l) continue;
      if (x >> i & 1) x ^= data[i];
    }
    return x;
  }
  friend constexpr xor_space operator& (const xor_space& l, const xor_space& r) {
    xor_space res{l};
    for (int i = 0; i < B; i++) res.add(r.data[i], r.time[i]);
    return res;
  }
  friend constexpr xor_space operator| (const xor_space& l, const xor_space& r) {
    xor_space<B * 2> tmp;
    for (int i = 0; i < B; i++) tmp.add((l.data[i] << B) | l.data[i], l.time[i]);
    for (int i = 0; i < B; i++) tmp.add((r.data[i] << B), r.time[i]);
    xor_space res;
    for (int i = 0; i < B; i++) if (tmp.data[i]) {
      res.data[i] = tmp.data[i];
      res.time[i] = tmp.time[i];
      res.cnt++;
    }
    return res;
  }
};