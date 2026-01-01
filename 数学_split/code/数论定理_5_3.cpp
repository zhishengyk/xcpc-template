/**
 * @struct Euler
 * @brief 欧拉筛法实现欧拉函数计算
 *
 * 该类使用欧拉筛法在线性时间内预处理欧拉函数值，
 * 同时记录每个数的最小质因子。
 */
struct Euler {
    /**
     * @brief 计算单个数的欧拉函数值（适用于超出预处理范围的大数）
     * @param x 要计算欧拉函数的数
     * @return x的欧拉函数值
     */
    int getPhi(int x) {
        // 如果在预处理范围内，直接返回预计算值
        if (x <= n) {
            return phi[x];
        }

        // 对于超出预处理范围的数，直接计算欧拉函数
        int res = x;
        // 遍历可能的质因子
        for (int i = 2; i <= x / i; ++i) {
            if (x % i == 0)
            {                            // 找到一个质因子i
                res = res / i * (i - 1); // 欧拉函数计算公式
                // 去除所有i因子
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        // 处理剩余的大于1的质因子
        if (x > 1) {
            res = res / x * (x - 1);
        }
        return res;
    }

    int n;                           // 预处理的上界
    std::vector<int> prime;          // 存储所有预处理的质数
    std::vector<int> phi;            // 存储欧拉函数值
    std::vector<int> minPrimeFactor; // 存储每个数的最小质因子
    std::vector<bool> vis;           // 标记是否为合数
    int primeCnt = 0;                // 质数计数器

    /**
     * @brief 构造函数，执行欧拉筛预处理
     * @param n 预处理的上界
     */
    Euler(int n) : n(n),
                   prime(n + 1),
                   phi(n + 1),
                   vis(n + 1, false),
                   minPrimeFactor(n + 1) {
        // 定义并立即执行欧拉筛函数
        auto getPhi = [&]() {
            // 初始化特殊情况
            phi[0] = 0;             // 通常认为φ(0)未定义，这里设为0
            phi[1] = 1;             // φ(1) = 1
            vis[0] = vis[1] = true; // 0和1不是质数

            // 欧拉筛主循环
            for (int i = 2; i <= n; ++i) {
                if (!vis[i])
                {                          // i是质数
                    minPrimeFactor[i] = i; // 质数的最小质因子是其本身
                    prime[++primeCnt] = i; // 存入质数表
                    phi[i] = i - 1;        // 质数的欧拉函数值为i-1
                }

                // 用当前数i与已知质数筛合数
                for (int j = 1; j <= primeCnt && i * prime[j] <= n; ++j) {
                    vis[i * prime[j]] = true;                // 标记为合数
                    minPrimeFactor[i * prime[j]] = prime[j]; // 记录最小质因子

                    if (i % prime[j] == 0) {
                        // i包含prime[j]因子时的欧拉函数计算
                        phi[i * prime[j]] = phi[i] * prime[j];
                        break; // 保证每个合数只被最小质因子筛一次
} else {
                        // i与prime[j]互质时的欧拉函数计算
                        phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                    }
                }
            }
        };

        // 执行欧拉筛预处理
        getPhi();
    }
};