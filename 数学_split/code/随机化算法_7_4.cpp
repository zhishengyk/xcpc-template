/**
 * @class MultiplicativeConvolution
 * @brief 利用原根和对数表实现的乘法卷积类
 *
 * 这个类通过将数字转换到原根的对数域，将乘法操作转换为加法操作，
 * 然后使用多项式乘法(卷积)来实现高效的乘法卷积计算。
 * 特别适用于需要在特定模数下进行大量乘法卷积的场景。
 */
class MultiplicativeConvolution {
private:
    int m; // 模数
    int G; // 模数m的原根
    /**
     * @brief 初始化对数表
     */
    void initLogTable() {
        log.resize(m);                         // 使用m而不是m-1，以便直接使用val作为索引
        std::fill(log.begin(), log.end(), -1); // 初始化为-1表示无效值

        // 构建对数表：log[G^i mod m] = i
        for (int i = 0, cur = 1; i < m - 1; ++i) {
            log[cur] = i;
            cur = cur * G % m;
        }
    }

public:
    /**
     * @brief 构造函数
     * @param modulus 模数m，必须是质数且存在原根
     */
    std::vector<int> log; // 对数表，log[val] = i 表示 val = G^i mod m
    explicit MultiplicativeConvolution(int modulus) : m(modulus) {
        G = findMinRoot(m); // 假设GetRoot函数已实现
        initLogTable();
    }

    /**
     * @brief 执行乘法卷积运算
     * @param input 输入序列，包含需要卷积的数值
     * @return 卷积结果的多项式表示
     *
     * 注意：输入中的0会被自动忽略，因为0在乘法群中没有对数表示
     */
    Poly computeConvolution(const std::vector<int> &input) {
        Poly a(m - 1); // 多项式大小为m-1，因为模m乘法群有m-1个元素
        // 将输入值转换到对数域
        for (int val : input) {
            if (val == 0) {
                continue; // 忽略0，因为0不在乘法群中
            }
            val %= m; // 确保值在模m范围内
            if (val < 0) {
                val += m; // 处理负数
            }
            a[log[val]]++; // 在对数域对应位置计数
        }
        return a;
    }

    // 执行循环卷积（需要确保Poly乘法是循环卷积）
    // 这里假设Poly类已经正确处理了循环卷积  请注意模数为m的循环卷积应该为m-1
};