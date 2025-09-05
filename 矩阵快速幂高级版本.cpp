#include <bits/stdc++.h>
using namespace std;
namespace OY {
    template <typename _Tp, uint32_t _M, uint32_t _N>
    struct StaticMatrix {
        _Tp m_val[_M][_N];
        static constexpr uint32_t row() { return _M; }
        static constexpr uint32_t column() { return _N; }
        static StaticMatrix<_Tp, _M, _N> raw(_Tp __a) {
            StaticMatrix<_Tp, _M, _N> res;
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) res[i][j] = __a;
            return res;
        }
        static StaticMatrix<_Tp, _M, _M> unit() {
            static_assert(_M == _N);
            StaticMatrix<_Tp, _M, _M> res{};
            for (uint32_t i = 0; i < _M; i++) res[i][i] = 1;
            return res;
        }
        _Tp *operator[](uint32_t __i) { return m_val[__i]; }
        const _Tp *operator[](uint32_t __i) const { return m_val[__i]; }
        StaticMatrix<_Tp, _M, _N> &operator+=(_Tp __a) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) m_val[i][j] += __a;
            return *this;
        }
        StaticMatrix<_Tp, _M, _N> &operator-=(_Tp __a) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) m_val[i][j] -= __a;
            return *this;
        }
        StaticMatrix<_Tp, _M, _N> &operator*=(_Tp __a) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) m_val[i][j] *= __a;
            return *this;
        }
        StaticMatrix<_Tp, _M, _N> &operator+=(const StaticMatrix<_Tp, _M, _N> &__other) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) m_val[i][j] += __other[i][j];
            return *this;
        }
        StaticMatrix<_Tp, _M, _N> &operator-=(const StaticMatrix<_Tp, _M, _N> &__other) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) m_val[i][j] -= __other[i][j];
            return *this;
        }
        StaticMatrix<_Tp, _M, _M> pow(uint64_t __n) const {
            static_assert(_M == _N);
            StaticMatrix<_Tp, _M, _M> res = unit(), a = *this;
            while (__n) {
                if (__n & 1) res = res * a;
                a = a * a;
                __n >>= 1;
            }
            return res;
        }
        template <typename _Fp>
        friend StaticMatrix<_Tp, _M, _N> operator+(const StaticMatrix<_Tp, _M, _N> &__a, const _Fp &__b) { return StaticMatrix<_Tp, _M, _N>(__a) += __b; }
        template <typename _Fp>
        friend StaticMatrix<_Tp, _M, _N> operator-(const StaticMatrix<_Tp, _M, _N> &__a, const _Fp &__b) { return StaticMatrix<_Tp, _M, _N>(__a) -= __b; }
        friend StaticMatrix<_Tp, _M, _N> operator*(const StaticMatrix<_Tp, _M, _N> &__a, const _Tp &__b) { return StaticMatrix<_Tp, _M, _N>(__a) *= __b; }
        template <uint32_t _L>
        friend StaticMatrix<_Tp, _M, _L> operator*(const StaticMatrix<_Tp, _M, _N> &__a, const StaticMatrix<_Tp, _N, _L> &__b) {
            StaticMatrix<_Tp, _M, _L> res{};
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++) {
                    _Tp a = __a[i][j];
                    for (uint32_t k = 0; k < _L; k++) res[i][k] += a * __b[j][k];
                }
            return res;
        }
        friend bool operator==(const StaticMatrix<_Tp, _M, _N> &__a, const StaticMatrix<_Tp, _M, _N> &__b) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++)
                    if (__a[i][j] != __b[i][j]) return false;
            return true;
        }
        friend bool operator!=(const StaticMatrix<_Tp, _M, _N> &__a, const StaticMatrix<_Tp, _M, _N> &__b) {
            for (uint32_t i = 0; i < _M; i++)
                for (uint32_t j = 0; j < _N; j++)
                    if (__a[i][j] != __b[i][j]) return true;
            return false;
        }
    };
};
const int MOD = 1e9 + 7;
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
int main() {
    int n;
    cin >> n;
    OY::StaticMatrix<Mint, 1, 8> init{{{1, 0, 0, 0, 0, 0, 0, 0}}};
    OY::StaticMatrix<Mint, 8, 8> P{{{24, 1, 0, 1, 0, 0, 0, 0},
                                    {23, 1, 1, 1, 0, 0, 0, 0},
                                    {24, 1, 0, 0, 0, 1, 0, 0},
                                    {23, 1, 0, 1, 1, 0, 0, 0},
                                    {24, 0, 0, 1, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 1, 24, 1},
                                    {0, 0, 0, 0, 0, 1, 25, 0},
                                    {0, 0, 0, 0, 0, 1, 24, 0}}};
    auto res = init * (P.pow(n));
    cout << res[0][5] + res[0][6] + res[0][7];
    return 0;
}