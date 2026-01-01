struct Mobius {
    int n; // 预计算的最大数值范围

    // 获取x的莫比乌斯函数值
    int getMo(int x) {
        // 如果x在预计算范围内，直接返回结果
        if (x <= n) {
            return mo[x];
        }
        // 否则现场计算莫比乌斯函数值
        int res = 1; // 初始化为1
        // 分解质因数
        for (int i = 2; i <= x / i; ++i) {
            if (x % i == 0) // 找到质因数 {
                res *= -1;   // 每找到一个质因数，符号翻转
                int tot = 0; // 计算该质因数的指数
                while (x % i == 0) {
                    x /= i;
                    ++tot;
                }
                // 如果质因数的指数大于1，莫比乌斯函数值为0
                if (tot != 1) {
                    return 0;
                }
            }
        }
        // 处理剩余的质因数
        if (x != 1) {
            res *= -1;
        }
        return res;
    }

    // 下面是预计算莫比乌斯函数用到的成员变量
    std::vector<int> vis;            // 标记是否为合数
    std::vector<int> prime;          // 存储素数
    std::vector<int> mo;             // 存储莫比乌斯函数值
    std::vector<int> minPrimeFactor; // 存储最小质因子
    int primeCnt = 0;                // 素数计数器

    // 构造函数，预计算1到n的莫比乌斯函数
    Mobius(int n) : n(n), vis(n + 1), prime(n + 1), mo(n + 1), minPrimeFactor(n + 1) {
        vis[0] = vis[1] = 1; // 0和1不是素数
        mo[0] = mo[1] = 1;   // 0和1的莫比乌斯函数值设为1（注：实际上μ(1)=1，μ(0)通常未定义）

        // 线性筛法计算莫比乌斯函数
        for (int i = 2; i <= n; ++i) {
            if (!vis[i]) // i是素数 {
                prime[++primeCnt] = i; // 记录素数
                mo[i] = -1;            // 素数的莫比乌斯函数值为-1
            }
            // 用当前已知素数筛i的倍数
            for (int j = 1; j <= primeCnt and i * prime[j] <= n; ++j) {
                vis[i * prime[j]] = 1; // 标记为合数
                if (i % prime[j] == 0) // i包含prime[j]的平方因子 {
                    mo[i * prime[j]] = 0; // 莫比乌斯函数值为0
                    break;
} else {
                    mo[i * prime[j]] = -mo[i]; // 新的素数因子，符号翻转
                }
            }
        }
    }
};