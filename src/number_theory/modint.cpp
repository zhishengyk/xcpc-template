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