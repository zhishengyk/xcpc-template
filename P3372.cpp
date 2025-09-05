#include <bits/stdc++.h>
using namespace std;

// 基于你的懒标记线段树模板，做了 C++14 友好化：
// - 固定 4*n 空间，不使用 std::__lg
// - 仅保留本题需要的接口（build/update/query）

template <typename Info, typename Lazy>
struct Segment_Tree_Lazy {
    Info *node;
    Lazy *post;

    explicit Segment_Tree_Lazy(int n = 0) {
        if (n < 1) n = 1;
        node = new Info[4 * (n + 5)]();
        post = new Lazy[4 * (n + 5)]();
    }

    void push_up(int p) { node[p] = node[p << 1] + node[p << 1 | 1]; }

    void push_down(int p, int l, int r) {
        const int m = (l + r) >> 1;
        const int left_size = m - l + 1;
        const int right_size = r - m;
        auto edit = [&](int u, int node_size) {
            node[u].update(post[p], node_size);
            post[u].update(post[p]);
        };
        edit(p << 1, left_size);
        edit(p << 1 | 1, right_size);
        post[p].clear();
    }

    void build(int p, int l, int r, const vector<Info> &info) {
        if (l == r) {
            node[p] = info[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, info);
        build(p << 1 | 1, m + 1, r, info);
        push_up(p);
    }

    void update(int p, int l, int r, int L, int R, const Lazy &x) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            node[p].update(x, r - l + 1);
            post[p].update(x);
            return;
        }
        int m = (l + r) >> 1;
        push_down(p, l, r);
        update(p << 1, l, m, L, R, x);
        update(p << 1 | 1, m + 1, r, L, R, x);
        push_up(p);
    }

    Info query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return Info();
        if (L <= l && r <= R) return node[p];
        int m = (l + r) >> 1;
        push_down(p, l, r);
        return query(p << 1, l, m, L, R) + query(p << 1 | 1, m + 1, r, L, R);
    }
};

struct Lazy {
    long long add;
    Lazy(long long v = 0) : add(v) {}
    void clear() { add = 0; }
    void update(const Lazy &o) { add += o.add; }
};

struct Info {
    long long s;
    Info(long long _s = 0) : s(_s) {}
    friend Info operator+(const Info &a, const Info &b) { return Info(a.s + b.s); }
    void update(const Lazy &lz, int node_size) { s += lz.add * node_size; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<Info> ini(n + 1);
    for (int i = 1; i <= n; ++i) ini[i] = Info(a[i]);

    Segment_Tree_Lazy<Info, Lazy> st(n);
    st.build(1, 1, n, ini);

    for (int i = 0; i < m; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; long long k; cin >> x >> y >> k;
            st.update(1, 1, n, x, y, Lazy(k));
        } else {
            int x, y; cin >> x >> y;
            cout << st.query(1, 1, n, x, y).s << '\n';
        }
    }
    return 0;
}


