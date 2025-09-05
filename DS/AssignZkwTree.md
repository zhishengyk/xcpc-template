### 一、模板类别

​	数据结构：区间推平 `zkw` 线段树。

​	练习题目：

1. [#2037. 「SHOI2015」脑洞治疗仪](https://loj.ac/p/2037)
2. [P2894 [USACO08FEB] Hotel G](https://www.luogu.com.cn/problem/P2894)
3. [P3979 遥远的国度](https://www.luogu.com.cn/problem/P3979)
4. [P4344 [SHOI2015] 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344)
5. [Range Set Range Composite](https://judge.yosupo.jp/problem/range_set_range_composite)(https://github.com/yosupo06/library-checker-problems/issues/829)



### 二、模板功能

​		本数据结构的功能与实现与 `MonoZkwTree` 几乎一致，唯一的特化就是本模板专门针对区间推平做了特化优化，所以与 `MonoZkwTree` 相同部分的内容不再介绍。

​		本数据结构对于半群的要求，与 `MonoZkwTree` 的要求有所不同。

​		对于不进行区间查询的场景，对代数结构的要求：

1. 声明 `value_type` 为值类型。

​		在此情况下，由于没有幺元，所以要求在构造的时候必须赋初值。

​		对于进行区间查询，且元素能够快速翻倍的场景，对幺半群的要求：

1. 声明 `value_type` 为值类型；
2. 定义静态函数 `op` ，接受两个 `value_type` 参数，返回它们的聚合值；
3. 定义静态函数 `identity` ，无输入参数，返回幺元；
4. 定义静态函数 `pow` ，接受一个 `value_type x` 参数和一个 `size_type n` 翻倍倍数，返回 `n` 个 `x` 的聚合值。

​		对于进行区间查询，且元素不能快速翻倍的场景，对幺半群的要求：

1. 声明 `value_type` 为值类型；
2. 定义静态函数 `op` ，接受两个 `value_type` 参数，返回它们的聚合值；
3. 定义静态函数 `identity` ，无输入参数，返回幺元；
4. 定义静态函数 `pow` ，接受一个 `value_type x` 参数，返回 `2` 个 `x` 的聚合值。本函数为可选项，如果不提供本函数，则使用 `op` 计算 `2` 个 `x` 的聚合值。

​		幺半群须有幺元，且运算需要满足**结合律**。

​		有两种情况选择：第一种是信息翻倍较慢的情况，第二种信息翻倍较快的情况。第一种情况的例子是，如果元素类型是自取模整数，信息聚合是乘法运算。那么当对某个区间推平为某个值 `x` 时，需要 $O(\log n)$ 的时间计算出这个区间的信息聚合值。在这种情况下，每个结点会维护一个打表，分别表示一个 `x` 、两个 `x` 、四个 `x` 、八个 `x` ……的信息聚合值，最终的单次修改和查询的时间复杂度只有一层对数。第二种情况的例子是，如果元素类型是自取模整数，信息聚合是加法运算。那么当对某个区间推平为某个值 `x` 时，只需要 $O(1)$ 的时间计算出这个区间的信息聚合值。这种情况下，不需要维护打表，最终的单次修改和查询的时间复杂度也只有一层对数。

### 三、模板示例

```c++
#include "DS/AssignZkwTree.h"
#include "IO/FastIO.h"

void test() {
    std::string s[] = {"apple", "banana", "peal", "orange", "banana"};
    // 一颗不维护信息聚合的树
    OY::AssignZkw<std::string> S(s, s + 5, "");
    cout << S << endl;
    S.modify(1, 3, "app");
    cout << S << endl;
    S.modify(2, 4, "bank");
    cout << S << endl;
    cout << endl;
}

void test_sum() {
    int arr[] = {1, 100, 1000, 10, 10000};
    // 一颗维护信息聚合的树
    // 对于数字类型的信息，而且还是求和信息
    // 因为通过乘法，可以很快算出翻倍的值，所以可以用如下特化
    OY::AssignSumZkw<int> S(5, [&](int i) { return arr[i]; }, 0);
    cout << S << endl;
    S.modify(1, 3, 20);
    S.modify(2, 4, 5);
    cout << S << endl;
    cout << "sum(S[0~2]) = " << S.query(0, 2) << endl;
    cout << "sum(S[1~3]) = " << S.query(1, 3) << endl;
    cout << "sum(S[2~4]) = " << S.query(2, 4) << endl;
    cout << endl;
}

void test_min() {
    int arr[] = {1, 100, 1000, 10, 10000};
    // 一颗维护区间最小值的树
    OY::AssignMinZkw<int> S(5, [&](int i) { return arr[i]; }, 0);
    cout << S << endl;
    S.modify(1, 3, 20);
    S.modify(2, 4, 5);
    cout << S << endl;
    cout << "min(S[0~2]) = " << S.query(0, 2) << endl;
    cout << "min(S[1~3]) = " << S.query(1, 3) << endl;
    cout << "min(S[2~4]) = " << S.query(2, 4) << endl;
    cout << endl;
}

void test_fast_pow() {
    int arr[] = {1, 2, 1, 1, 3, 1, 2};
    // 假设维护一个数字区间，维护区间乘积
#if CPP_STANDARD >= 202002L
    auto op = [](int x, int y) { return x * y; };
    auto pow = [](int x, int n) { return ::pow(x, n); };
#else
    struct {
        int operator()(int x, int y) const { return x * y; }
    } op;
    struct {
        int operator()(int x, int n) const { return ::pow(x, n); }
    } pow;
#endif
    auto S = OY::make_fast_pow_AssignZkwTree<int>(7, op, pow, [&](int i) { return arr[i]; }, 1);
    cout << S << endl;
    S.modify(1, 3, 3);
    cout << S << endl;
    S.modify(2, 5, 4);
    cout << S << endl;
    cout << "prod(S2[0~2]) = " << S.query(0, 2) << endl;
    cout << "prod(S2[1~3]) = " << S.query(1, 3) << endl;
    cout << "prod(S2[2~4]) = " << S.query(2, 4) << endl;
    S.modify(2, 5, 2);
    cout << S << endl;
    cout << "prod_all = " << S.query_all() << endl;
    cout << endl;
}

void test_slow_pow() {
    int64_t arr[] = {12, 2, 1, 3, 2, 0, 10};
    // 假设维护一个长整数区间，维护区间乘积
    // 由于长整数的 pow 可能有精度问题，所以只能采用 Lazy 树
#if CPP_STANDARD >= 202002L
    auto op = [](int64_t x, int64_t y) { return x * y; };
#else
    struct {
        double operator()(int64_t x, int64_t y) const { return x * y; }
    } op;
#endif
    auto S = OY::make_lazy_AssignZkwTree<int64_t>(7, op, [&](int i) { return arr[i]; }, 1);
    cout << S << endl;
    S.modify(1, 3, 3);
    cout << S << endl;
    S.modify(2, 5, 1);
    cout << S << endl;
    cout << "prod(S2[0~2]) = " << S.query(0, 2) << endl;
    cout << "prod(S2[1~3]) = " << S.query(1, 3) << endl;
    cout << "prod(S2[2~4]) = " << S.query(2, 4) << endl;
    S.modify(2, 5, 2);
    cout << S << endl;
    cout << "prod_all = " << S.query_all() << endl;
    cout << endl;
}

int main() {
    test();
    test_sum();
    test_min();
    test_fast_pow();
    test_slow_pow();
}
```

```
#输出如下
[apple, banana, peal, orange, banana]
[apple, app, app, app, banana]
[apple, app, bank, bank, bank]

[1, 100, 1000, 10, 10000]
[1, 20, 5, 5, 5]
sum(S[0~2]) = 26
sum(S[1~3]) = 30
sum(S[2~4]) = 15

[1, 100, 1000, 10, 10000]
[1, 20, 5, 5, 5]
min(S[0~2]) = 1
min(S[1~3]) = 5
min(S[2~4]) = 5

[1, 2, 1, 1, 3, 1, 2]
[1, 3, 3, 3, 3, 1, 2]
[1, 3, 4, 4, 4, 4, 2]
prod(S2[0~2]) = 12
prod(S2[1~3]) = 48
prod(S2[2~4]) = 64
[1, 3, 2, 2, 2, 2, 2]
prod_all = 96

[12, 2, 1, 3, 2, 0, 10]
[12, 3, 3, 3, 2, 0, 10]
[12, 3, 1, 1, 1, 1, 10]
prod(S2[0~2]) = 36
prod(S2[1~3]) = 3
prod(S2[2~4]) = 1
[12, 3, 2, 2, 2, 2, 10]
prod_all = 5760

```

