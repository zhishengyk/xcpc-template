#include <bits/stdc++.h>
using namespace std;

/*
    Sparse Table 板子（ST 表）
    --------------------------
    支持在线段树不可修改的情况下的区间幂等运算查询，复杂度：
        • 预处理 O(n log n)
        • 查询 O(1)

    模板参数说明：
        T   —— 元素类型
        F   —— 幂等运算函数对象，满足 F(x,x)=x 且结合律
               典型如 min/max/gcd/按位与/或 等

    使用示例（区间最小值）：
        vector<int> a(n);
        SparseTable<int, std::min<int>> st(a);
        cout << st.query(l, r);
*/

template <typename T, class F>
class SparseTable {
public:
    using value_type = T;
    using Op = F;

    SparseTable() = default;
    explicit SparseTable(const vector<T>& a) { build(a); }

    /* 重新构建 */
    void build(const vector<T>& a) {
        n = (int)a.size();
        if (!n) return;
        int K = __lg(n) + 1;
        st.assign(K, vector<T>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                st[k][i] = Op{}(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    /* 区间查询 [l, r]，0-based */
    T query(int l, int r) const {
        int k = __lg(r - l + 1);
        return Op{}(st[k][l], st[k][r - (1 << k) + 1]);
    }

private:
    int n{};                       // 元素个数
    vector<vector<T>> st;          // st[k][i] 代表区间 [i, i+2^k-1]
};

// ------------------ 示例 ------------------
#ifdef LOCAL_TEST
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // 取最小值示例
    SparseTable<int, std::min<int>> st(a);
    while (q--) {
        int l, r; cin >> l >> r; // 0-based
        cout << st.query(l, r) << '\n';
    }
    return 0;
    /*
            struct Min {
            int operator()(int a, int b) const { return std::min(a, b); }
        };
        SparseTable<int, Min> st_min(a);
    */
}
#endif
