constexpr int N = 1e8; 

volatile i64 res = 0;
volatile i64 add = rand();
volatile i64 sub = rand();
volatile i64 mul = rand();
volatile i64 div = rand();
volatile i64 mod = rand();
volatile i64 XOR = rand();
for (int i = 1; i <= N; i++) {
  res += add;
  res -= sub;
  res *= mul;
  res /= div;
  res %= mod;
  res ^= XOR;
}

cout << res << '\n';