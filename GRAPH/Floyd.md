### 一、模板类别

​	数据结构：`Floyd` 算法。

​	练习题目：

1. [Arbitrage](https://acm.hdu.edu.cn/showproblem.php?pid=1217)
2. [find the safest road](https://acm.hdu.edu.cn/showproblem.php?pid=1596)
3. [B3647 【模板】Floyd](https://www.luogu.com.cn/problem/B3647)
4. [P2047 [NOI2007] 社交网络](https://www.luogu.com.cn/problem/P2047)
5. [U80592 【模板】floyd](https://www.luogu.com.cn/problem/U80592)


### 二、模板功能

​	图论模板往往包含一个 `Solver` 和一个 `Graph` 。前者仅仅进行逻辑运算，而不包含图本身的数据；后者保存了图的点、边数据，并提供方便的接口。

​	简单起见，使用者可以只使用 `Graph` 及其接口。

#### 1.构造图

1. 数据类型

   类型设定 `size_type = uint32_t` ，表示图中编号的类型。

   模板参数 `typename Tp` ，表示边权类型。

   模板参数 `bool ReverseEdge` ，表示是否建反向边。在无向图中可以勾选此参数。

   构造参数 `size_type vertex_cnt` ，表示点数，默认为 `0` 。

   构造参数 `size_type edge_cnt` ，表示边数。默认为 `0` 。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   `Floyd` 算法处理的问题为有向图的最短路问题。

   如果图为无向图且均为双向边，可以将 `BiEdge` 参数设为 `true` ，边数只需要传递单向的边数，不需要乘二。
   
   对于负权图，只有在确保图中没有负圈的情况下可以计算最短路。

   本数据结构可以接受重边和自环。

#### 2.重置(resize)

1. 数据类型

   输入参数 `size_type vertex_cnt` ，表示点数。

   输入参数 `size_type edge_cnt` ，表示边数。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   本方法会强制清空之前的数据，并建立新图。

#### 3.加边(add_edge)

1. 数据类型

   输入参数 `size_type a`​ ，表示边的起点编号。

   输入参数 `size_type b` ，表示边的终点编号。

   输入参数 `Tp dis` ，表示边权。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   **注意：**在无向图中，若边均为双向边，勾选 `ReverseEdge` 之后只需要调用一次本函数加边。

#### 4.获取最短路查询器(calc)

1. 数据类型
   
   模板参数 `typename Group` ，表示描述路径类型的代数结构。
   
   模板参数 `typename CountType` ，表示路径的计数类型。
   
   模板参数 `bool GetPath` ，表示在求最短路长度时，是否记录最短路路径。

   返回类型 `std::pair<Solver<Group, CountType, GetPath>, bool>` ，前者表示用来计算和保存最短路的对象，后者表示最短路是否计算成功。

2. 时间复杂度

    $O(n^3)$ 。

3. 备注

   如果有负环，则计算失败。

   如果无负环，则计算成功，可以通过返回的对象查询最短路长度，生成最短路路径。
   
   模板参数 `Group` 规定了边权类型、路径长度类型、路径的默认长度、边权组合成路径长度的方式、路径长度的比较函数类型。若为 `AddGroup` 表示常规的边权和路径长度；若为 `MaxGroup` 表示以最大边权为路径长度。
   
   模板参数 `CountType` 规定了最短路的计数类型。由于最短路往往数量众多，往往传递自取模类型。若传递 `void` ，表示不进行计数。
   
   模板参数 `GetPath` 表示是否保存最短路路径。
   
   **注意：**如果要进行路径计数，需保证无零环和负环；显然，添加的自环只要是正权都相当于无效加边。


#### 5.判断是否有负环(has_negative_cycle)

1. 数据类型

   模板参数 `typename Group` ，表示描述路径类型的半群。

2. 时间复杂度

    $O(n^3)$ 。

3. 备注

   本方法判断图中是否存在负环。

#### 6.获取最短路(get_path)

1. 数据类型

   模板参数 `typename Group` ，表示描述路径类型的半群。
   
   输入参数 `size_type source` ，表示起点编号。

   输入参数 `size_type target` ，表示终点编号。

   返回类型 `std::vector<size_type>` ，表示获取到的最短路。

2. 时间复杂度

    $O(n^3)$ 。

3. 备注

   本方法获取从给定起点出发到终点的边权和最小的路径。

   当有负环存在时，返回空。

### 三、模板示例

```c++
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
```

```
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

```

