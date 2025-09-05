### 一、模板类别

​	数学： `32` 位取模。

练习题目：

1. [P1198 [JSOI2008] 最大数](https://www.luogu.com.cn/problem/P1198)
2. [P3793 由乃救爷爷](https://www.luogu.com.cn/problem/P3793)
3. [P5903 【模板】树上 K 级祖先](https://www.luogu.com.cn/problem/P5903)

### 二、模板功能

#### 1.构造

1. 数据类型

   构造参数 `uint32_t P` ，表示模数。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   本模板用于加速固定模数的取模过程。在动态模数的情况下，本模板取模速度大幅领先于原生取模计算。
   
   本模板仅限于被除数和除数均为 `32` 位无符号数时的情况。
   
### 三、模板示例

```c++
#include "IO/FastIO.h"
#include "MATH/Lemire32.h"

int main() {
    uint32_t P = 101;
    OY::Lemire32 L(P);

    uint32_t a = 321;
    cout << a << " / " << P << " = " << a / L << endl;
    cout << a << " % " << P << " = " << a % L << endl;
}
```

```
#输出如下
321 / 101 = 3
321 % 101 = 18

```

