#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, L;
    cin >> n >> L;

    L++;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i] + 1;
    }

    vector<long long> dp(n + 1);

    auto sqr = [&](long long x) {
        return x * x;
    };
    // 把dp式子拆成Y - K * X的形式，其中K与j有关，Y和X与i有关，如果X跟K都单调递增，可以用单调队列维护凸壳
    // dp[i] + sqr(sum[j] - L - sum[i])
    // sum'[j] = sum[j] - L
    // dp[i] + sqr(sum'[j] - sum[i])
    // dp[i] + sqr(sum'[j]) + sqr(sum[i]) - 2 * sqr(sum'[j]) * sum[i]
    // dp[i] + sqr(sum[i]) - 2 * sqr(sum'[j]) * sum[i] + sqr(sum'[j])
    // Y = dp[i] + sqr(sum[i]), K = 2 * sqr(sum'[j]), X = sum[i]
    // sqr(sum'[j]) + Y - K * X

    auto x = [&](int idx) {
        return sum[idx];
    };

    auto y = [&](int idx) {
        return dp[idx] + sqr(sum[idx]);
    };

    auto k = [&](int idx) {
        return 2 * (sum[idx] - L);
    };

    auto cmp = [&](int a, int b, int c) {
        return __int128(y(b) - y(a)) * (x(c) - x(b)) >= __int128(y(c) - y(b)) * (x(b) - x(a));
    };

    vector<int> dq(n + 1);
    int f = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        long long K = k(i);
        // 判断队头是否为最优，如果不是则弹出
        while (f < b && y(dq[f]) - K * x(dq[f]) >= y(dq[f + 1]) - K * x(dq[f + 1])) {
            f++;
        }
        dp[i] = sqr(sum[i] - L) + (y(dq[f]) - K * x(dq[f]));
        // 判断b点是否在凸包内，则判断K(dq[b], dq[b - 1]) >= K(dq[b], i)，如果成立那么b就是凹陷下去的一个点，不在凸包内
        while (f < b && cmp(dq[b - 1], dq[b], i)) {
            b--;
        }
        dq[++b] = i;
    }
    cout << dp[n];
    return 0;
}