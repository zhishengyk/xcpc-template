#include "DS/BIT_ex.h"
#include "DS/GlobalHashBIT.h"
#include "DS/TagSegTree.h"
#include "DS/TagZkwTree.h"
#include "DS/ZkwTree.h"
#include "IO/FastIO.h"

/*
[U187320 【模板】树状数组 3](https://www.luogu.com.cn/problem/U187320)
*/
/**
 * 本题需要进行区间增值，区间查询
 * 为树状数组模板题
 */
int main() {
    uint32_t n, m;
    cin >> n >> m;
    auto read = [](auto...) {
        int64_t x;
        cin >> x;
        return x;
    };
    OY::StaticBIT_ex<int64_t, 1 << 21> S(n, read);
    // OY::TagSumZkw<int64_t> S(n, read);
    // OY::VectorTagSumSeg<int64_t, uint32_t> S(n, read);
    // OY::ZkwLazySumTree<int64_t> S(n, read);
    // auto S = [&]() {
    //     OY::GBIT::Tree<uint32_t, int64_t, true, false, 1 << 22> S(n);
    //     for (uint32_t i = 0; i != n; i++) S.add(i, read());
    //     return S;
    // }();
    for (uint32_t i = 0; i < m; i++) {
        char op;
        cin >> op;
        if (op == '1') {
            uint32_t l, r;
            int64_t x;
            cin >> l >> r >> x;
            S.add(l - 1, r - 1, x);
        } else {
            uint32_t l, r;
            cin >> l >> r;
            cout << S.query(l - 1, r - 1) << endl;
        }
    }
}