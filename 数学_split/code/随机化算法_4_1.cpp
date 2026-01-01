using ll = long long;

template <class T, T P>
class Polynomial : public std::vector<T> {
    static constexpr int mul(const int &a, const int &b) {
        int res = 1ll * a * b % P;
        if (res < 0)
            res += P;
        return res;
    }
    static constexpr ll mul(const ll &a, const ll &b) {
        ll res = a * b - (ll)(1.L * a * b / P) * P;
        res %= P;
        if (res < 0) {
            res += P;
        }
        return res;
    }
    static constexpr T add(T a, const T &b) {
        a += b;
        a -= (a >= P ? P : 0);
        return a;
    }
    static constexpr T sub(T a, const T &b) {
        a -= b;
        a += (a < 0 ? P : 0);
        return a;
    }
    static constexpr T power(T a, ll b) {
        T res = 1;
        while (b) {
            if (b & 1)
                res = mul(res, a);
            a = mul(a, a);
            b >>= 1;
        }
        return res;
    }
    static std::vector<T> w;

public:
    using std::vector<T>::vector;
    friend void FWT_or(Polynomial &f, int op) {
        int n = std::__lg(f.size());
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < (1 << n); ++i) {
                if (i & (1 << k)) {
                    f[i] = add(f[i], mul(op, f[i ^ (1 << k)]));
                }
            }
        }
    }

    friend Polynomial fwtOr(Polynomial &F, Polynomial &G) { // H[i]=F[j]*G[k] if(j or k==i)
        int n = std::max(F.size(), G.size());
        int s = std::__lg(n - 1);
        n = (1 << (s + 1));
        Polynomial H(n);
        F.resize(n), G.resize(n);
        FWT_or(F, 1);
        FWT_or(G, 1);
        for (int i = 0; i < n; ++i) {
            H[i] = mul(F[i], G[i]);
        }
        FWT_or(H, -1);
        FWT_or(F, -1);
        FWT_or(G, -1);
        return H;
    }

    friend void FWT_and(Polynomial &f, int op) {
        int n = std::__lg(f.size());
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < (1 << n); ++i) {
                if (!(i & (1 << k))) {
                    f[i] = add(f[i], mul(op, f[i ^ (1 << k)]));
                }
            }
        }
    }

    friend Polynomial fwtAnd(Polynomial &F, Polynomial &G) { // H[i]=F[j]*G[k] if(j and k==i)
        int n = std::max(F.size(), G.size());
        int s = std::__lg(n - 1);
        n = (1 << (s + 1));
        F.resize(n), G.resize(n);
        Polynomial H(n);
        FWT_and(F, 1);
        FWT_and(G, 1);
        for (int i = 0; i < n; ++i) {
            H[i] = mul(F[i], G[i]);
        }
        FWT_and(H, -1);
        FWT_and(F, -1);
        FWT_and(G, -1);
        return H;
    }

    friend void FWT_xor(Polynomial &f, int op) {
        int n = std::__lg(f.size());
        for (int d = 1; d < (1 << n); d <<= 1) {
            for (int i = 0; i < (1 << n); i += (d << 1)) { // 从最小的二进制位地推上去
                for (int j = 0; j < d; ++j) {
                    T x = f[i + j], y = f[i + d + j];
                    f[i + j] = add(x, y);
                    f[i + j + d] = sub(x, y);
                }
            }
        }
        if (op == -1) {
            T inv_n = power(1 << n, P - 2);
            for (int i = 0; i < (1 << n); ++i) {
                f[i] = mul(f[i], inv_n);
            }
        }
    }
    friend Polynomial fwtXor(Polynomial &F, Polynomial &G) { // H[i]=F[j]*G[k] if(j xor k==i)
        int n = std::max(F.size(), G.size());
        int s = std::__lg(n - 1);
        n = (1 << (s + 1));
        F.resize(n), G.resize(n);
        Polynomial H(n);
        FWT_xor(F, 1);
        FWT_xor(G, 1);
        for (int i = 0; i < n; ++i) {
            H[i] = mul(F[i], G[i]);
        }
        FWT_xor(H, -1);
        FWT_xor(F, -1);
        FWT_xor(G, -1);
        return H;
    }

    friend Polynomial SubsetConvol(Polynomial &F, Polynomial &G) { // 子集卷积 H[i]=F[j]*G[k] if( j|k==i and j&k==0)
        int n = std::max(F.size(), G.size());
        int bit = std::__lg(n - 1) + 1;
        n = (1 << bit);
        F.resize(n), G.resize(n);
        std::vector a(bit + 1, Polynomial(n));
        std::vector b(bit + 1, Polynomial(n));
        std::vector c(bit + 1, Polynomial(n));
        for (int i = 0; i < n; ++i) {
            a[__builtin_popcount(i)][i] = F[i];
            b[__builtin_popcount(i)][i] = G[i];
        }
        for (int i = 0; i <= bit; ++i) {
            FWT_or(a[i], 1);
            FWT_or(b[i], 1);
        }
        for (int i = 0; i <= bit; ++i) {
            for (int j = 0; i + j <= bit; ++j) {
                for (int k = 0; k < (1 << bit); ++k) {
                    c[i + j][k] = add(c[i + j][k], mul(a[i][k], b[j][k]));
                }
            }
        }
        for (int i = 0; i <= bit; ++i) {
            FWT_or(c[i], -1);
        }
        Polynomial H(n);
        for (int i = 0; i < n; ++i) {
            H[i] = c[__builtin_popcount(i)][i];
        }
        return H;
    }
};
template <class T, T P>
std::vector<T> Polynomial<T, P>::w;
using Poly = Polynomial<int, 998244353>;