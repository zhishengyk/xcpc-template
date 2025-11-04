constexpr int N = 5e5;

const int b = 4, B = (1 << b); // cache line size (in integers, not bytes)

// the height of the tree over an n-element array 
constexpr int height(int n) {
    return (n <= B ? 1 : height(n / B) + 1);
}

// where the h-th layer starts
constexpr int offset(int h) {
    int s = 0, n = N;
    while (h--) {
        n = (n + B - 1) / B;
        s += n * B;
    }
    return s;
}

constexpr int H = height(N);
alignas(64) int t[offset(H)]; // an array for storing nodes

int sum(int k) {
  int s = 0;
  for (int h = 0; h < H; h++)
      s += t[offset(h) + (k >> (h * b))];
  return s;
}

struct Precalc {
  alignas(64) int mask[B][B];

  constexpr Precalc() : mask{} {
      for (int k = 0; k < B; k++)
          for (int i = 0; i < B; i++)
              mask[k][i] = (i > k ? -1 : 0);
  }
};

constexpr Precalc T;

typedef int vec __attribute__ (( vector_size(32) ));

constexpr int round(int k) {
    return k & ~(B - 1); // = k / B * B
}

void add(int k, int x) {
    vec v = x + vec{};
    for (int h = 0; h < H; h++) {
        auto a = (vec*) &t[offset(h) + round(k)];
        auto m = (vec*) T.mask[k % B];
        for (int i = 0; i < B / 8; i++)
            a[i] += v & m[i];
        k >>= b;
    }
}