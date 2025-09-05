#include <bits/stdc++.h>
enum int_size {
    int_4m   = 1 << 20,
    int_8m   = 1 << 21,
    int_16m  = 1 << 22,
    int_32m  = 1 << 23,
    int_64m  = 1 << 24,
    int_128m = 1 << 25,
    int_256m = 1 << 26,
    int_512m = 1 << 27
};

template <typename Info, int Size>
struct Chairman_Tree {
    struct Node {
        Info data;
        int lson;
        int rson;

        Node()
        : data(Info()), lson(0), rson(0) {}
    };
    int last;
    Node node[Size / (sizeof(Node) / sizeof(int))];

    Chairman_Tree()
    : last(0) {}

    void clear() {
        std::fill(node, node + last, Node());
        last = 0;
    }

    void push_up(int p) {
        node[p].data = node[node[p].lson].data + node[node[p].rson].data;
    }

    void build(int &p, int l, int r, Info init) {
        p = ++last;
        if (l == r)
            return (void)(node[p].data = init);
        int m = (l + r) >> 1;
        build(node[p].lson, l, m, init);
        build(node[p].rson, m + 1, r, init);
        push_up(p);
    }

    void build(int &p, int l, int r, std::vector<Info> &init) {
        p = ++last;
        if (l == r)
            return (void)(node[p].data = init[l]);
        int m = (l + r) >> 1;
        build(node[p].lson, l, m, init);
        build(node[p].rson, m + 1, r, init);
        push_up(p);
    }

    void update(int &p, int q, int l, int r, int u, Info x) {
        node[p = ++last] = node[q];
        if (l == r)
            return (void)(node[p].data.update(x, r - l + 1));
        int m = (l + r) >> 1;
        if (u <= m)
            update(node[p].lson, node[q].lson, l, m, u, x);
        else
            update(node[p].rson, node[q].rson, m + 1, r, u, x);
        push_up(p);
    }

    Info query(int p, int q, int l, int r, int L, int R) {
        if (!p || R < l || r < L)
            return Info();
        if (L <= l && r <= R)
            return node[p].data - node[q].data;
        int m = (l + r) >> 1;
        return query(node[p].lson, node[q].lson, l, m, L, R) + query(node[p].rson, node[q].rson, m + 1, r, L, R);
    }
};

struct info {
    int val;

    info(int _val = 0)
    : val(_val) {}

    void update(info tag, int node_size) {
        val += tag.val;
    }

    friend info operator + (info l, info r) {
        return info(l.val + r.val);
    }

    friend info operator - (info l, info r) {
        return info(l.val - r.val);
    }
};

Chairman_Tree<info, int_256m + int_128m> CT;

void code() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> all;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        all.push_back(a[i]);
    }
    all.push_back(1e9);
    std::sort(all.begin(), all.end());
    all.resize(std::unique(all.begin(), all.end()) - all.begin());

    int N = all.size();
    std::vector<int> rt(n + 1);
    for (int i = 1; i <= n; i++) {
        auto it = std::lower_bound(all.begin(), all.end(), a[i]) - all.begin() + 1;
        CT.update(rt[i], rt[i - 1], 1, N, it, 1);
    }

    auto &t = CT.node;
    const auto kth = [&](auto &&self, int p, int q, int l, int r, int k) -> int {
        if (l == r)
            return l;
        int m = (l + r) >> 1;
        int tmp = (t[t[p].lson].data - t[t[q].lson].data).val;
        if (tmp >= k)
            return self(self, t[p].lson, t[q].lson, l, m, k);
        else
            return self(self, t[p].rson, t[q].rson, m + 1, r, k - tmp);
    };
    const auto cntk = [&](auto &&self,int p,int l,int r,int L,int R)->info {
        if(r < L || l > R) return info(0);
        if(l >=L && r <= R) return t[p].data;
        int mid = l + r >> 1;
        return self(self,t[p].lson,l,mid,L,R) + self(self,t[p].rson,mid + 1,r,L,R);

    };

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        auto it = std::lower_bound(all.begin(),all.end(),k) - all.begin() + 1;
        std::cout << cntk(cntk,rt[r],1,N,it,N).val - cntk(cntk,rt[l-1],1,N,it,N).val << "\n";
    }
}