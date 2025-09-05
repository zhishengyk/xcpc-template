### 一、模板类别

​	数学：高斯-约旦消元法。

​	练习题目：

1. [P2455 [SDOI2006] 线性方程组](https://www.luogu.com.cn/problem/P2455)
2. [P3389 【模板】高斯消元法](https://www.luogu.com.cn/problem/P3389)
3. [System of Linear Equations](https://judge.yosupo.jp/problem/system_of_linear_equations)(https://github.com/yosupo06/library-checker-problems/issues/18)



### 二、模板功能

#### 1.分式求某项系数

1. 数据类型

    类型设定 `size_type = uint32_t` ，表示模板中涉及的数字类型。
    
   模板参数 `typename Tp` ，表示元素类型。

   模板参数 `size_type MAX_UNKNOWN` ，表示未知数的最大数量。

   模板参数 `size_type MAX_EQUATION` ，表示方程的最大数量。

   构造参数 `size_type unknown` ，表示未知数的具体数量。

   构造参数 `size_type equation` ，表示方程的具体数量。

2. 时间复杂度

   $O(n^2)$ 。

3. 备注

   高斯消元解决的是，给定一组方程，求解一组未知数的问题。

   方程的形式为，等号左侧为所有的未知数与其系数的乘积之和；等号右侧为结果值。

#### 2.获取某方程的某项系数(coef)

1. 数据类型

   输入参数 `size_type equation_ID` ，表示要设置的方程的编号。

   输入参数 `size_type unknown_ID` ，表示要设置的未知数的编号。

2. 时间复杂度

   $O(1)$ 。
   
3. 备注

   本方法有只读和可写两个重载。


#### 3.获取某方程的右侧值(result)

1. 数据类型

   输入参数 `size_type equation_ID` ，表示要设置的方程的编号。

2. 时间复杂度

   $O(1)$ 。
   
3. 备注

   本方法有只读和可写两个重载。

#### 4.设置某方程(set_equation)

1. 数据类型

   输入参数 `size_type equation_ID` ，表示要设置的方程的编号。

   输入参数 `std::initializer_list<Tp> equation` ，表示要设置的方程。

2. 时间复杂度

   $O(n)$ ，此处 `n` 指未知数数量。

3. 备注

   本方法仅用于普通高斯消元模板里，使用 `std::initializer_list<Tp>` 一次性设置整个方程。

   **注意：** 请保证传入的方程长度为未知数数量加一。

#### 5.计算(calc)

1. 数据类型

   输入参数 `GetBigger get_bigger` ，表示判断是否绝对值更大的函数。
   
   输入参数 `IsZero is_zero` ，表示判断元素为零的函数。

   返回类型 `bool` ，表示方程组是否有解。

2. 时间复杂度

    $O(n^3)$ 。

3. 备注

   在调用本方法前，请先将所有方程的未知数系数和右侧值填写好。

   参数 `GetBigger get_bigger` 用来传递一个比较函数，这个函数接受两个 `Tp` 类型的参数，返回一个 `bool` ，表示参数一是否比参数二的绝对值大。一般本参数不需要做改写。
   
   如果 `Tp` 为浮点数，由于浮点数存在精度误差，所以可能需要提供特殊的判零函数接口。一般而言， `is_zero` 函数采用默认参数即可。

   当方程组无解时，返回 `false` 。

   当方程组有唯一解或者多解时，返回 `true` 。

#### 6.查询是否有多解(has_multi_solution)

1. 数据类型

   返回类型 `bool` ，表示查询结果。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   在调用本方法前，须先调用计算。

#### 7.获取某未知数的解

1. 数据类型

   输入参数 `size_type unknown_ID` ，表示要查询的未知数的编号。

   返回类型 `Tp` ，表示该未知数的值。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   在调用本方法前，须先调用计算。

#### 8.获取解系的秩(rank)

1. 数据类型

   返回类型 `size_type` 。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   在调用本方法前，须先调用计算。
   
   通过 `get_solution` 只能获得一个解，可以在其基础上添加任意个特定的基向量，仍然是原方程的解。
   
   本方法返回的就是，最大线性无关基向量数目。通过 `enumerate_base` 可以访问这些基向量。

#### 9.枚举基向量(enumerate_base)

1. 数据类型

   输入参数 `Callback &&call` ，表示回调函数。

2. 时间复杂度

   $O(m*n)$ ，其中 `m` 表示未知数数量， `n` 表示方程数量。

3. 备注

   在调用本方法前，须先调用计算。
   
### 三、模板示例

```c++
#include "IO/FastIO.h"
#include "MATH/GaussJordanElimination.h"
#include "MATH/StaticModInt32.h"

int main() {
    // double 版本高斯消元，三个未知数，三个方程
    OY::GJE::GaussJordanElimination<double, 10, 10> GE(3, 3);
    // 1 x + 3 y + 4 z = 5
    GE.set_equation(0, {1, 3, 4, 5});
    // 1 x + 4 y + 7 z = 3
    GE.set_equation(1, {1, 4, 7, 3});
    // 9 x + 3 y + 2 z = 2
    GE.set_equation(2, {9, 3, 2, 2});
    // 计算
    if (!GE.calc({}, [](double x) { return std::abs(x) < 1e-9; })) {
        cout << "No Solution\n";
    } else if (GE.has_multi_solution()) {
        cout << "Multi Solution. Possible solution:\n";
        for (int i = 0; i < 3; i++)
            cout << "x" << i << " = " << GE.get_solution(i) << endl;
    } else {
        cout << "Unique Solution:\n";
        for (int i = 0; i < 3; i++)
            cout << "x" << i << " = " << GE.get_solution(i) << endl;
    }

    // 也可以适用于自取模数类
    // mint 版本高斯消元，两个未知数，四个方程
    using mint = OY::mint998244353;
    OY::GJE::GaussJordanElimination<mint, 10, 10> GE2(2, 3);
    // 1 x + 3 y = 5
    GE2.set_equation(0, {1, 3, 5});
    // 2 x + 6 y = 10
    GE2.set_equation(1, {2, 6, 10});
    // 0 x + 0 y = 0
    GE2.set_equation(2, {0, 0, 0});
    // 计算
    if (!GE2.calc()) {
        cout << "No Solution\n";
    } else if (GE2.has_multi_solution()) {
        cout << "Multi Solution. Possible solution:\n";
        for (int i = 0; i < 2; i++)
            cout << "x" << i << " = " << GE2.get_solution(i) << endl;
    } else {
        cout << "Unique Solution:\n";
        for (int i = 0; i < 2; i++)
            cout << "x" << i << " = " << GE2.get_solution(i) << endl;
    }
}
```

```
#输出如下
Unique Solution:
x0 = -0.973684
x1 = 5.184211
x2 = -2.394737
Multi Solution. Possible solution:
x0 = 5
x1 = 0

```

