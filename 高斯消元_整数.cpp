#include <bits/stdc++.h>
using namespace std;

struct GaussMod {
	int n;
	long long mod;
	vector<vector<long long>> a; // n x (n+1)
	vector<int> where;           // 每列主元所在行

	GaussMod(int n, long long mod) : n(n), mod(mod), a(n, vector<long long>(n + 1, 0)), where(n, -1) {}

	inline long long norm(long long x) const {
		x %= mod; if (x < 0) x += mod; return x;
	}
	inline long long mul(long long x, long long y) const {
		return (long long)((__int128) x * y % mod);
	}
	long long mod_pow(long long a, long long e) const {
		long long r = 1;
		for (a = norm(a); e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
		return r;
	}
	long long inv(long long x) const {
		// 要求 mod 为素数；否则请改为 exgcd 并处理不可逆情况
		return mod_pow(x, mod - 2);
	}

	// 返回：-1 无解；0 无穷多解；1 唯一解。唯一解写入 x（0..mod-1）
	int solve(vector<long long>& x) {
		int row = 0;
		for (int col = 0; col < n && row < n; ++col) {
			int sel = -1;
			for (int i = row; i < n; ++i) if (a[i][col] % mod != 0) { sel = i; break; }
			if (sel == -1) continue;
			if (sel != row) swap(a[sel], a[row]);
			where[col] = row;

			long long inv_piv = inv(a[row][col]);
			for (int j = col; j <= n; ++j) a[row][j] = mul(a[row][j], inv_piv);

			for (int i = 0; i < n; ++i) if (i != row) {
				long long fac = a[i][col];
				if (fac) {
					for (int j = col; j <= n; ++j) {
						a[i][j] = norm(a[i][j] - mul(fac, a[row][j]));
					}
				}
			}
			++row;
		}

		for (int i = 0; i < n; ++i) {
			bool all0 = true;
			for (int j = 0; j < n; ++j) if (a[i][j] % mod != 0) { all0 = false; break; }
			if (all0 && a[i][n] % mod != 0) return -1; // 0 = 非零
		}

		x.assign(n, 0);
		int rank = 0;
		for (int j = 0; j < n; ++j) if (where[j] != -1) {
			x[j] = norm(a[where[j]][n]);
			++rank;
		}
		if (rank < n) return 0; // 自由元存在
		return 1;               // 唯一解
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; long long mod;
	if (!(cin >> n >> mod)) return 0;
	GaussMod g(n, mod);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j) {
			long long v; cin >> v;
			g.a[i][j] = g.norm(v);
		}
	}

	vector<long long> x;
	int res = g.solve(x);
	if (res == -1) cout << -1 << "\n";
	else if (res == 0) cout << 0 << "\n";
	else {
		for (int i = 0; i < n; ++i) cout << "x" << (i + 1) << "=" << x[i] << "\n";
	}
	return 0;
}