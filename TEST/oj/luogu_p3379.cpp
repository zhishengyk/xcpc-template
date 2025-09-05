#include "DS/SqrtTree.h"
#include "IO/FastIO.h"
#include "TREE/BfnController.h"
#include "TREE/DoubleLCA.h"
#include "TREE/HeavyLightDecomposition.h"
#include "TREE/LinkTree.h"
#include "TREE/LongShortDecomposition.h"
#include "TREE/MenghaniMatani.h"
#include "TREE/RMQLCA.h"

/*
[P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
*/
/**
 * 本题为 LCA 模板题
 */

static constexpr uint32_t N = 500000;
int main() {
    uint32_t n, m, s;
    cin >> n >> m >> s;
    OY::LinkTree::Tree<bool, N> S(n);
    for (uint32_t i = 1; i < n; i++) {
        uint32_t a, b;
        cin >> a >> b;
        S.add_edge(a - 1, b - 1);
    }
    S.prepare();
    S.set_root(s - 1);

    OY::RMQLCA::Table<decltype(S), OY::SqrtMinTable<uint32_t, OY::SQRT::RandomController<>, 10>> T(&S);
    // OY::HLD::Table<decltype(S)> T(&S);
    // OY::BFN::Table<decltype(S)> T(&S);
    // OY::MenghaniMatani::Table<decltype(S)> T(&S);
    // OY::DoubleLCA::Table<decltype(S)> T(&S);
    // OY::LSD::Table<decltype(S)> T(&S);

    for (uint32_t i = 0; i < m; i++) {
        uint32_t a, b;
        cin >> a >> b;
        cout << T.calc(a - 1, b - 1) + 1 << '\n';
    }
}