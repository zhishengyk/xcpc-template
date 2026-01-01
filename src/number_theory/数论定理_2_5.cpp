// 返回 n 的四平方和表示 a^2+b^2+c^2+d^2
// 尽量让 a,b,c 尽量小（更多 0）
std::vector<int> fourSquareSum(int n) {
    std::vector<int> squares;
    std::unordered_set<int> sq_set;

    int lim = sqrt(n);
    for (int i = 0; i <= lim; ++i) {
        int sq = i * i;
        squares.push_back(sq);
        sq_set.insert(sq);
    }
    // 1. 检查 1 个平方数
    if (sq_set.count(n)) {
        return {int(sqrt(n)), 0, 0, 0};
    }
    // 2. 检查 2 个平方数
    for (int a = 0; a * a <= n; ++a) {
        int rem = n - a * a;
        if (sq_set.count(rem)) {
            int b = sqrt(rem);
            return {a, b, 0, 0};
        }
    }

    // 3. 检查 3 个平方数
    for (int a = 0; a * a <= n; ++a) {
        for (int b = 0; a * a + b * b <= n; ++b) {
            int rem = n - a * a - b * b;
            if (sq_set.count(rem)) {
                int c = sqrt(rem);
                return {a, b, c, 0};
            }
        }
    }
    // 4. 最后使用 4 个平方数
    // 枚举 a,b，然后剩余 rem 用两平方和快速查找
    for (int a = 0; a * a <= n; ++a) {
        for (int b = 0; a * a + b * b <= n; ++b) {
            int rem = n - a * a - b * b;
            for (int c = 0; c * c <= rem; ++c) {
                int d2 = rem - c * c;
                if (sq_set.count(d2)) {
                    int d = sqrt(d2);
                    return {a, b, c, d};
                }
            }
        }
    }
    return {0, 0, 0, 0}; // 不可能到这里
}