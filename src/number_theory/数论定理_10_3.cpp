
/**
 * @class PrimitiveRootFinder
 * @brief 原根求解器
 *
 * 该类封装了求解模数x的最小原根及其所有原根的方法，
 * 基于欧拉函数和快速幂算法实现。
 */
class PrimitiveRootFinder {
public:
    /**
     * @brief 构造函数，初始化欧拉筛实例
     * @param euler 预初始化的欧拉筛类实例
     */
    PrimitiveRootFinder() {}

    /**
     * @brief 判断给定数x是否存在原根
     * @param x 要判断的数
     * @return 如果x有原根返回true，否则false
     *
     * @note 根据数论理论，只有以下形式的数有原根：
     * 1. 1, 2, 4
     * 2. p^a，其中p是奇素数
     * 3. 2*p^a，其中p是奇素数
     */
    bool hasRoot(int x) const {
        // 特殊情况处理
        if (x == 1 || x == 2 || x == 4) {
            return true;
        }

        // 处理偶数情况
        if (x % 2 == 0) {
            x /= 2;
            // 如果除以2后还是偶数，则不符合2*p^a的形式
            if (x % 2 == 0) {
                return false;
            }
        }

        // 检查是否为p^a的形式
        int primeFactor = euler.minPrimeFactor[x];
        if (primeFactor == 2) {
            return false; // 不满足p是奇素数的条件
        }

        // 检查x是否能被分解为p^a
        while (x % primeFactor == 0) {
            x /= primeFactor;
        }

        // 如果x被完全分解，说明是p^a的形式
        return x == 1;
    }

    /**
     * @brief 获取模x的最小原根
     * @param x 要求原根的模数
     * @return 最小原根，如果不存在原根则返回-1
     */
    int findMinRoot(int x) const {
        if (!hasRoot(x)) {
            return -1;
        }

        const int phi = euler.getPhi(x);
        const auto primeFactors = getPrimeFactor(phi);

        // 枚举可能的g值寻找最小原根
        for (int g = 1;; ++g) {
            // 检查g^phi ≡ 1 P x
            if (fpow(g, phi, x) != 1) {
                continue;
            }

            // 检查g^(phi/p) ≠ 1 P x 对所有phi的素因子p
            bool isPrimitive = true;
            for (int p : primeFactors) {
                if (fpow(g, phi / p, x) == 1) {
                    isPrimitive = false;
                    break;
                }
            }

            if (isPrimitive) {
                return g;
            }
        }
    }

    /**
     * @brief 获取模x的所有原根
     * @param x 要求原根的模数
     * @return 包含所有原根的vector，按升序排列
     */
    std::vector<int> findAllRoot(int x) const {
        std::vector<int> roots;

        const int g = findMinRoot(x);
        if (g == -1) {
            return roots;
        }
        roots.push_back(g);
        const int phi = euler.getPhi(x);
        int current = g;
        // 生成所有原根：g^k，其中gcd(k, phi) = 1
        for (int k = 2; k < phi; ++k) {
            current = current * g % x;
            if (std::gcd(k, phi) == 1) {
                roots.push_back(current);
            }
        }

        std::sort(roots.begin(), roots.end());
        return roots;
    }

private:
    /**
     * @brief 快速幂算法
     * @param a 底数
     * @param b 指数
     * @param P 模数
     * @return (a^b) % P
     */
    static int fpow(int a, int b, int P) {
        int res = 1;
        a %= P;
        while (b > 0) {
            if (b & 1) {
                res = 1ll * res * a % P;
            }
            b >>= 1;
            a = 1ll * a * a % P;
        }
        return res;
    }

    /**
     * @brief 获取数的所有不同质因数
     * @param n 要分解的数
     * @return 包含n的所有不同质因数的vector
     */
    std::vector<int> getPrimeFactor(int n) const {
        std::vector<int> factors;
        if (n == 1) {
            return factors;
        }
        while (n != 1) {
            int p = euler.minPrimeFactor[n];
            factors.push_back(p);
            while (n % p == 0) {
                n /= p;
            }
        }
        return factors;
    }
};