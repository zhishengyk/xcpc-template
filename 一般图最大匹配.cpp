struct blossemtree{
    vector<vector<int>> g; 
    queue<int> q;
    vector<int> fa, type, link, Next, vis;
    int n;
    int find(int x) {
        return fa[x] = fa[x] == x ? x : find(fa[x]);
    }
    void add(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void combine(int x,int lca) {
        while (x != lca) {
            int u = link[x], v = Next[u];
            if (find(v) != lca) Next[v] = u;
            if (type[u] == 1) {
                type[u] = 2;
                q.push(u);
            }
            fa[find(x)] = find(u);
            fa[find(u)] = find(v);
            x = v;
        }
    }
    void contrack(int x, int y) {
        int lca = x;
        fill(vis.begin(), vis.end(), false);
        for (int i = x; ~i; i = Next[link[i]]) {
            i = find(i);
            vis[i] = true;
            if (link[i] == -1) break;
        }
        for (int i = y; ~i; i = Next[link[i]]) {
            i = find(i);
            if (vis[i]) {
                lca = i;
                break;
            }
            if (link[i] == -1) break;
        }
        if (lca != find(x)) Next[x] = y;
        if (lca != find(y)) Next[y] = x;
        combine(x, lca);
        combine(y, lca);
    }
    void bfs(int S) {
        fill(type.begin(), type.end(), 0);
        fill(Next.begin(), Next.end(), 0);
        iota(fa.begin(), fa.end(), 0);
        while (!q.empty()) q.pop();
        q.push(S);
        type[S] = 2; 
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto y : g[x]) {
                if (find(x) == find(y) || link[x] == y || type[y] == 1) continue;
                if (type[y] == 2) {
                    contrack(x, y);
                } else if (link[y] != -1) {
                    Next[y] = x;
                    type[y] = 1;
                    type[link[y]] = 2;
                    q.push(link[y]);
                } else {
                    Next[y] = x;
                    int pos = y, u = Next[pos], v = link[u];
                    while (true) {
                        link[pos] = u; 
                        link[u] = pos;
                        if (v == -1) break;
                        pos = v;
                        u = Next[pos];
                        v = link[u];
                    }
                    return;
                }
            }
        }
    }
    int maxmatch() {
        for (int i = 0; i < n; i++) if (link[i] == -1) bfs(i);
        int ans = 0;
        for (int i = 0; i < n; i++) if (link[i] != -1) ans++;
        return ans / 2;
    }
    void init(int _n) {
        n = _n;
        g = vector<vector<int>>(n);
        link = vector<int>(n, -1);
        fa = vector<int>(n);
        type = vector<int>(n);
        Next = vector<int>(n, -1);
        vis = vector<int>(n);
    }
} tree;