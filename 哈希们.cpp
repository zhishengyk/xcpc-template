const int MOD = 1002417107;
template <unsigned M_> struct ModInt {
    static constexpr unsigned M = M_;
    unsigned x;
    constexpr ModInt() : x(0U) {}
    constexpr ModInt(unsigned x_) : x(x_ % M) {}
    constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
    constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
    constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
    constexpr ModInt operator++() { (*this) += 1; return *this; }
    constexpr ModInt operator--() { (*this) -= 1; return *this; }
    constexpr ModInt operator++(int) { const ModInt temp = *this; ++(*this); return temp; }
    constexpr ModInt operator--(int) { const ModInt temp = *this; --(*this); return temp; }
    ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
    ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
    ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
    ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
    ModInt pow(long long e) const {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
    }
    ModInt inv() const {
        unsigned a = M, b = x; int y = 0, z = 1;
        for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
        assert(a == 1U); return ModInt(y);
    }
    ModInt operator+() const { return *this; }
    ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
    template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
    template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
    template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
    template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
    explicit operator bool() const { return x; }
    bool operator==(const ModInt &a) const { return (x == a.x); }
    bool operator!=(const ModInt &a) const { return (x != a.x); }
    bool operator<(const ModInt &a) const { return (x < a.x); }
    bool operator>(const ModInt &a) const { return (x > a.x); }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
    friend std::istream &operator>>(std::istream &is, ModInt &a) { return is >> a.x; }
};
using Mint = ModInt<MOD>;
const int N = 1e5 + 10;
const int BASE = 10000481;
Mint P[N];
struct DynamicHasher {
    vector<Mint> f;
    string s;
    int n;
    void build(int p, int l, int r) {
        if (l == r) {
            f[p] = s[l];
            return;
        }
        int mid = (l + r) / 2;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        f[p] = f[p << 1] * P[r - mid] + f[p << 1 | 1];
    }
    void change(int p, int l, int r, int x, char y) {
        if (l == r) {
            f[p] = y;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) change(p << 1, l, mid, x, y);
        if (x > mid) change(p << 1 | 1, mid + 1, r, x, y);
        f[p] = f[p << 1] * P[r - mid] + f[p << 1 | 1];
    }
    Mint que(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return f[p];
        int mid = (l + r) / 2;
        if (y <= mid) return que(p << 1, l, mid, x, y);
        if (x > mid) return que(p << 1 | 1, mid + 1, r, x, y);
        return que(p << 1, l, mid, x, mid) * P[y - mid] + que(p << 1 | 1, mid + 1, r, x, y);
    }
    Mint query(int l, int r) {
        return que(1, 1, n, l, r);
    }
    void modify(int pos, char c) {
        change(1, 1, n, pos, c);
    }
    DynamicHasher() {}
    DynamicHasher(string &_s) : n(_s.length()), f(4 * _s.length()), s(_s) { s = " " + s; build(1, 1, n); }
};

struct staticHasher {
    vector<Mint> f;
    string s;
    int n;
    void build() {
        for (int i = 1; i <= n; i++) {
            f[i] = f[i - 1] * BASE + s[i];
        }
    }
    Mint query(int l, int r) {
        return f[r] - f[l - 1] * P[r - l + 1];
    }
    staticHasher() {}
    staticHasher(string &_s) : n(_s.length()), f(_s.length() + 1), s(_s) { s = " " + s; build(); }
};
int main() {
    P[0] = 1;
    for (int i = 1; i < N; i++) P[i] = P[i - 1] * BASE;
}