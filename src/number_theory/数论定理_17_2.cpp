struct Min25 {
    int n;            // 要计算前缀和的上界
    int block;        // 分块大小，取sqrt(n)
    int primeCnt = 0; // 素数计数器

    // 存储分块信息：
    std::vector<int> lowBlockId;  // 存储小于等于block的值的id
    std::vector<int> highBlockId; // 存储大于block的值的id
    std::vector<int> w;           // 存储所有分块点的值

    std::vector<int> g;     // 存储g函数的前缀和
    std::vector<int> prime; // 存储预处理的小素数
    std::vector<int> vis;   // 筛法标记数组
    std::vector<int> primePrefix;

    // 根据值val获取其在w数组中的索引
    int getId(int val) {
        return (val <= block ? lowBlockId[val] : highBlockId[n / val]);
    }
    int calcPrefix(int x) { // 获得所有位置的前缀和
        return x;
    }
    int calcPrimePrefix(int x) { // x表示是第几个质数
        return primePrefix[x];
    }
    int calcF(int x) { // 对应的函数F(x)
        return 1;
    }

    // 构造函数，初始化Min25筛
    Min25(int n) : n(n),
                   block(sqrt(n)),
                   w(2 * block + 1), // 分配2*sqrt(n)的空间
                   g(2 * block + 1),
                   prime(block + 1),
                   vis(block + 1, 0),
                   lowBlockId(block + 1),
                   highBlockId(block + 1),
                   primePrefix(block + 1, 0) {
        // 欧拉筛预处理小素数
        vis[0] = vis[1] = true; // 0和1不是素数
        for (int i = 2; i <= block; ++i) {
            if (!vis[i]) {
                prime[++primeCnt] = i; // 记录素数
                primePrefix[primeCnt] = primePrefix[primeCnt - 1] + calcF(i);
            }
            // 筛去i的倍数
            for (int j = 1; j <= primeCnt and i * prime[j] <= block; ++j) {
                vis[i * prime[j]] = true; // 标记为合数
                if (i % prime[j] == 0)
                { // 保证每个数只被最小素因子筛去
                    break;
                }
            }
        }

        // 整除分块预处理
        int tot = 0; // 分块计数器
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l); // 计算当前块的右边界
            int val = n / l; // 当前块的代表值

            w[++tot] = val; // 存储分块值

            // 根据值大小选择不同的存储位置
            if (val <= block) {
                lowBlockId[val] = tot;
} else {
                highBlockId[n / val] = tot;
            }

            // 初始化g(0,m)
            g[tot] = calcPrefix(val) - calcPrefix(1);
        }

        // DP计算g函数
        for (int j = 1; j <= primeCnt; ++j)
        { // 遍历所有小素数
            for (int i = 1; i <= tot and prime[j] * prime[j] <= w[i]; ++i) {
                int k = getId(w[i] / prime[j]); // 获取转移位置

                g[i] -= calcF(prime[j]) * (g[k] - calcPrimePrefix(j - 1));
            }
        }
    }

    // 获取质数处函数值的前缀和
    int getPrimePrefix(int n) {
        int k = getId(n); // 获取n对应的索引
        return g[k];      // 返回预处理好的前缀和
    }
};
