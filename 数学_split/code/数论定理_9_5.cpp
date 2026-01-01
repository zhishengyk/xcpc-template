// 扩展BSGS算法：求解高次同余方程 a^x ≡ b (mod P) 的最小正整数解，其中p不需要是质数
// 参数说明：
//   a: 底数
//   b: 余数
//   P: 模数
// 返回值：
//   成功返回最小正整数解x，无解返回-1

template <class T, ll P>
class ExBsgs {
public:
    ExBsgs() {};
    T getAns(T a, T b) {
        // 首先对参数取模处理
        a %= P, b %= P;

        // 特殊情况处理
        if (b == 1 || P == 1)
        { // 任何数的0次方都是1，且模1的同余式总是成立
            return T(0);
        }

        T d, k = 0, A = 1; // d:最大公约数，k:迭代次数，A:累积系数

        // 第一阶段：消除a和p的公因数
        while (true) {
            d = std::gcd(a, P); // 计算a和p的最大公约数
            if (d == 1)
            { // 当a和p互质时退出循环
                break;
            }
            if (b % d)
            { // 如果b不能被d整除，则方程无解
                return T(-1);
            }
            k++;                 // 迭代次数增加
            b /= d;              // 约简b
            P /= d;              // 约简p
            A = A * (a / d) % P; // 更新累积系数

            // 检查是否已经找到解
            if (A == b)
            { // 如果A ≡ b (mod P)，则当前k就是解
                return k;
            }
        }

        // 第二阶段：BSGS算法部分
        T m = ceil(sqrt(P)); // 计算分块大小

        // 预处理：构建哈希表（baby-step）
        T t = b;                         // t用于存储中间结果
        std::unordered_map<T, int> hash; // 哈希表存储值到索引的映射
        hash[b] = 0;                     // 初始状态：b*a^0 ≡ b (mod P)
        for (int j = 1; j < m; ++j) {
            t = t * a % P; // 计算b*a^j mod P
            hash[t] = j;   // 存入哈希表
        }

        // 计算a^m mod p（giant-step的基数）
        T mi = 1;
        for (int i = 1; i <= m; ++i) {
            mi = mi * a % P;
        }

        // 搜索匹配项（giant-step）
        t = A; // 从累积系数A开始
        for (int i = 1; i <= m; ++i) {
            t = t * mi % P; // 计算A*(a^m)^i mod P
            if (hash.count(t))
            { // 如果在哈希表中找到匹配
                // 解为：i*m - hash[t] + k
                return T(i * m - hash[t] + k);
            }
        }
        // 没有找到解
        return T(-1);
    }
};