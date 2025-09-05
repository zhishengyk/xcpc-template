#include <bits/stdc++.h>
using namespace std;
#include <vector>
using namespace std;

template <typename T = long long>
struct bit {
    vector<T> v;   // 1-based 树状数组
    int n;         // 长度

    // 构造函数，可直接传入数组大小
    bit(int _n = 0) { init(_n); }

    // 重新初始化
    void init(int _n) {
        n = _n;
        v.assign(n + 1, 0);
    }

    // 低位运算
    static int lowbit(int x) { return x & -x; }

    // 单点加值：在 idx 位置加 delta
    void add(int idx, T delta) {
        for (; idx <= n; idx += lowbit(idx))
            v[idx] += delta;
    }

    // 前缀和：查询 [1..idx] 的和
    T sum(int idx) const {
        T res = 0;
        for (; idx > 0; idx -= lowbit(idx))
            res += v[idx];
        return res;
    }

    // 区间和：查询 [l..r] 的和
    T range_sum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }
};
set <int> st[4];
void solve() {
    int n,q;
    cin >> n >> q;
    vector <bit<int>> t(4,bit <int> (n + 1));
    string s;
    cin >> s;
    s = " " + s;
    for(int i=1;i<=n;i++) {
        char x = s[i] ;
        t[x - 'a'].add(i,1);
        st[x - 'a'].insert(i);
    }
    auto get1 = [&](){// ac
        if(st[0].size() == 0 || st[2].size() == 0 ) return 0;
        auto p1 = *st[0].begin();
        auto p2 = *st[2].rbegin();
        return t[1].range_sum(p1,p2);
    };
    auto get2 = [&]() {
        // ab
        if(st[0].size() == 0 || st[1].size() == 0) return 0;
        auto p1 = *st[0].begin();
        auto p2 = st[1].lower_bound(p1);
        if(p2 == st[1].end()) return 0;
//			cout << p1 << " " << *p2 << "\n";
        return t[2].range_sum(*p2 + 1,n);

    };
    auto get3 = [&]() {
        // bc
        if(st[1].size() ==0 || st[2].size() == 0) return 0;
        auto p1 = *st[2].rbegin();
        auto p2 = st[1].lower_bound(p1);
        if(p2 == st[1].begin()) return 0;
        p2 = prev(p2);
	
        return t[0].range_sum(1,*p2);
    };
    while(q -- ) {
        int pos;
        char c;
        cin >> pos >> c;
        char pre = s[pos];
//		cout << pre << " ";
        s[pos] = c;
        t[pre - 'a'].add(pos,-1);
        st[pre - 'a'].erase(pos);
        t[c - 'a'].add(pos,1);
        st[c - 'a'].insert(pos);
	
        int ans = min({get3(),get2(),get1()});
        cout << max(ans,0) << "\n";
    }




}
signed main() {
    ios::sync_with_stdio(0),cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t -- ) solve();
    return 0;
}
