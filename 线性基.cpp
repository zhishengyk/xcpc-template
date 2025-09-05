struct Hamel {
    // 基向量数组，每个元素对应二进制位的最高位
    std::vector<long long> p;
    // 是否存在零向量（0: 不存在，1: 存在）
    int zero;
    // 非零基向量的数量
    int cnt_h;
    int max_bit = 31;
    Hamel() : zero(0), cnt_h(0) {
        p.resize(max_bit + 1, 0);
    }
    void clear() {
        fill(p.begin(),p.end(),0);
        zero = 0;
        cnt_h = 0;
    }
    // 通过long long数组构造线性基
    Hamel(const std::vector<long long>& a) : Hamel() {
        for (auto x : a) insert(x);
    }

    // 通过初始化列表构造（例如 Hamel h = {1,2,3};）
    Hamel(std::initializer_list<long long> init) : Hamel() {
        for (auto x : init) insert(x);
    }

    /* 核心操作 */
    // 向线性基中插入元素x
    void insert(long long x) {
        for (int i = max_bit; i >= 0; --i) {
            if ((x >> i) & 1) {          // 检测x的第i位是否为1
                if (p[i]) {
                    x ^= p[i];           // 用已有基向量消去当前位
                } else {
                    p[i] = x;            // 新增基向量
                    ++cnt_h;
                    return;              // 插入成功直接返回
                }
            }
        }
        zero = 1;                        // 能执行到这里说明插入了零向量
    }

    // 高斯消元标准化基向量（预处理第k小查询）
    void sort_H() {
        for (int i = max_bit; i >= 0; --i) {
            if (!p[i]) continue;
            // 消去高位向量的低位影响
            for (int j = i-1; j >= 0; --j) {
                if ((p[i] >> j) & 1) p[i] ^= p[j];
            }
        }
    }

    /* 查询操作 */
    // 给定初始值x，求最大异或结果
    long long ask_max(long long x = 0) {
        long long ans = x;
        for (int i = max_bit; i >= 0; --i) {
            if ((ans ^ p[i]) > ans) ans ^= p[i];  // 贪心策略
        }
        return ans;
    }

    // 给定初始值x，求最小异或结果
    long long ask_min(long long x = 0) {
        long long ans = x;
        for (int i = max_bit; i >= 0; --i) {
            if (ans & (1LL << i)) ans ^= p[i];    // 消除高位
        }
        return ans;
    }

    // 获取线性基中的最小元素（非零）
    long long get_min() {
        for (int i = 0; i <= max_bit; ++i) {
            if (p[i]) return p[i];
        }
        return 0;  // 只有存在零向量时才会执行到这里
    }

    // 获取线性基能表示的最大值
    long long get_max() {
        return ask_max(0);
    }

    // 查询第k小的异或值（包含零向量）
    long long min_k(long long k) {
        if (k <= 0) return -1;
        if (zero) {                     // 处理零向量特殊情况
            if (--k == 0) return 0;
        }
        if (k >= (1LL << cnt_h)) return -1;

        sort_H();  // 预处理基向量排序
        long long ans = 0;
        int count = 0;
        for (int i = 0; i <= max_bit; ++i) {
            if (!p[i]) continue;
            if (k & (1LL << count)) ans ^= p[i];  // 二进制选择基向量
            ++count;
        }
        return ans;
    }

    // 查询第k大的异或值
    long long max_k(long long k) {
        long long total = (1LL << cnt_h) - !zero;  // 计算总数
        if (k <= 0 || k > total) return -1;
        return min_k(total - k + 1);     // 转换为第k小问题
    }

    /* 辅助功能 */
    // 检查x是否可以被线性基表示
    bool check(long long x) {
        if(x == 0) return zero == 1;
        for (int i = max_bit; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (p[i]) x ^= p[i];
                else return false;
            }
        }
        return true;
    }

    // 合并另一个线性基（或数组）到当前基
    void merge(const std::vector<long long>& a) {
        for (auto x : a) insert(x);
    }
};