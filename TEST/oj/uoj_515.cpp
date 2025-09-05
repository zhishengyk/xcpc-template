#include "DS/OfflineSideView.h"
#include "DS/SideView.h"
#include "IO/FastIO.h"

/*
[#515. 【UR #19】前进四](https://uoj.ac/problem/515)
*/
/**
 * 本题题面已经点明，可以转化为某点之后的不同的后缀最小值个数的查询
 * 那么我们不妨从后往前走，记录后缀最小值，后缀最小值变化多少次就说明有多少个不同的后缀最小值
 * 最小值的变化次数，可以用 SideView 模板解决
 *
 * 在线版本的 SideView 会超时
 */

void solve_offline() {
    uint32_t n, m;
    cin >> n >> m;
    OY::DescendingOfflineSideView<uint32_t, std::greater<uint32_t>> sol(n);
    for (uint32_t i = 0; i != n; i++) {
        uint32_t x;
        cin >> x;
        sol.add_modify(n - 1 - i, x);
    }
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t pos;
        cin >> op >> pos;
        if (op == '1') {
            uint32_t val;
            cin >> val;
            sol.add_modify(n - pos, val);
        } else
            sol.add_query(n - pos);
    }
    for (auto a : sol.solve()) cout << a << endl;
}

void solve_online() {
    uint32_t n, m;
    cin >> n >> m;
    OY::DescendingSideView<uint32_t> S(n);
    for (uint32_t i = 0; i != n; i++) {
        uint32_t x;
        cin >> x;
        S.modify(n - 1 - i, x);
    }
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t pos;
        cin >> op >> pos;
        if (op == '1') {
            uint32_t val;
            cin >> val;
            S.modify(n - pos, val);
        } else
            cout << S.presum(n - pos) << endl;
    }
}

int main() {
    solve_offline();
    // solve_online();
}