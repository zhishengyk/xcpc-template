#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(random_device{}());
#define int long long 
int random(int l, int r) {
	return rng() % (r - l + 1) + l;
}
const int mod = random((int)1e9,(int)2e9);
using Mint = long long ;
const int N = 3e5;
const int BASE = 10000481;
Mint P[N + 1];
struct hash_type {
	Mint val;
	int len;
	constexpr hash_type() : val(0ULL), len(0) {}
	constexpr hash_type(Mint _val, int _len) : val(_val), len(_len) {}
	hash_type &operator+=(const hash_type &a) { val = val * P[a.len] + a.val; len += a.len; return *this; }
	hash_type operator+(const hash_type &a) const { return (hash_type(*this) += a); }
	bool operator==(const hash_type &a) const { return (val == a.val && len == a.len); }
	bool operator!=(const hash_type &a) const { return (val != a.val || len != a.len); }
	bool operator<(const hash_type &a) const { return (val == a.val ? len < a.len : val < a.val); }
	bool operator>(const hash_type &a) const { return (val == a.val ? len > a.len : val > a.val); }
};
struct staticHasher {
	vector<Mint> m_val;
	staticHasher() {}
	staticHasher(string &s) {
		int n = s.length();
		m_val = vector<Mint>(n + 1);
		for (int i = 0; i < n; i++) {
			m_val[i + 1] = (m_val[i] * BASE + s[i]) %mod;
		}
	}
	hash_type query(int l, int r) {
		return hash_type((m_val[r + 1] - m_val[l] * P[r - l + 1])%mod, r - l + 1);
	}
};
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	P[0] = 1;
	for (int i = 1; i <= N; i++) {
		P[i] = P[i - 1] * BASE;
	}
	return 0;
}