#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

namespace prime_sieve {
  constexpr int N = 4e6;
  constexpr int M = 2e3;
  vector<int> prime;
  bitset<N + 1> is_prime;

  void init() {
    prime.reserve(N >> 3);
    is_prime.set();
    for (int i = 2; i <= M; i++) {
      if (!is_prime[i]) continue;
      for (int j = i << 1; j <= N; j += i) is_prime[j] = 0;
    }
    for (int i = 2; i <= N; i = is_prime._Find_next(i)) {
      prime.push_back(i);
    }
  }
};