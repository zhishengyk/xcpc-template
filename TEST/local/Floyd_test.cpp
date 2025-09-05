#include "GRAPH/Floyd.h"
#include "IO/FastIO.h"
#include "TEST/std_bit.h"

void test_Floyd() {
    // 普通使用者只需要了解熟悉 OY::FLOYD::Graph 的使用
    cout << "test Floyd:\n";

    // 建图
    OY::FLOYD::Graph<int, false> G(7, 9);
    // 注意加的边都是有向边
    G.add_edge(0, 1, 100);
    G.add_edge(0, 2, -200);
    G.add_edge(3, 4, 100);
    G.add_edge(3, 5, 100);
    G.add_edge(0, 3, 95);
    G.add_edge(6, 4, 100);
    G.add_edge(4, 5, -190);
    G.add_edge(5, 1, 100);
    G.add_edge(5, 6, 200);

    // 获取最短路长度查询器
    auto res = G.calc();
    auto &&table = res.first;
    bool flag = res.second;
    cout << "min dis from 0 to 0:" << table.query(0, 0) << endl;
    cout << "min dis from 4 to 1:" << table.query(4, 1) << endl;
    cout << "min dis from 0 to 6:" << table.query(0, 6) << endl;

    // 如果模板参数为 true，那么查询器还可以查询最短路的结点编号
    auto table2 = G.calc<OY::FLOYD::AddGroup<int>, void, true>().first;
    table2.trace(0, 6, [](int from, int to) { cout << "go from " << from << " -> " << to << endl; });

    // G 本身有更方便的接口
    std::vector<uint32_t> path = G.get_path(0, 6);
    for (int i = 0; i < path.size(); i++) cout << path[i] << (i + 1 == path.size() ? "\n\n" : " -> ");
}

void test_solver() {
#if CPP_STANDARD >= 201402L
    // 进阶使用者，可以把 Solver 用到自己的图里
    cout << "test solver:\n";
    // 这里以常见的二维 vector 存图举例
    std::vector<std::vector<std::pair<int, int>>> adj(7);
    adj[0].push_back({1, 100});
    adj[0].push_back({2, -200});
    adj[3].push_back({4, 100});
    adj[3].push_back({5, 100});
    adj[0].push_back({3, 95});
    adj[6].push_back({4, 100});
    adj[4].push_back({5, -190});
    adj[5].push_back({1, 100});
    adj[5].push_back({6, 200});

    // 直接建一个可追溯最短路的解答器
    using monoid = OY::FLOYD::AddGroup<int64_t>;
    OY::FLOYD::Solver<monoid, void, true> sol(7);
    // 传递一个遍历边的泛型回调
    sol.run([&](auto call) {
        for (int from = 0; from < 7; from++)
            for (auto to_and_dis : adj[from]) call(from, to_and_dis.first, to_and_dis.second);
    });

    // 查询最短路长度
    cout << "min dis from 0 to 0:" << sol.query(0, 0) << endl;
    cout << "min dis from 4 to 1:" << sol.query(4, 1) << endl;
    cout << "min dis from 0 to 6:" << sol.query(0, 6) << endl;

    // 生成一个最短路径
    sol.trace(0, 6, [](int from, int to) { cout << "from " << from << " to " << to << endl; });

#endif
}

int main() {
    test_Floyd();
    test_solver();
}
/*
#输出如下
test Floyd:
min dis from 0 to 0:0
min dis from 4 to 1:-90
min dis from 0 to 6:205
go from 0 -> 3
go from 3 -> 4
go from 4 -> 5
go from 5 -> 6
0 -> 3 -> 4 -> 5 -> 6

test solver:
min dis from 0 to 0:0
min dis from 4 to 1:-90
min dis from 0 to 6:205
from 0 to 3
from 3 to 4
from 4 to 5
from 5 to 6

*/