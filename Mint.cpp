#include <bits/stdc++.h>
using namespace std;

template <int MOD>
struct modint {
	int val;

	static int norm(long long x) {
		x %= MOD;
		if (x < 0) x += MOD;
		return static_cast<int>(x);
	}
	static constexpr int get_mod() { return MOD; }

	modint() : val(0) {}
	modint(const int& m) : val(norm(m)) {}
	modint(const long long& m) : val(norm(m)) {}

	modint inv() const {
		int a = val, b = MOD, u = 1, v = 0;
		if (a == 0) return modint(0);
		while (b) {
			int t = a / b;
			a -= t * b; swap(a, b);
			u -= t * v; swap(u, v);
		}
		if (a != 1) return modint(0);
		return modint(u);
	}

	modint operator-() const { return modint(norm(-val)); }

	bool operator==(const modint& o) const { return val == o.val; }
	bool operator!=(const modint& o) const { return val != o.val; }
	bool operator<(const modint& o) const { return val < o.val; }

	modint& operator+=(const modint& o) { val += o.val; if (val >= MOD) val -= MOD; return *this; }
	modint& operator-=(const modint& o) { val -= o.val; if (val < 0) val += MOD; return *this; }
	modint& operator*=(const modint& o) { val = static_cast<int>(1ll * val * o.val % MOD); return *this; }
	modint& operator/=(const modint& o) { return *this *= o.inv(); }

	// bitwise ops on underlying integers (no modulo)
	modint& operator^=(const modint& o) { val ^= o.val; return *this; }
	modint& operator>>=(const modint& o) { val >>= o.val; return *this; }
	modint& operator<<=(const modint& o) { val <<= o.val; return *this; }

	modint operator+(const modint& o) const { modint r = *this; r += o; return r; }
	modint operator-(const modint& o) const { modint r = *this; r -= o; return r; }
	modint operator*(const modint& o) const { modint r = *this; r *= o; return r; }
	modint operator/(const modint& o) const { modint r = *this; r /= o; return r; }

	modint operator^(const modint& o) const { modint r = *this; r ^= o; return r; }
	modint operator>>(const modint& o) const { modint r = *this; r >>= o; return r; }
	modint operator<<(const modint& o) const { modint r = *this; r <<= o; return r; }

	friend istream& operator>>(istream& is, modint& a) {
		long long v; is >> v; a.val = norm(v); return is;
	}
	friend ostream& operator<<(ostream& os, const modint& a) { return os << a.val; }
	friend string tostring(const modint& a) { return to_string(a.val); }

    // class qpow: integer exponent only
	template <typename T, typename = enable_if_t<is_integral_v<T>>>
	static modint qpow(modint base, T exp) {
		if constexpr (is_signed_v<T>) {
			if (exp < 0) return modint(0);
		}
		modint result = 1;
		while (exp) {
			if (exp & 1) result *= base;
			base *= base;
			exp >>= 1;
		}
		return result;
	}
};

using M107 = modint<1000000007>;
using M998 = modint<998244353>;

using Mint = M107;
// constexpr int mod = ...;
// using Mint = modint<mod>;

struct Fact {
	vector<Mint> fact, factinv;
	int n;
	Fact(const int& _n) : fact(1, Mint(1)), factinv(1, Mint(1)), n(0) { ensure(_n); }
	void ensure(const int& m) {
		if (m <= n) return;
		fact.resize(m + 1);
		factinv.resize(m + 1);
		for (int i = max(1, n + 1); i <= m; ++i) fact[i] = fact[i - 1] * i;
		factinv[m] = fact[m].inv();
		for (int i = m; i; --i) factinv[i - 1] = factinv[i] * i;
		n = m;
	}
	Mint C(const int& nn, const int& kk) {
		if (nn < 0 || kk < 0 || nn < kk) return 0;
		ensure(nn);
		return fact[nn] * factinv[kk] * factinv[nn - kk];
	}
	Mint A(const int& nn, const int& kk) {
		if (nn < 0 || kk < 0 || nn < kk) return 0;
		ensure(nn);
		return fact[nn] * factinv[nn - kk];
	}
};

// Precompute factorials upper bound. Ensure max n in input <= this value.
static Fact sb(1000001);

static void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	Mint ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (n - i < 0) continue; // avoid negative exponent
		ans += Mint(i) * sb.C(n - i - 1, m - i) / Mint::qpow(Mint(2), n - i);
	}
	ans *= Mint(k);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	if (!(cin >> t)) return 0;
	while (t--) solve();
	return 0;
}