#include "GRAPH/Floyd.h"
#include "GRAPH/Johnson.h"
#include "IO/FastIO.h"

/*
[B3647 【模板】Floyd](https://www.luogu.com.cn/problem/B3647)
*/
/**
 * 本题为 floyd 算法模板题
 */

int main() {
    uint32_t n, m;
    cin >> n >> m;
    OY::FLOYD::Graph<uint32_t, true> G(n, m);
    // OY::Johnson::Graph<uint32_t> G(n, m * 2);
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b, dis;
        cin >> a >> b >> dis;
        G.add_edge(a - 1, b - 1, dis);
        // 当使用 Johnson 方法时，由于建图建的是有向图，所以需要加反向边
        // G.add_edge(b - 1, a - 1, dis);
    }

    using monoid = OY::FLOYD::AddGroup<uint32_t>;
    auto res = G.calc<monoid>().first;
    for (uint32_t i = 0; i < n; i++)
        for (uint32_t j = 0; j < n; j++) cout << res.query(i, j) << " \n"[j == n - 1];
}
