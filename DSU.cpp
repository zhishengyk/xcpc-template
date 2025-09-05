struct DSU {
    int n;
    std::vector<int> fa, sz;
    DSU(int n): n(n) {
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 0; i <= n; i ++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x) {
        if (x == fa[x]) return fa[x];
        return fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int dx = find(x), dy = find(y);
        if (dx != dy) {
            sz[dy] += sz[dx];
            fa[dx] = dy;
            return true;
        }
        return false;
    }
};