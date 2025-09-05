#include "DS/CompressedSparseRow.h"
#include "DS/LinkBucket.h"
#include "DS/PersistentDSU.h"
#include "DS/RollbackDSU.h"
#include "DS/StaticBufferWrapWithoutCollect.h"
#include "IO/FastIO.h"

/*
[P3402 可持久化并查集](https://www.luogu.com.cn/problem/P3402)
*/
/**
 * 本题为可持久化并查集模板题
 * 由于没有在线，所以可以离线用回滚并查集
 */

static constexpr uint32_t N = 100000, M = 200000;
struct Node {
    uint32_t ver, is_query, a, b;
};
uint32_t id[M + 1];
void solve_rollbackdsu_lbc() {
    uint32_t n, m;
    cin >> n >> m;
    OY::LBC::Container<Node> buckets(m + 1, m);
    uint32_t ver = 0, cur = 0;
    // 先读入所有查询，记录好版本之间的依赖关系
    for (uint32_t i = 1; i <= m; i++) {
        char op;
        cin >> op;
        if (op == '2') {
            cin >> ver;
            id[i] = id[ver];
            cur++;
        } else {
            uint32_t a, b;
            cin >> a >> b;
            if (op == '3')
                buckets[id[i] = id[ver]].push_front(Node{i - cur - 1, true, a - 1, b - 1});
            else
                buckets[id[ver]].push_front(Node{id[i] = ++cur, false, a - 1, b - 1});
            ver = i;
        }
    }
    OY::RollbackDSU::Table U(n);
    std::string res(m - cur, ' ');
    auto dfs = [&](auto self, uint32_t cur, uint32_t a, uint32_t b) -> void {
        uint32_t head_a = U.find(a), head_b = U.find(b);
        if (head_a != head_b) {
            if (U.size<true>(head_a) > U.size<true>(head_b)) std::swap(head_a, head_b);
            U.unite_to<false>(head_a, head_b);
        }
        for (auto &&[ver, is_q, a, b] : buckets[cur])
            if (is_q)
                res[ver] = '0' + U.in_same_group(a, b);
            else
                self(self, ver, a, b);
        if (head_a != head_b) U.cancle(head_a, head_b);
    };
    dfs(dfs, 0, 0, 0);
    for (char c : res) cout << c << endl;
}

void solve_rollbackdsu_csr() {
    uint32_t n, m;
    cin >> n >> m;
    OY::CSR::Container<Node> buckets0(m + 1, m);
    uint32_t ver = 0, cur = 0;
    // 先读入所有查询，记录好版本之间的依赖关系
    for (uint32_t i = 1; i <= m; i++) {
        char op;
        cin >> op;
        if (op == '2') {
            cin >> ver;
            id[i] = id[ver];
            cur++;
        } else {
            uint32_t a, b;
            cin >> a >> b;
            if (op == '3')
                buckets0[id[i] = id[ver]].push_back(Node{i - cur - 1, true, a - 1, b - 1});
            else
                buckets0[id[ver]].push_back(Node{id[i] = ++cur, false, a - 1, b - 1});
            ver = i;
        }
    }
    auto buckets = buckets0.get_buckets();

    OY::RollbackDSU::Table U(n);
    std::string res(m - cur, ' ');
    auto dfs = [&](auto self, uint32_t cur, uint32_t a, uint32_t b) -> void {
        uint32_t head_a = U.find(a), head_b = U.find(b);
        if (head_a != head_b) {
            if (U.size<true>(head_a) > U.size<true>(head_b)) std::swap(head_a, head_b);
            U.unite_to<false>(head_a, head_b);
        }
        for (auto &&[ver, is_q, a, b] : buckets[cur])
            if (is_q)
                res[ver] = '0' + U.in_same_group(a, b);
            else
                self(self, ver, a, b);
        if (head_a != head_b) U.cancle(head_a, head_b);
    };
    dfs(dfs, 0, 0, 0);
    for (char c : res) cout << c << endl;
}

using PerDSU = OY::PerDSU::Table<uint32_t, false, OY::StaticBufferWrapWithoutCollect<7000000>::type>;
PerDSU S[M + 1];
void solve_perdsu() {
    uint32_t n, m;
    cin >> n >> m;
    S[0].resize(n);
    for (uint32_t i = 1; i <= m; i++) {
        char op;
        cin >> op;
        if (op == '1') {
            uint32_t a, b;
            cin >> a >> b;
            (S[i] = S[i - 1].copy()).unite_by_size(a - 1, b - 1);
        } else if (op == '2') {
            uint32_t k;
            cin >> k;
            S[i] = S[k];
        } else {
            uint32_t a, b;
            cin >> a >> b;
            cout << (S[i] = S[i - 1].copy()).in_same_group(a - 1, b - 1) << '\n';
        }
    }
}

int main() {
    solve_rollbackdsu_lbc();
    // solve_rollbackdsu_csr();
    // solve_perdsu();
}