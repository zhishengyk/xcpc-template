#include <bits/stdc++.h>

template <typename Info>
struct Segment_Tree {
    Info *node;

    explicit Segment_Tree(int n = 0) {
        if (n < 1) n = 1;
      
        node = new Info[4 * (n + 5)]();
    }


    void push_up(int p) { node[p] = node[p << 1] + node[p << 1 | 1]; }

    void build(int p, int l, int r, const std::vector<Info> &info) {
        if (l == r) {
            node[p] = info[l];
            return;
        }
        const int m = (l + r) >> 1;
        build(p << 1, l, m, info);
        build(p << 1 | 1, m + 1, r, info);
        push_up(p);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            node[p] = Info();
            return;
        }
        const int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int u, Info x) {
        if (u < l || r < u) return;
        if (l == r) {
            node[p].update(x);
            return;
        }
        const int m = (l + r) >> 1;
        update(p << 1, l, m, u, x);
        update(p << 1 | 1, m + 1, r, u, x);
        push_up(p);
    }

    Info query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return Info();
        if (L <= l && r <= R) return node[p];
        const int m = (l + r) >> 1;
        return query(p << 1, l, m, L, R) + query(p << 1 | 1, m + 1, r, L, R);
    }

    template <typename Check>
    std::pair<int, Info> search(int p, int l, int r, int L, int R, Info pre, Check check) {
        if (r < L || R < l) return std::make_pair(-1, Info());
        if (!check(pre + node[p])) return std::make_pair(-1, node[p]);
        if (l == r) return std::make_pair(l, node[p]);
        int mid = (l + r) >> 1;
        auto left_res = search(p << 1, l, mid, L, R, pre, check);
        if (left_res.first == -1) {
            return search(p << 1 | 1, mid + 1, r, L, R, pre + left_res.second, check);
        }
        return left_res;
    }
};

template <typename Info, typename Lazy>
struct Segment_Tree_Lazy {
    Info *node;
    Lazy *post;

    explicit Segment_Tree_Lazy(int n = 0) {
        if (n < 1) n = 1;
        node = new Info[4 * (n + 5)]();
        post = new Lazy[4 * (n + 5)]();
    }

    // allow copy/assign (shallow, shares storage)

    void push_up(int p) { node[p] = node[p << 1] + node[p << 1 | 1]; }

    void push_down(int p, int l, int r) {
        const int m = (l + r) >> 1;
        const int left_size = m - l + 1;
        const int right_size = r - m;
        auto apply_to_child = [&](int u, int node_size) {
            node[u].update(post[p], node_size);
            post[u].update(post[p]);
        };
        apply_to_child(p << 1, left_size);
        apply_to_child(p << 1 | 1, right_size);
        post[p].clear();
    }

    void build(int p, int l, int r, const std::vector<Info> &info) {
        if (l == r) {
            node[p] = info[l];
            return;
        }
        const int m = (l + r) >> 1;
        build(p << 1, l, m, info);
        build(p << 1 | 1, m + 1, r, info);
        push_up(p);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            node[p] = Info();
            return;
        }
        const int m = (l + r) >> 1;
        build(p << 1, l, m);
        build(p << 1 | 1, m + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int L, int R, Lazy x) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            node[p].update(x, r - l + 1);
            post[p].update(x);
            return;
        }
        const int m = (l + r) >> 1;
        push_down(p, l, r);
        update(p << 1, l, m, L, R, x);
        update(p << 1 | 1, m + 1, r, L, R, x);
        push_up(p);
    }

    Info query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return Info();
        if (L <= l && r <= R) return node[p];
        const int m = (l + r) >> 1;
        push_down(p, l, r);
        return query(p << 1, l, m, L, R) + query(p << 1 | 1, m + 1, r, L, R);
    }

    template <typename Check>
    std::pair<int, Info> search(int p, int l, int r, int L, int R, Info pre, Check check) {
        if (r < L || R < l) return std::make_pair(-1, Info());
        if (!check(pre + node[p])) return std::make_pair(-1, node[p]);
        if (l == r) return std::make_pair(l, node[p]);
        int mid = (l + r) >> 1;
        push_down(p, l, r);
        auto left_res = search(p << 1, l, mid, L, R, pre, check);
        if (left_res.first == -1) {
            return search(p << 1 | 1, mid + 1, r, L, R, pre + left_res.second, check);
        }
        return left_res;
    }
};

#if 0
// ========================= 示例区域（不参与编译） =========================
// 说明：以下示例来源于你的模板，稍作改动并加注释。放在 #if 0 内，不参与编译。

// 一、非懒版本：填空示例（你的 `info` 骨架，适合 Segment_Tree<info>）
// 使用时请补充字段与逻辑；若你同时使用懒版本的 info，请更名避免与下方重名。
struct info { // 非懒 Info（填空）
    // 示例：添加你需要维护的字段
    // long long s;

    info() {}

    // 区间合并：返回合并后的信息
    friend info operator+(info l, info r) {
        info res;
        // 示例：res.s = l.s + r.s;
        return res;
    }

    // 单点更新：将当前位置赋值为 x 对应的值
    void update(info x) {
        *this = x;
    }
};

// 二、懒标记版本：填空示例（空骨架）。
// 用于 Segment_Tree_Lazy<info_lazy, lazy>。根据需要自行填充字段与逻辑。
struct lazy {
    lazy() {}
    void clear() {}
    void update(lazy p) { (void)p; }
};

// ========================= 示例区域结束 =========================
#endif

#endif
 
// 使用例子：洛谷 P3372「线段树 1」
// 需求：区间加、区间求和。下标 1-based，数据范围 1e5，和不超过 2e18。

// 懒标记：表示“整段加 add”
struct Lazy {
    long long add;                 // 对该节点覆盖区间需要加的值
    Lazy(long long v = 0) : add(v) {}
    void clear() { add = 0; }      // 清空标记（向下推后）
    void update(const Lazy &o) {   // 合并父标记到子标记：加法可叠加
        add += o.add;
    }
};

// 节点信息：这里只维护“区间和”即可
struct Info {
    long long s;                   // 该节点覆盖区间的总和
    Info(long long _s = 0) : s(_s) {}
    friend Info operator+(const Info &a, const Info &b) {
        return Info(a.s + b.s);    // 合并左右儿子
    }
    // 懒标记对节点的影响：整段长度为 node_size，每个元素都 +lz.add
    void update(const Lazy &lz, int node_size) { s += lz.add * node_size; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0; // 读 n,m
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i]; // 读初值（1-indexed）

    // 用叶子初值构造 Info 数组
    vector<Info> ini(n + 1);
    for (int i = 1; i <= n; ++i) ini[i] = Info(a[i]);

    // 建树 O(n)
    Segment_Tree_Lazy<Info, Lazy> st(n);
    st.build(1, 1, n, ini);

    // 处理 m 次操作：
    // op=1: 区间 [x,y] 每个数 +k
    // op=2: 查询区间 [x,y] 的和
    for (int i = 0; i < m; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; long long k; cin >> x >> y >> k;
            st.update(1, 1, n, x, y, Lazy(k));
        } else { // op == 2
            int x, y; cin >> x >> y;
            cout << st.query(1, 1, n, x, y).s << '\n';
        }
    }
    return 0;
}
