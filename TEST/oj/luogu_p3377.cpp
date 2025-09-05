#include "DS/DSU.h"
#include "DS/MonoPairHeap.h"
#include "DS/StaticBufferWrapWithCollect.h"
#include "IO/FastIO.h"

/*
[P3377 【模板】左偏树（可并堆）](https://www.luogu.com.cn/problem/P3377)
*/
/**
 * 本题为可并堆模板题
 * 直接用配对堆解决
 */
struct item {
    uint32_t id;
    int32_t value;
    friend bool operator<(const item &x, const item &y) {
        return x.value > y.value || (x.value == y.value and x.id > y.id);
    }
};
OY::MonoPairHeap<item, std::less<item>, OY::StaticBufferWrapWithCollect<100000>::type> S[100000];
OY::DSUTable<true> U;
bool popped[100000];
int main() {
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) {
        int32_t x;
        cin >> x;
        S[i].push(item{i, x});
    }
    U.resize(n);
    while (m--) {
        char op;
        cin >> op;
        if (op == '1') {
            uint32_t x, y;
            cin >> x >> y;
            x--, y--;
            if (popped[x] || popped[y]) continue;
            uint32_t xx = U.find(x), yy = U.find(y);
            if (xx == yy) continue;
            if (U.size<true>(xx) < U.size<true>(yy)) {
                U.unite_to(xx, yy);
                S[yy].join(S[xx]);
            } else {
                U.unite_to(yy, xx);
                S[xx].join(S[yy]);
            }
        } else {
            uint32_t x;
            cin >> x;
            x--;
            if (popped[x]) {
                cout << "-1\n";
                continue;
            }
            uint32_t xx = U.find(x);
            auto [id, value] = S[xx].top();
            cout << value << endl;
            S[xx].pop();
            popped[id] = true;
        }
    }
}