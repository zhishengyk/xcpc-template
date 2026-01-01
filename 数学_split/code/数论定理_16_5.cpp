// 杜教筛模板类，用于高效计算欧拉函数φ(n)和莫比乌斯函数μ(n)的前缀和
struct DujiaoSieve {
    const int N = 2e6;
    std::vector<int> prime, phi, mo;
    std::vector<bool> vis;
    int primeCnt = 0;
    // 哈希表，用于存储已经计算过的前缀和结果（记忆化）
    std::unordered_map<ll, int> hashPhi; // 存储欧拉函数前缀和
    std::unordered_map<ll, int> hashMo;  // 存储莫比乌斯函数前缀和

    // 构造函数，初始化时调用init()进行预处理
    DujiaoSieve() : prime(N + 1), phi(N + 1), mo(N + 1), vis(N + 1, 0) {
        init();
    }

    // 初始化函数，使用线性筛预处理前N个数的φ和μ值及其前缀和
    void init() {
        // 初始化1的特殊情况
        mo[1] = phi[1] = 1;

        // 线性筛法（欧拉筛）
        for (int i = 2; i <= N; ++i) {
            if (!vis[i])
            {                          // 如果i是素数
                prime[++primeCnt] = i; // 记录素数
                phi[i] = i - 1;        // 素数的欧拉函数值为i-1
                mo[i] = -1;            // 素数的莫比乌斯函数值为-1
            }

            // 用当前已知素数筛i的倍数
            for (int j = 1; i * prime[j] <= N && j <= primeCnt; ++j) {
                vis[i * prime[j]] = true; // 标记为合数

                if (i % prime[j] == 0)
                {                                          // i包含prime[j]的平方因子
                    mo[i * prime[j]] = 0;                  // 莫比乌斯函数值为0（可以不写，因为默认初始化为0）
                    phi[i * prime[j]] = phi[i] * prime[j]; // 欧拉函数性质
                    break;                                 // 保证每个数只被最小质因子筛一次
} else {
                    mo[i * prime[j]] = -mo[i];                   // 新的素数因子，莫比乌斯函数符号翻转
                    phi[i * prime[j]] = phi[i] * (prime[j] - 1); // 欧拉函数性质
                }
            }
        }

        // 计算前缀和数组
        for (int i = 1; i <= N; ++i) {
            phi[i] += phi[i - 1]; // 欧拉函数前缀和
            mo[i] += mo[i - 1];   // 莫比乌斯函数前缀和
        }
    }

    // 计算欧拉函数前缀和（杜教筛核心）
    ll prePhi(int n) {
        if (n < N)
        { // 如果在预处理范围内，直接返回
            return phi[n];
        }
        if (hashPhi.count(n))
        { // 如果已经计算过，直接从哈希表中取
            return hashPhi[n];
        }

        // 初始估计值（利用欧拉函数求和公式）
        ll ans = 1ll * n * (n + 1) / 2;

        // 分块处理，利用数论分块优化
        for (int l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);                          // 计算当前块的右边界
            ans -= 1ll * prePhi(n / l) * (r - l + 1); // 递归计算并减去贡献
        }

        return hashPhi[n] = ans; // 存储结果到哈希表并返回
    }

    // 计算莫比乌斯函数前缀和（杜教筛核心）
    ll preMo(int n) {
        if (n < N)
        { // 如果在预处理范围内，直接返回
            return mo[n];
        }
        if (hashMo.count(n))
        { // 如果已经计算过，直接从哈希表中取
            return hashMo[n];
        }

        // 初始值为1（因为μ(1)=1）
        ll ans = 1;

        // 分块处理，利用数论分块优化
        for (int l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);                         // 计算当前块的右边界
            ans -= 1ll * preMo(n / l) * (r - l + 1); // 递归计算并减去贡献
        }

        return hashMo[n] = ans; // 存储结果到哈希表并返回
    }
};
DujiaoSieve Sieve;