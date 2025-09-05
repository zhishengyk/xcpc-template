#include "GRAPH/Steiner.h"
#include "IO/FastIO.h"

/*
[P6192 【模板】最小斯坦纳树](https://www.luogu.com.cn/problem/P6192)
*/
/**
 * 本题为最小斯坦纳树模板题
 */

int main() {
    uint32_t n, m, k;
    cin >> n >> m >> k;

    OY::STEINER::Graph<int> G(n, m);
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b;
        int cost;
        cin >> a >> b >> cost;
        G.add_edge(a - 1, b - 1, cost);
    }

    for (uint32_t i = 0; i < k; i++) {
        uint32_t key;
        cin >> key;
        G.set_key(key - 1);
    }

    cout << G.calc_spfa<false>().first.total_cost();
    // cout << G.calc_dijk<false>().first.total_cost();
}
