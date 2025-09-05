template <typename Info>
struct Segment_Tree {
    Info *node;

    Segment_Tree(int _n = 0) {
        node = new Info[4 << std::__lg(_n + 1)]();
    }

    void push_up(int p) {
        node[p] = node[p << 1] + node[p << 1 | 1];
    }

    void build(int p, int l, int r, const std::vector<Info> &info) {
        if (l == r)
            return (void)(node[p] = info[l]);
        const int m = (l + r) >> 1;
        build(p << 1, l, m, info);
        build(p << 1 | 1, m + 1, r, info);
        push_up(p);
    }

    void build(int p, int l, int r) {
        if (l == r)
            return (void)(node[p] = Info());
        const int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int u, Info x) {
        if (u < l || r < u)
            return;
        if (l == r)
            return (void)(node[p].update(x));
        const int m = (l + r) >> 1;
        update(p << 1, l, m, u, x);
        update(p << 1 | 1, m + 1, r, u, x);
        push_up(p);
    }

    Info query(int p, int l, int r, int L, int R) {
        if (R < l || r < L)
            return Info();
        if (L <= l && r <= R)
            return node[p];
        const int m = (l + r) >> 1;
        return query(p << 1, l, m, L, R) + query(p << 1 | 1, m + 1, r, L, R);
    }
    int search(int p,int l,int r,int L,int R,Info pre, const auto  check) {

        if(r < L || R < l || !check(pre + node[p])) return -1;
        if(l == r) return l;
        int mid = l + r >> 1;
        auto x = search(p << 1,l,mid,L,R,pre,check);
        if(x == -1) {
            return search(p << 1 | 1,mid + 1, r,L,R,pre + node[p << 1],check);
        }

        return x;
    }
};
struct info {
    info() {
        
    }
    friend info operator + (info l,info r) {
        info res;
        
        return res;
    }
    void update(info x) {
        *this = x;
    }

};