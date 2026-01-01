class FastGCD {
    int N;                             // 支持的最大整数
    int M;                             // 小整数表上限
    std::vector<std::vector<int>> f;   // 小整数 GCD 表
    std::vector<std::array<int, 3>> d; // 每个整数拆成最多 3 块质因数
    std::vector<int> p;                // 素数数组
    std::vector<bool> v;               // 筛标记

public:
    FastGCD(int n, int m)
        : N(n), M(m), f(M + 1, std::vector<int>(M + 1)),
          d(N + 1, std::array<int, 3>{0, 0, 0}),
          v(N + 1, false) {
        precompute();
    }

    // =================== 普通欧几里得，用于小表生成 ===================
    int gcdNormal(int a, int b) const {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

private:
    void precompute() {
        p.clear();

        // 1. 构建小整数 GCD 表 f[i][j]，保证安全
        for (int i = 0; i <= M; i++) {
            for (int j = 0; j <= M; j++) {
                if (i == 0 || j == 0)
                    f[i][j] = i + j;
                else if (i == j)
                    f[i][j] = i;
                else if (i > j)
                    f[i][j] = f[i - j][j]; // 安全：i-j >= 1
                else
                    f[i][j] = f[j][i]; // i < j，交换
            }
        }

        // 2. 初始化 d[1]
        d[1] = std::array<int, 3>{1, 1, 1};

        // 3. 线性筛 + 分块质因数
        for (int i = 2; i <= N; i++) {
            if (!v[i]) {
                p.push_back(static_cast<int>(i));
                d[i] = std::array<int, 3>{static_cast<int>(i), 1, 1};
            }
            for (size_t j = 0; j < p.size(); j++) {
                int k = i * p[j];
                if (k > N)
                    break;
                v[k] = true;
                d[k] = d[i]; // 继承父数质因数块
                if (d[k][0] * p[j] <= M)
                    d[k][0] *= p[j];
                else if (d[k][1] * p[j] <= M)
                    d[k][1] *= p[j];
                else
                    d[k][2] *= p[j];
                if (i % p[j] == 0)
                    break; // 线性筛剪枝
            }
        }
    }

public:
    int query(int x, int y) const {
        if (!x || !y)
            return x + y;
        int t = 1;
        const auto &px = d[x];
        for (int i = 0; i < 3 && y > 1; i++) {
            if (px[i] <= 1)
                continue;
            int k = 0;
            if (px[i] <= M)
                k = f[px[i]][y % px[i]];
            else if (y % px[i] == 0)
                k = px[i];
            if (k == 0)
                continue; // 避免除零
            t *= k;
            y /= k;
        }
        return t;
    }
};
