#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <int P>
struct modint {
  u64 x;
  
  constexpr modint() : x(0) {}
  constexpr modint(auto _x) : x(_x) {}
  
  constexpr modint pow(u64 b) const {
    modint res{1};
    for (modint a{*this}; b; b >>= 1, a *= a) {
      if (b & 1) res *= a;
    }
    return res;
  }
  constexpr modint inv() const { return pow(P - 2); }
  constexpr friend istream& operator>> (istream& is, modint& val) { return is >> val.x; }
  constexpr friend ostream& operator<< (ostream& os, const modint& val) { return os << val.x; }
  constexpr modint& operator+= (const modint& rhs) { x += rhs.x, x = min(x, x - P); return *this; }
  constexpr modint& operator-= (const modint& rhs) { x -= rhs.x, x = min(x, x + P); return *this; }
  constexpr modint& operator*= (const modint& rhs) { (x *= rhs.x)       %= P; return *this; }
  constexpr modint& operator/= (const modint& rhs) { (x *= rhs.inv().x) %= P; return *this; }
  constexpr friend modint operator+ (const modint& lhs, const modint& rhs) { return modint{lhs} += rhs; }
  constexpr friend modint operator- (const modint& lhs, const modint& rhs) { return modint{lhs} -= rhs; }
  constexpr friend modint operator* (const modint& lhs, const modint& rhs) { return modint{lhs} *= rhs; }
  constexpr friend modint operator/ (const modint& lhs, const modint& rhs) { return modint{lhs} /= rhs; }
};

namespace combination {
  constexpr int N = 1e6 + 10;
  constexpr int P = 998244353;
  using m32 = modint<P>;
  m32 fac[N + 1];
  m32 inv[N + 1];
  m32 pw2[N + 1];
  m32 pw3[N + 1];

  void init() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i;
    inv[N] = fac[N].inv();
    for (int i = N; i >= 1; i--) inv[i - 1] = inv[i] * i;
    pw2[0] = 1;
    for (int i = 1; i <= N; i++) pw2[i] = pw2[i - 1] + pw2[i - 1];
    pw3[0] = 1;
    for (int i = 1; i <= N; i++) pw3[i] = pw3[i - 1] * 3;
  }
  m32 C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * inv[n - m] * inv[m];
  }
  m32 A(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * inv[n - m];
  }
  m32 pow2(int n) {
    if (n < 0) return 0;
    return pw2[n];
  }
  m32 pow3(int n) {
    if (n < 0) return 0;
    return pw3[n];
  }
};