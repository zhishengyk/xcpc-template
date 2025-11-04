constexpr int N = 5000;

vector<bitset<N + 1>> f(N + 1, bitset<N + 1>());
for (int i = 1; i <= N; i++) {
  f[i][i] = 1;
}
for (int i = 1; i <= N * N / 2; i++) {
  int u = rand() % N + 1;
  int v = rand() % N + 1;
  f[u][v] = 1;
}

for (int i = 1; i <= N; i++) {
  for (int k = 1; k <= N; k++) {
    if (f[i][k]) f[i] |= f[k];
  }
}

for (int i = 1; i <= N; i++) {
  cout << f[i] << '\n';
}