vector<int> sz(n + 1), del(n + 1);
long long ans = 0;
function<void(int, int)> dfs_solve = [&](int x, int tot) {
    int root = 0;
    function <void(int, int)> getRoot = [&](int x, int fa) {
        sz[x] = 1;
        int ok = 1;
        for (auto [y, _] : g[x]) {
            if (del[y] || y == fa) continue;
            getRoot(y, x);
            sz[x] += sz[y];
            if (sz[y] > tot / 2) ok = 0; 
        }
        if (tot - sz[x] > tot / 2) ok = 0;
        if (ok) root = x;
    };
    getRoot(x, 0);
    del[root] = 1; 
    vector<int> v1, v2;
    v2.push_back(0);
    function <void(int, int, int)> getAns = [&](int x, int fa, int dep) {
        v1.push_back(dep);
        v2.push_back(dep);
        sz[x] = 1;
        for (auto [y, cost] : g[x]) {
            if (y == fa || del[y]) continue;
            getAns(y, x, dep + cost);
            sz[x] += sz[y]; 
        }
    };
    auto cal = [&](vector<int> &vec) {
    	return 0;
    };
    for (auto [y, cost] : g[root]) {
        if (del[y]) continue;
        v1.clear();
        getAns(y, root, cost);
        ans -= cal(v1);
    }
    ans += cal(v2);
    for (auto [y, _] : g[root]) {
        if (!del[y]) dfs_solve(y, sz[y]);
    }
};
dfs_solve(1, n);
cout << ans;