template <typename A, typename B>
struct pair { A first; B second; };

template <typename Info>
struct Segment_Tree {
    // 动态开点：使用子节点索引维护树
    Info *node;
    int *ls, *rs;
    int tot, cap;

    Segment_Tree(int _n = 0) {
        cap = ((_n ? _n * 2 : 8) + 8);
        node = new Info[cap]();
        ls = new int[cap]();
        rs = new int[cap]();
        tot = 1; // 1 作为根，0 为空
    }

    int new_node() {
        ++tot;
        ls[tot] = rs[tot] = 0;
        node[tot] = Info();
        return tot;
    }

    int get_ls(int p) {
        if (!ls[p]) ls[p] = new_node();
        return ls[p];
    }
    int get_rs(int p) {
        if (!rs[p]) rs[p] = new_node();
        return rs[p];
    }

    void push_up(int p) { node[p] = node[ls[p]] + node[rs[p]]; }

    template <typename Arr>
    void build(int p, int l, int r, const Arr &info) {
        if (l == r) {
            node[p] = info[l];
            return;
        }
        const int m = (l + r) >> 1;
        int Lc = get_ls(p);
        int Rc = get_rs(p);
        build(Lc, l, m, info);
        build(Rc, m + 1, r, info);
        push_up(p);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            node[p] = Info();
            return;
        }
        const int m = (l + r) >> 1;
        int Lc = get_ls(p);
        int Rc = get_rs(p);
        build(Lc, l, m);
        build(Rc, m + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int u, Info x) {
        if (u < l || r < u) return;
        if (l == r) {
            node[p].update(x);
            return;
        }
        const int m = (l + r) >> 1;
        if (u <= m) update(get_ls(p), l, m, u, x);
        else update(get_rs(p), m + 1, r, u, x);
        push_up(p);
    }

    Info query(int p, int l, int r, int L, int R) {
        if (p == 0 || R < l || r < L) return Info();
        if (L <= l && r <= R) return node[p];
        const int m = (l + r) >> 1;
        return query(ls[p], l, m, L, R) + query(rs[p], m + 1, r, L, R);
    }

    template <typename Check>
    pair<int,Info> search(int p,int l,int r,int L,int R,Info pre, Check check) {
        if (p == 0 || r < L || R < l) return {-1, Info()};
        if (!check(pre + node[p])) return {-1, node[p]};
        if (l == r) return {l, node[p]};
        int m = (l + r) >> 1;
        auto res = search(ls[p], l, m, L, R, pre, check);
        if (res.first == -1) return search(rs[p], m + 1, r, L, R, pre + res.second, check);
        return res;
    }
};


