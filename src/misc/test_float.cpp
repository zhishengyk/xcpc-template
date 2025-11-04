constexpr int N = 1e8;

volatile double res = 1.0;
volatile double add = 1.0000001;
volatile double sub = 0.0000001;
volatile double mul = 1.0000002;
volatile double div = 1.0000003;

for (int i = 1; i <= N; i++) {
  res += add;
  res -= sub;
  res *= mul;
  res /= div;
}

cout << fixed << setprecision(10) << res << '\n';
