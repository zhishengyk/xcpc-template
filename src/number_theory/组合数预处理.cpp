template <class T, T P>
struct Comb {
    void norm(ll &x) {
        if (x >= P) {
            x -= P;
        }
        if (x < 0) {
            x += P;
        }
    }
    void norm(int &x) {
        if (x >= P) {
            x -= P;
        }
        if (x < 0) {
            x += P;
        }
    }
    ll mul(ll a, ll b) {
        ll res = a * b - (ll)(1.L * a * b / P) * P;
        res %= P;
        norm(res);
        return res;
    }
    int mul(int a, int b) {
        int res = 1ll * a * b % P;
        norm(res);
        return res;
    }
    std::vector<T> fac, ifac, inv;
    T power(T a, T b) {
        T res = 1;
        while (b) {
            if (b & 1) {
                res = mul(res, a);
            }
            a = mul(a, a);
            b >>= 1;
        }
        return res;
    }
    T getInv(T a) {
        return power(a, P - 2);
    }
    void init(int n) {
        fac.resize(n + 1);
        ifac.resize(n + 1);
        inv.resize(n + 1);
        fac[0] = 1; // 从0开始
        for (T i = 1; i <= n; i++) {
            fac[i] = mul(i, fac[i - 1]);
        }
        ifac[n] = getInv(fac[n]);
        for (T i = n; i >= 1; i--) {
            ifac[i - 1] = mul(i, ifac[i]);
            inv[i] = mul(ifac[i], fac[i - 1]);
        }
    }
    T A(int a, int b) {
        return mul(fac[a], ifac[a - b]);
    }
    T C(int a, int b) {
        if (a < b or b < 0) {
            return 0;
        }
        return mul(A(a, b), ifac[b]);
    }
    Comb(int n) {
        init(n);
    }
};