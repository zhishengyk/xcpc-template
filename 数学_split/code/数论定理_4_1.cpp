/**
 * @struct Prime
 * @brief 质数筛法结构体（欧拉筛/线性筛）
 */
struct Prime {
    int n;                           // 筛法处理的上界
    int primeCnt = 0;                // 质数计数器
    std::vector<int> prime;          // 存储所有筛出的质数（从prime[1]开始存储）
    std::vector<bool> vis;           // 标记数组，vis[i]=true表示i是合数
    std::vector<int> minPrimeFactor; // 记录每个数的最小质因子

    /**
     * @brief 构造函数，执行线性筛法预处理
     * @param n 筛法处理的上界值
     */
    Prime(int n) : n(n), prime(n + 1), vis(n + 1), minPrimeFactor(n + 1) {
        // 定义并立即执行筛法lambda函数
        auto getPrime = [&]() {
            // 0和1不是质数，直接标记
            vis[0] = vis[1] = true;

            // 主筛法循环：从2开始到n
            for (int i = 2; i <= n; ++i) {
                // 如果i未被标记为合数，则它是质数
                if (!vis[i]) {
                    prime[++primeCnt] = i; // 存入质数表
                    minPrimeFactor[i] = i; // 质数的最小质因子是其本身
                }

                // 用当前数i与已筛出的质数相乘来标记合数
                for (int j = 1; j <= primeCnt and i * prime[j] <= n; ++j) {
                    // 标记i*prime[j]为合数
                    minPrimeFactor[i * prime[j]] = prime[j]; // 记录最小质因子
                    vis[i * prime[j]] = true;                // 标记为合数

                    // 关键优化：保证每个合数只被最小质因子筛一次
                    if (i % prime[j] == 0) {
                        break;
                    }
                }
            }
        };

        // 执行筛法
        getPrime();

        // 调整prime数组大小为实际质数数量+1（因为prime从下标1开始使用）
        prime.resize(primeCnt + 1);
    }
};