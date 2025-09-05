#include <bits/stdc++.h>
using namespace std;
const unsigned long long MOD = 4179340454199820289;
template <unsigned long long M_> struct ModInt {
	static constexpr unsigned long long M = M_;
	long long x;
	constexpr ModInt() : x(0ULL) {}
	constexpr ModInt(unsigned x_) : x(x_ % M) {}
	constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
	constexpr ModInt(int x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
	constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
	constexpr ModInt operator++() { (*this) += 1; return *this; }
	constexpr ModInt operator--() { (*this) -= 1; return *this; }
	constexpr ModInt operator++(int) { const ModInt temp = *this; ++(*this); return temp; }
	constexpr ModInt operator--(int) { const ModInt temp = *this; --(*this); return temp; }
	ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
	ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
	ModInt &operator*=(const ModInt &a) { x = (static_cast<__int128_t>(x) * a.x) % M; return *this; }
	ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
	ModInt pow(long long e) const {
		if (e < 0) return inv().pow(-e);
		ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
	}
	ModInt inv() const {
		return pow(MOD - 2);
	}
	ModInt operator+() const { return *this; }
	ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0ULL; return a; }
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
std::vector<Mint> P;
int BASE;
void init(int N) {
	BASE = unsigned(std::chrono::steady_clock::now().time_since_epoch().count());
	P = std::vector<Mint>(N + 1);
	P.front() = 1;
	for (int i = 1; i <= N; i++) {
		P[i] = P[i - 1] * BASE;
	}
}
struct hash_type {
	Mint val;
	int len;
	hash_type() : val(0ULL), len(0) {}
	hash_type(char c) : val(c), len(1) {}
	hash_type(Mint _val, int _len) : val(_val), len(_len) {}
	hash_type &operator+=(const hash_type &a) { val = val * P[a.len] + a.val; len += a.len; return *this; }
	hash_type operator+(const hash_type &a) const { return (hash_type(*this) += a); }
	bool operator==(const hash_type &a) const { return (val == a.val && len == a.len); }
	bool operator!=(const hash_type &a) const { return (val != a.val || len != a.len); }
	bool operator<(const hash_type &a) const { return (val == a.val ? len < a.len : val < a.val); }
	bool operator>(const hash_type &a) const { return (val == a.val ? len > a.len : val > a.val); }
};
struct staticHasher {
	std::vector<Mint> m_val;
	staticHasher() {}
	staticHasher(const std::string &s) {
		int n = s.length();
		m_val = std::vector<Mint>(n + 1);
		for (int i = 0; i < n; i++) {
			m_val[i + 1] = m_val[i] * BASE + s[i];
		}
	}
	hash_type get(int l, int r) {
		return hash_type(m_val[r + 1] - m_val[l] * P[r - l + 1], r - l + 1);
	}
};
int main() {
	init(500000);
	
	return 0;
}