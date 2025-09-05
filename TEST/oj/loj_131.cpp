#include "DS/BIT.h"
#include "DS/MonoBIT.h"
#include "DS/MonoZkwTree.h"
#include "DS/WTree.h"
#include "IO/FastIO.h"

/*
[#131. 树状数组 2 ：区间修改，单点查询](https://loj.ac/p/131)
*/
/**
 * 本题要进行区间增加和单点查询
 * 可以转化为差分值的单点增加和区间查询
 * 为树状数组模板题
 * 然而，目前最快的代码应当是用 GNU 扩展所打造的 WTREE 模板
 */

int64_t last;
int main() {
    uint32_t n, m;
    cin >> n >> m;
    auto read = [](auto...) {
        int64_t x = last;
        cin >> last;
        return last - x;
    };
    OY::WSumTree<int64_t> S(n, read);
    // OY::StaticBIT<int64_t, 1 << 20> S(n, read);
    // OY::MonoSumBIT<int64_t> S(n, read);
    // OY::MonoSumTree<int64_t> S(n, read);
    for (uint32_t i = 0; i < m; i++) {
        char op;
        cin >> op;
        if (op == '1') {
            uint32_t x, y;
            int64_t k;
            cin >> x >> y >> k;
            S.add(x - 1, k);
            if (y != n) S.add(y, -k);
        } else {
            uint32_t x;
            cin >> x;
            cout << S.presum(x - 1) << endl;
            // cout << S.query(0, x - 1) << endl;
        }
    }
}
