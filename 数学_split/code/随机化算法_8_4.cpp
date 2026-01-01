/**
 * @class WildcardStringMatcher
 * @brief 使用NTT优化的通配符字符串匹配器
 *
 * 这个类实现了基于NTT的高效字符串匹配算法，能够处理包含通配符('*')的模式串和文本串。
 * 通过多项式乘法将字符串匹配问题转化为数值计算问题，利用NTT加速计算过程。
 */
class WildcardStringMatcher {
private:
    int P; // 模数，用于NTT计算

public:
    /**
     * @brief 构造函数
     * @param P NTT使用的质数模数
     */
    explicit WildcardStringMatcher(int P) : P(P) {}

    /**
     * @brief 执行通配符字符串匹配
     * @param pattern 模式串，可以包含通配符'*'
     * @param text 文本串，可以包含通配符'*'
     * @return 匹配位置的索引列表(1-based)
     *
     * 算法原理：
     * 1. 将字符转换为数值('a'-'z'->1-26, '*'->0)
     * 2. 反转模式串以便多项式乘法
     * 3. 通过三次多项式乘法计算匹配度
     * 4. 匹配度为0的位置即为完全匹配位置
     */
    std::vector<int> match(const std::string &pattern, const std::string &text) {
        int m = pattern.size();
        int n = text.size();

        // 反转模式串以便多项式乘法
        std::string reversePattern = pattern;
        std::reverse(reversePattern.begin(), reversePattern.end());

        // 将字符转换为数值('a'-'z'->1-26, '*'->0)
        Poly S(m), T(n);
        for (int i = 0; i < m; ++i) {
            S[i] = (reversePattern[i] != '*') ? (reversePattern[i] - 'a' + 1) : 0;
        }
        for (int i = 0; i < n; ++i) {
            T[i] = (text[i] != '*') ? (text[i] - 'a' + 1) : 0;
        }

        // 计算三次多项式乘法的组合，用于匹配度计算
        std::vector<int> p = computeMatchingScore(S, T, m, n);

        // 收集所有匹配度为0的位置(完全匹配)
        std::vector<int> result;
        for (int i = m - 1; i < static_cast<int>(p.size()) - m + 1; ++i) {
            if (p[i] == 0) {
                result.push_back(i - m + 2); // 转换为1-based索引
            }
        }

        return result;
    }
    /**
     * @brief 从标准输入读取数据并执行匹配
     * @return 匹配位置的索引列表(1-based)
     *
     * 输入格式:
     * 第一行: m n (模式串长度和文本串长度)
     * 第二行: 模式串
     * 第三行: 文本串
     */

private:
    /**
     * @brief 计算字符串匹配度分数
     * @param S 模式串的多项式表示(已反转)
     * @param T 文本串的多项式表示
     * @param m 模式串长度
     * @param n 文本串长度
     * @return 匹配度分数向量，分数为0表示完全匹配
     */
    std::vector<int> computeMatchingScore(const Poly &S, const Poly &T, int m, int n) {
        Poly cur(m), tmp(n);
        std::vector<int> p;

        // 第一项: S^3 * T
        for (int i = 0; i < m; ++i) {
            cur[i] = 1ll * S[i] * S[i] % P * S[i] % P;
        }
        for (int i = 0; i < n; ++i) {
            tmp[i] = T[i];
        }
        cur = cur * tmp;
        p.assign(cur.size(), 0);
        for (int i = 0; i < static_cast<int>(cur.size()); ++i) {
            p[i] = (p[i] + cur[i]) % P;
        }

        // 第二项: -2 * S^2 * T^2
        cur.resize(m);
        for (int i = 0; i < m; ++i) {
            cur[i] = 1ll * S[i] * S[i] % P;
        }
        for (int i = 0; i < n; ++i) {
            tmp[i] = 1ll * T[i] * T[i] % P;
        }
        cur = cur * tmp;
        for (int i = 0; i < static_cast<int>(cur.size()); ++i) {
            p[i] = (p[i] - 2ll * cur[i] % P + P) % P;
        }

        // 第三项: S * T^3
        cur.resize(m);
        for (int i = 0; i < m; ++i) {
            cur[i] = S[i];
        }
        for (int i = 0; i < n; ++i) {
            tmp[i] = 1ll * T[i] * T[i] % P * T[i] % P;
        }
        cur = cur * tmp;
        for (int i = 0; i < static_cast<int>(cur.size()); ++i) {
            p[i] = (p[i] + cur[i]) % P;
        }

        return p;
    }
};
