#include "GRAPH/Floyd.h"
#include "IO/FastIO.h"

/*
[U80592 【模板】floyd](https://www.luogu.com.cn/problem/U80592)
*/
/**
 * 本题为 floyd 算法模板题
 */

int main() {
    uint32_t n, m;
    cin >> n >> m;
    OY::FLOYD::Graph<uint32_t, true> G(n, m);
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b, dis;
        cin >> a >> b >> dis;
        G.add_edge(a - 1, b - 1, dis);
    }

    using monoid = OY::FLOYD::AddGroup<uint32_t>;
    auto res = G.calc<monoid>().first;
    for (uint32_t i = 0; i < n; i++) {
        uint64_t sum = 0;
        for (uint32_t j = 0; j < n; j++) sum += res.query(i, j);
        cout << sum % 998244354 << endl;
    }
}
