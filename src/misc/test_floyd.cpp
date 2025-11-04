constexpr int N = 1000;

vector<vector<int>> f(N + 1, vector<int>(N + 1));
for (int i = 1; i <= N; i++) {
  f[i][i] = 1;
}
for (int i = 1; i <= N; i++) {
  int u = rand() % N + 1;
  int v = rand() % N + 1;
  f[u][v] = 1;
}

for (int i = 1; i <= N; i++) {
  for (int k = 1; k <= N; k++) {
    for (int j = 1; j <= N; j++) {
      f[i][j] |= f[i][k] | f[k][j];
    }
  }
}

for (int i = 1; i <= N; i++) {
  for (int j = 1; j <= N; j++) {
    cout << f[i][j];
  }
  cout << '\n';
}