
#include <bits/stdc++.h>
using namespace std;

template<typename T = long double>
struct Gauss {
	int n;
	vector<vector<T>> a;      // n x (n+1) 增广矩阵
	T eps;
	vector<int> where;        // 每一列的主元所在行

	Gauss(int n, T eps = (T)1e-10) : n(n), a(n, vector<T>(n + 1)), eps(eps), where(n, -1) {}

	// 返回：-1 无解；0 无穷多解；1 唯一解。唯一解写入 x
	int solve(vector<T>& x) {
		int row = 0;
		for (int col = 0; col < n && row < n; ++col) {
			int sel = row;
			for (int i = row; i < n; ++i)
				if (fabsl((long double)a[i][col]) > fabsl((long double)a[sel][col])) sel = i;
			if (fabsl((long double)a[sel][col]) <= (long double)eps) continue;
			swap(a[sel], a[row]);
			where[col] = row;

			T div = a[row][col];
			for (int j = col; j <= n; ++j) a[row][j] /= div;

			for (int i = 0; i < n; ++i) if (i != row) {
				T fac = a[i][col];
				if (fabsl((long double)fac) > (long double)eps) {
					for (int j = col; j <= n; ++j) a[i][j] -= fac * a[row][j];
				}
			}
			++row;
		}
		// 判无解：0=非零
		for (int i = 0; i < n; ++i) {
			bool all0 = true;
			for (int j = 0; j < n; ++j)
				if (fabsl((long double)a[i][j]) > (long double)eps) { all0 = false; break; }
			if (all0 && fabsl((long double)a[i][n]) > (long double)eps) return -1;
		}

		x.assign(n, 0);
		int rank = 0;
		for (int j = 0; j < n; ++j) if (where[j] != -1) {
			x[j] = a[where[j]][n];
			++rank;
		}
		if (rank < n) return 0;   
		return 1;                
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	if (!(cin >> n)) return 0;
	Gauss<long double> g(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= n; ++j) {
			long double v; cin >> v;
			g.a[i][j] = v;
		}

	vector<long double> x;
	int res = g.solve(x);
	if (res == -1) {
		cout << -1 << "\n";
	} else if (res == 0) {
		cout << 0 << "\n";
	} else {
		cout.setf(std::ios::fixed);
		cout << setprecision(2);
		for (int i = 0; i < n; ++i) {
			long double xi = x[i];
			if (fabsl((long double)xi) < 5e-4L) xi = 0; // 避免打印 -0.00
			cout << "x" << (i + 1) << "=" << (double)xi << "\n";
		}
	}
	return 0;
}
