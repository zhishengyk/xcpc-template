#include "DS/BIT2D.h"
#include "DS/GlobalHashBIT2D.h"
#include "DS/OfflinePointAddRectSumMaintainer2D.h"
#include "DS/PointAddRectSumMaintainer2D.h"
#include "IO/FastIO.h"

/*
[#133. 二维树状数组 1：单点修改，区间查询](https://loj.ac/p/133)
*/
/**
 * 本题为二维树状数组模板题
 */

void solve_bit2d() {
    uint32_t n, m;
    cin >> n >> m;
    OY::BIT2D64 S(n, m);
    char op;
    while (cin >> op) {
        if (op == '1') {
            uint32_t r, c;
            int64_t v;
            cin >> r >> c >> v;
            S.add(r - 1, c - 1, v);
        } else {
            uint32_t r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << S.query(r1 - 1, r2 - 1, c1 - 1, c2 - 1) << endl;
        }
    }
}

OY::GBIT2D::Tree<uint32_t, int64_t, false, false, 8388617> GS;
void solve_hashbit2d() {
    uint32_t n, m;
    cin >> n >> m;
    GS.resize(n, m);
    char op;
    while (cin >> op) {
        if (op == '1') {
            uint32_t r, c;
            int64_t v;
            cin >> r >> c >> v;
            GS.add(r - 1, c - 1, v);
        } else {
            uint32_t r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << GS.query(r1 - 1, r2 - 1, c1 - 1, c2 - 1) << endl;
        }
    }
}

void solve_OFFLINEPARSM2D() {
    uint32_t n, m;
    cin >> n >> m;
    OY::OFFLINEPARSM2D::Solver<uint32_t, int, int64_t> S;
    char op;
    while (cin >> op) {
        if (op == '1') {
            uint32_t r, c;
            int v;
            cin >> r >> c >> v;
            S.add_point(r, c, v);
        } else {
            uint32_t r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            S.add_query(r1, r2, c1, c2);
        }
    }
    for (auto a : S.solve()) cout << a << endl;
}

void solve_PARSM2D() {
    uint32_t n, m;
    cin >> n >> m;
    OY::PARSM2D::Table<uint32_t, int, int64_t, 64> S;
    char op;
    while (cin >> op) {
        if (op == '1') {
            uint32_t r, c;
            int v;
            cin >> r >> c >> v;
            S.add_point(r, c, v);
        } else {
            uint32_t r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << S.query(r1, r2, c1, c2) << endl;
        }
    }
}

int main() {
    solve_bit2d();
    // solve_hashbit2d();
    // solve_OFFLINEPARSM2D();
    // solve_PARSM2D();
}