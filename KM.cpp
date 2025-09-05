auto solve = [&](vector<vector<long long>> &a, int n) {
	const long long INF = numeric_limits<long long>::max();
	vector<long long> hl(n), hr(n), slk(n);
	vector<int> fl(n, -1), fr(n, -1), vl(n), vr(n), pre(n), q(n), match(n);
	int ql = 0, qr = 0;
	auto check = [&](int i) {
		if (vl[i] = 1, fl[i] != -1) return vr[q[qr++] = fl[i]] = 1;
		while (i != -1) swap(i, fr[fl[i] = pre[i]]);
		return 0;
	};
	auto bfs = [&](int s) {
		fill(slk.begin(), slk.end(), INF);
		fill(vl.begin(), vl.end(), 0);
		fill(vr.begin(), vr.end(), 0);
		for (vr[q[ql = 0] = s] = qr = 1; ; ) {
			for (long long d; ql < qr; )
				for (int i = 0, j = q[ql++]; i < n; i++)
					if (!vl[i] && slk[i] >= (d = hl[i] + hr[j] - a[i][j]))
						if (pre[i] = j, d) slk[i] = d;
			else if (!check(i)) return;
			long long d = INF;
			for (int i = 0; i < n; i++)
				if (!vl[i] && d > slk[i]) d = slk[i];
			for (int i = 0; i < n; i++) {
				if (vl[i]) hl[i] += d;
				else slk[i] -= d;
				if (vr[i]) hr[i] -= d;
			}
			for (int i = 0; i < n; i++)
				if (!vl[i] && !slk[i] && !check(i)) return;
		}
	};
	for (int i = 0; i < n; i++) hl[i] = *max_element(a[i].begin(), a[i].end());
	for (int j = 0; j < n; j++) bfs(j);
	long long ans = 0;
	for (int i = 0; i < n; i++) ans += a[i][fl[i]];
	for (int i = 0; i < n; i++) match[fl[i]] = i;
	return make_pair(ans, match);
};