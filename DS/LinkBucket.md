### 一、模板类别

​	数据结构：链桶。

​	（这是自取的名字，该数据结构用来维护总长一定的若干个 `std::vector` ，为图论中链式前向星的自然推广。）

​	练习题目：

1. [find the safest road](https://acm.hdu.edu.cn/showproblem.php?pid=1596)
2. [Question for the Leader](https://acm.hdu.edu.cn/showproblem.php?pid=5329)
3. [Hotaru's problem](https://acm.hdu.edu.cn/showproblem.php?pid=5371)
4. [P3201 [HNOI2009] 梦幻布丁](https://www.luogu.com.cn/problem/P3201)
5. [P3246 [HNOI2016] 序列](https://www.luogu.com.cn/problem/P3246)
6. [P3261 [JLOI2015] 城池攻占](https://www.luogu.com.cn/problem/P3261)
7. [P3402 可持久化并查集](https://www.luogu.com.cn/problem/P3402)
8. [P3835 【模板】可持久化平衡树](https://www.luogu.com.cn/problem/P3835)
9. [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
10. [P4062 [Code+#1] Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062)
11. [P4151 [WC2011] 最大XOR和路径](https://www.luogu.com.cn/problem/P4151)
12. [P4211 [LNOI2014] LCA](https://www.luogu.com.cn/problem/P4211)
13. [P4556 [Vani有约会] 雨天的尾巴 /【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)
14. [P5022 [NOIP2018 提高组] 旅行](https://www.luogu.com.cn/problem/P5022)
15. [P5049 [NOIP2018 提高组] 旅行 加强版](https://www.luogu.com.cn/problem/P5049)
16. [P5287 [HNOI2019] JOJO](https://www.luogu.com.cn/problem/P5287)
17. [P6822 [PA2012] Tax](https://www.luogu.com.cn/problem/P6822)
18. [P8512 [Ynoi Easy Round 2021] TEST_152](https://www.luogu.com.cn/problem/P8512)
19. [U208135 可持久化并查集 加强版](https://www.luogu.com.cn/problem/U208135)
20. [记忆](https://ac.nowcoder.com/acm/problem/274793)
21. [parent 树上启发式合并](https://ac.nowcoder.com/acm/problem/274852)
22. [小Z的树迁移](https://ac.nowcoder.com/acm/problem/281601)
23. [Persistent Queue](https://judge.yosupo.jp/problem/persistent_queue)(https://github.com/yosupo06/library-checker-problems/issues/379)
24. [Persistent Unionfind](https://judge.yosupo.jp/problem/persistent_unionfind)(https://github.com/yosupo06/library-checker-problems/issues/405)
25. [Cycle Detection (Directed)](https://judge.yosupo.jp/problem/cycle_detection)(https://github.com/yosupo06/library-checker-problems/issues/534)
26. [Cycle Detection (Undirected)](https://judge.yosupo.jp/problem/cycle_detection_undirected)(https://github.com/yosupo06/library-checker-problems/issues/869)
27. [C. 最短路径](https://qoj.ac/contest/1875/problem/9903)
28. [D. 最小生成树](https://qoj.ac/problem/9904)






### 二、模板功能

#### 1.建立链桶

1. 数据类型

   类型设定 `size_type = uint32_t` ，表示各种下标的变量类型。

   模板参数 `typename Tp` ，表示链桶中要存放的元素类型。
   
   模板参数 `bool MaintainSize` ，表示是否维护每个桶的元素数量。

   构造参数 `size_type bucket_cnt` ，表示本链桶实际桶数。默认值为 `0` 。

   构造参数 `size_type item_cnt` ，表示本链桶实际元素数。默认值为 `0` 。

2. 时间复杂度

   $O(n)$ 。

3. 备注

   链桶处理的问题，可以参考链式前向星存储图时的场景：

   1. 不关心桶中元素的顺序。由于链桶存放元素与读取元素的顺序恰好相反，所以维持元素顺序不便；由于本质为链表，所以也不支持用下标访问桶中元素。
   2. 桶的总数和元素总数在构造时必须已知。或者至少得知道一个上限。
   3. 元素和桶的数量比适当。如果过低，即元素数量远少于桶数，大部分桶都是空桶，那么用 `std::map` 可能比逐个桶做初始化更佳；如果过高，链式前向星相比起 `std::vector<std::vector<Tp>>` 就既不方便，也无性能优势。

#### 2.重置(resize)

1. 数据类型

   输入参数 `size_type bucket_cnt` ，表示本链桶实际桶数。

   输入参数 `size_type item_cnt` ，表示本链桶实际元素数。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   注意，本函数与 `std::vector` 的 `resize` 截然不同，丝毫不保留之前的元素，而是全部丢弃，并使用新的空间。

#### 3.获取某桶(operator[])

1. 数据类型

   输入参数 `size_type buc_id` ，表示要获取的桶的编号。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   返回的桶可以通过 `for` 循环进行范围遍历；可以取出 `begin`， `end` 迭代器；可以通过 `push_front` 加入新元素。
   
   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

#### 4.获取某桶的首迭代器(bucket_begin)

1. 数据类型

   输入参数 `size_type buc_id` ，表示桶的编号。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

#### 5.获取某桶的尾迭代器(bucket_end)

1. 数据类型

2. 时间复杂度

   $O(1)$ 。

3. 备注

   由于所有桶的尾迭代器均相同，所以无需要入参。
   
#### 6.交换两个桶(swap)

1. 数据类型

   输入参数 `size_type buc_id1` ，表示第一个桶。
   
   输入参数 `size_type buc_id2` ，表示第二个桶。

2. 时间复杂度

   $O(1)$ 。
   
#### 7.合并两个桶(merge)

1. 数据类型

   输入参数 `size_type buc_id` ，表示第一个桶。
   
   输入参数 `size_type rhs` ，表示第二个桶。

2. 时间复杂度

   $O(n)$ ，此处 `n` 指第二个桶的大小。
   
3. 备注

   执行本操作之后， `rhs` 桶被清空。


### 三、模板示例

```c++
#include "DS/LinkBucket.h"
#include "IO/FastIO.h"

int main() {
    OY::LBC::Container<std::string> S(3, 6);
    S[0].push_front("apple");
    S[2].push_front("banana");
    S[2].push_front("pear");
    S[1].push_front("orange");
    S[1].push_front("cat");
    S[0].push_front("dog");
    S[2].pop_front();
    
    for (int i = 0; i < 3; i++) {
        for (auto &item : S[i])
            cout << item << ' ';
        cout << '\n';
    }
}
```

```
#输出如下
dog apple 
cat orange 
banana 

```

