#include "GRAPH/Dinic.h"
#include "GRAPH/EdmondsKarp.h"
#include "IO/FastIO.h"

/*
[#115. 无源汇有上下界可行流](https://loj.ac/p/115)
*/
/**
 * 本题为无源汇有上下界可行流模板题
 */

int main() {
    uint32_t n, m;
    cin >> n >> m;

    OY::DINIC::BoundGraph<int> G(n, m);
    // OY::EK::BoundGraph<int> G(n, m);
    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b, min_cap, max_cap;
        cin >> a >> b >> min_cap >> max_cap;
        G.add_edge(a - 1, b - 1, min_cap, max_cap);
    }
    G.set();

    if (!G.is_possible().second)
        cout << "NO";
    else {
        cout << "YES\n";
        G.do_for_flows([&](uint32_t i, uint32_t flow) {
            cout << flow << '\n';
        });
    }
}