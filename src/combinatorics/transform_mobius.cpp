#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

void supset_mobius(auto& a) {
  int n = a.size();
  assert(n == (n & -n));
  for (int i = 1; i != n; i <<= 1)
    for (int j = 0; j != n; j += i << 1)
      for (int k = 0; k != i; k++) a[j + k] -= a[i + j + k];
}
void subset_mobius(auto& a) {
  int n = a.size();
  assert(n == (n & -n));
  for (int i = 1; i != n; i <<= 1)
    for (int j = 0; j != n; j += i << 1)
      for (int k = 0; k != i; k++) a[i + j + k] -= a[j + k];
}