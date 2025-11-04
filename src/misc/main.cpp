#ifdef LOCAL
  #include "main.hpp"
  #define debug(x) cerr << #x << " = " << x << '\n'
#else
  #pragma GCC optimize("Ofast,unroll-loops")
  #include <bits/stdc++.h>
  #include <bits/extc++.h>
  #define debug(x) void(0)
#endif

using namespace std;
using i64 = long long;
using u64 = unsigned long long;

void code() {
  
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (int i = 1, n = (cin >> n, n); i <= n; i++)
    code();

  return 0;
}