const int N = 1001;
std::vector<int> Gauss(std::vector<std::bitset<N>> &equation, std::vector<int> &res, int n) {
    int m = equation.size();
    std::vector<int> ans(n, 0);
    int row = 0;

    // 前向消元
    for (int col = 0; col < n && row < m; ++col) {
        // 寻找主元
        int pivot = -1;
        for (int i = row; i < m; ++i) {
            if (equation[i][col]) {
                pivot = i;
                break;
            }
        }

        if (pivot == -1)
            continue; // 自由元

        // 交换行
        if (pivot != row) {
            std::swap(equation[row], equation[pivot]);
            std::swap(res[row], res[pivot]);
        }

        // 消去其他行
        for (int i = 0; i < m; ++i) {
            if (i != row && equation[i][col]) {
                equation[i] ^= equation[row];
                res[i] ^= res[row];
            }
        }

        ++row;
    }

    // 检查无解情况
    for (int i = row; i < m; ++i) {
        if (res[i]) {
            return {-1}; // 无解
        }
    }

    // 回代求解
    for (int i = 0; i < n; ++i) {
        ans[i] = -1; // 初始化为自由元
    }

    for (int i = row - 1; i >= 0; --i) {
        // 找到主元列
        int col = 0;
        while (col < n && !equation[i][col])
            ++col;

        if (col >= n)
            continue; // 全零行

        ans[col] = res[i];
        // 标记非自由元
        for (int j = col + 1; j < n; ++j) {
            if (equation[i][j]) {
                if (ans[j] == -1) {
                    // 自由元可以任意取值，这里设为0
                    ans[j] = 0;
                }
                ans[col] ^= ans[j];
            }
        }
    }
    // 处理自由元（设为0）
    for (int i = 0; i < n; ++i) {
        if (ans[i] == -1) {
            ans[i] = 0;
        }
    }

    return ans;
}