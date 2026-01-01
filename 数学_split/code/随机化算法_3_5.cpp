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
    static void initW(int _log) {
        const int r = 1 << _log;
        if (w.size() >= r) {
            return;
        }
        w.assign(r, 0);
        w[r >> 1] = 1;
        T s = power(3, (P - 1) >> _log); // 3是原根

        for (int i = r / 2 + 1; i < r; i++) {
            w[i] = mul(w[i - 1], s);
        }

        for (int i = r / 2 - 1; i > 0; i--) {
            w[i] = w[i * 2];
        }
    }

public:
    using std::vector<T>::vector;

    friend void dft(Polynomial &a) {
        const int n = a.size();
        for (int k = n >> 1; k; k >>= 1) {
            for (int i = 0; i < n; i += k << 1) {
                for (int j = 0; j < k; j++) {
                    T v = a[i + j + k];
                    a[i + j + k] = mul(sub(a[i + j], v), w[k + j]);
                    a[i + j] = add(a[i + j], v);
                }
            }
        }
    }
    friend void idft(Polynomial &a) {
        const int n = a.size();
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += k << 1) {
                for (int j = 0; j < k; j++) {
                    T u = a[i + j];
                    T v = mul(a[i + j + k], w[j + k]);
                    a[i + j + k] = sub(u, v);
                    a[i + j] = add(u, v);
                }
            }
        }
        T val = P - (P - 1) / n;
        for (int i = 0; i < n; i++) {
            a[i] = mul(a[i], val);
        }
        std::reverse(a.begin() + 1, a.end());
    }

    friend Polynomial operator*(Polynomial a, Polynomial b) {
        if (a.size() == 0 or b.size() == 0) {
            return Polynomial();
        }
        int n = a.size() + b.size() - 1;
        int _log = std::__lg(2 * n - 1);
        int s = 1 << _log;
        if (((P - 1) & (s - 1)) != 0 or std::min(a.size(), b.size()) < 128) {
            Polynomial res(n);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    res[i + j] = add(res[i + j], mul(a[i], b[j]));
                }
            }
            return res;
        }

        initW(_log);
        a.resize(s), b.resize(s);
        dft(a), dft(b);
        for (int i = 0; i < s; i++) {
            a[i] = mul(a[i], b[i]);
        }
        idft(a);
        return a.resize(n), a;
    }
    friend Polynomial deriv(const Polynomial &a) // 求导 {
        int n = a.size();
        if (n <= 1) {
            return Polynomial();
        }
        Polynomial p(n - 1);
        for (int i = 1; i < n; i++) {
            p[i - 1] = mul(i, a[i]);
        }
        return p;
    }
    friend Polynomial integr(const Polynomial &a) {
        int n = a.size();
        Polynomial p(n + 1);

        std::vector<int> _inv(n + 1);
        _inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            _inv[i] = mul(_inv[P % i], (P - P / i));
        }
        for (int i = 0; i < n; ++i) {
            p[i + 1] = mul(a[i], _inv[i + 1]);
        }
        return p;
    }
    friend Polynomial inv(const Polynomial &a) {
        int n = a.size();
        if (n == 1) {
            return {power(a[0], P - 2)};
        }
        Polynomial half(a.begin(), a.begin() + (n + 1) / 2);
        Polynomial b = inv(half), c = a * b;
        for (auto &x : c) {
            x = (x == 0 ? 0 : P - x); // ?
        }
        c[0] = add(c[0], 2);
        c = c * b;
        c.resize(n);
        return c;
    }

    friend Polynomial ln(const Polynomial &a) {
        int n = a.size();

        Polynomial b(n, 0);
        for (int i = 1; i < n; i++) {
            b[i - 1] = mul(i, a[i]);
        }
        b = b * inv(a);
        b.resize(n);

        std::vector<T> _inv(n);
        _inv[1] = 1;
        for (int i = 2; i < n; i++) {
            _inv[i] = mul(P - P / i, _inv[P % i]);
        }
        for (int i = n - 1; i; i--) {
            b[i] = mul(b[i - 1], _inv[i]);
        }
        b[0] = 0;
        return b;
    }

    friend Polynomial exp(const Polynomial &a) {
        int n = a.size();
        if (n == 1) {
            return {1};
        }
        Polynomial half(a.begin(), a.begin() + (n + 1) / 2);
        Polynomial b = exp(half);
        b.resize(n);
        Polynomial c = ln(b);
        for (int i = 0; i < n; i++) {
            c[i] = sub(a[i], c[i]);
        }
        c[0] = add(c[0], 1);
        c = c * b;
        c.resize(n);
        return c;
    }

    friend Polynomial power(Polynomial &F, std::string s) {
        T k1 = 0;
        T k2 = 0;
        T k3 = 0;
        for (int i = 0; i < s.length(); ++i) {
            k1 = add(mul(k1, 10), s[i] - '0');
            k2 = (1ll * k2 * 10 + s[i] - '0') % (P - 1);
            if (i < 7) {
                k3 = k3 * 10 + s[i] - '0';
            }
        }
        int n = F.size();
        if (!F[0] and k3 >= F.size()) {
            F.assign(n, 0);
            return F;
        }
        T pos = 0; // 处理移位
        for (int i = 0; i < n; ++i) {
            if (F[i]) {
                pos = i;
                break;
            }
        }
        if (pos) {
            for (int i = pos; i < n; ++i) {
                F[i - pos] = F[i];
                F[i] = 0;
            }
        }
        T val = F[0];
        T cur = power(val, P - 2);
        for (int i = 0; i < F.size(); ++i) {
            F[i] = mul(F[i], cur);
        }
        F = ln(F);
        for (int i = 0; i < F.size(); ++i) {
            F[i] = mul(F[i], k1);
        }
        F = exp(F);
        cur = power(val, k2);
        for (int i = 0; i < F.size(); ++i) {
            F[i] = mul(F[i], cur);
        }
        if (pos) {
            pos = (1ll * pos * k1 < n ? pos * k1 : n);
            for (int i = n - 1; i >= 0; --i) {
                if (i + pos < n) {
                    F[i + pos] = F[i];
                }
                F[i] = 0;
            }
        }
        return F;
    }

    friend Polynomial power(const Polynomial &F, int b, int m) // m是目标的区间长度 {
        Polynomial res = {1};
        Polynomial G = F;
        while (b) {
            if (b & 1) {
                res = res * G;
                if (res.size() > m) {
                    res.resize(m);
                }
            }
            G = G * G;
            if (G.size() > m) {
                G.resize(m);
            }
            b >>= 1;
        }
        return res;
    }
};
template <class T, T P>
std::vector<T> Polynomial<T, P>::w;
using Poly = Polynomial<int, 998244353>;