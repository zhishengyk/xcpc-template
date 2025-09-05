### 一、模板类别

​	数据结构：状压 `RMQ` 。

​	练习题目：

1. [Check Corners](http://acm.hdu.edu.cn/showproblem.php?pid=2888)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
4. [P2032 扫描](https://www.luogu.com.cn/problem/P2032)
5. [P3793 由乃救爷爷](https://www.luogu.com.cn/problem/P3793)
6. [P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)
7. [k - 路径（hard vension）](https://ac.nowcoder.com/acm/problem/279411)
8. [小红的树上路径查询（hard）](https://ac.nowcoder.com/acm/problem/281352)


### 二、模板功能

​		本数据结构分两个版本，一个版本的查询结果为最值所在的下标，一个版本的查询结果为最值的值。可以根据需要使用。以下文档按照返回下标进行编写。

#### 1.建立状压RMQ

1. 数据类型

   类型设定 `size_type = uint32_t` ，表示表中下标、区间下标的变量类型。

   模板参数 `typename Tp` ，表示元素类型。
   
   模板参数 `typename Compare` ，表示比较函数的类型。

   模板参数 `size_t MAX_LEVEL` ，表示内层 `ST` 表的最大层数。默认为 `24` 。

   构造参数 `size_type length` ，表示状压 `RMQ` 的覆盖范围为 `[0, length)`。默认值为 `0` 。

   构造参数 `InitMapping mapping` ，表示在初始化时，从下标到值的映射函数。

2. 时间复杂度

    $O(n)$ ；相当于 `ST` 表执行一个 $\frac n {\log n}$ 规模的初始化，再 执行 $\frac n {\log n}$ 个 $\log n$ 规模的初始化。

3. 备注

   状压 `RMQ` 处理的问题为区间最值的维护，而且必须是严格意义上的最值，而不能是按位或、按位与等等。这一点是与 `ST` 表不同的。
   
   **注意：**
   
   构造参数中的 `mapping` 参数，入参为下标，返回值须为一个 `value_type` 对象。

#### 2.建立状压RMQ

1. 数据类型

   构造参数 `Iterator first` ，表示区间维护的区间头。

   构造参数 `Iterator last` ，表示区间维护的区间尾。（开区间）

   其它同上。

2. 时间复杂度

   同上。

3. 备注

   同上。

   使用迭代器进行初始化，可以将区间初状态直接赋到状压 `RMQ` 里。


#### 3.重置(resize)

1. 数据类型

   输入参数 `size_type length` ，表示状压 `RMQ` 要处理的区间大小。

   输入参数 `InitMapping mapping` ，表示初始化时，从下标到值的映射函数。

2. 时间复杂度

    $O(n)$ ；相当于 `ST` 表执行一个 $\frac n {\log n}$ 规模的初始化，再 执行 $\frac n {\log n}$ 个 $\log n$ 规模的初始化。

3. 备注

   使用映射函数进行初始化，可以将区间初状态直接赋到状压 `RMQ` 里。

    `mapping` 要求传入一个下标，返回一个 `value_type` 类型的值。在调用时，会按照下标从 `0` 到 `length-1` 依次调用。

#### 4.重置(reset)

1. 数据类型

   输入参数 `Iterator first` ，表示区间维护的区间头。

   输入参数 `Iterator last` ，表示区间维护的区间尾。（开区间）

2. 时间复杂度

   同上。

3. 备注

   同上。

   使用迭代器进行重置，可以将区间初状态直接赋到状压 `RMQ` 里。


#### 5.单点赋值(modify)

1. 数据类型

   输入参数 `size_type i​` ，表示单点赋值的下标。

   输入参数 `value_type val​` ，表示赋的值。

2. 时间复杂度

   $O(\frac n \log n+w)$ ，此处 `w` 指 `MaskType` 位宽度；相当于 `ST` 表进行一次单点赋值，然后再进行一次 `w` 长度的操作。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

#### 6.单点查询(query)

1. 数据类型

   输入参数 `size_type i` ，表示查询的下标。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）


#### 7.区间查询(query)

1. 数据类型

   输入参数 `size_type left​` ，表示区间查询的开头下标。

   输入参数 `size_type right​`，表示区间查询的结尾下标。(闭区间)

2. 时间复杂度

    $O(1)$ ；相当于 `ST` 表进行一次区间查询。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

#### 8.查询全部(query_all)

1. 数据类型

2. 时间复杂度

   $O(1)$ ；相当于 `ST` 表进行一次区间查询。

#### 9.根据下标获取值(get)

1. 数据类型

   输入参数 `size_type index` ，表示查询的下标。

   返回类型 `value_type` ，表示区间里下标对应的元素值。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   本方法仅存在于查询最值下标的版本中。

### 三、模板示例

```c++
#include "DS/MaskRMQ.h"
#include "IO/FastIO.h"

int main() {
    // 先给出一个长度为 10 的数组
    int A[10] = {100, 99, 100, 101, 102, 103, 102, 103, 102, 103};
    for (int i = 0; i < 10; i++)
        cout << A[i] << (i == 9 ? '\n' : ' ');

    // 建立一个区间最大值、返回最大值下标的状压 RMQ 表
    OY::MaskRMQMaxIndexTable<int> S(A, A + 10);
    cout << "max(A[3~6]).index = " << S.query(3, 6) << endl;

    // 建立一个区间最小值、返回最小值的值的状压 RMQ 表
    OY::MaskRMQMinValueTable<int> S2(A, A + 10);
    cout << "min(A[3~6])       = " << S2.query(3, 6) << endl;
}
```

```
#输出如下
100 99 100 101 102 103 102 103 102 103
max(A[3~6]).index = 5
min(A[3~6])       = 101

```

