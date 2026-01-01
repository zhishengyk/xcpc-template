// 假设Poly类和相关NTT实现已经存在
/**
 * @class bigInt
 * @brief 使用NTT优化的高精度计算器，支持加、减、乘运算
 *
 * 这个类封装了基于NTT(数论变换)的高效大整数算法，
 * 可以将用字符串表示的大整数进行加、减、乘运算。
 */
class bigInt {
public:
    bigInt() = default;
    std::string nttMul(const std::string &a, const std::string &b) {
        if (a.empty() || b.empty()) {
            return "0";
        }
        bool neg = false;
        std::string n1 = a, n2 = b;
        if (a[0] == '-') {
            neg = !neg;
            n1 = a.substr(1);
        }
        if (b[0] == '-') {
            neg = !neg;
            n2 = b.substr(1);
        }

        int n = n1.size(), m = n2.size();
        Poly a(n), b(m);
        for (int i = 0; i < n; ++i) {
            a[i] = n1[i] - '0';
        }
        for (int i = 0; i < m; ++i) {
            b[i] = n2[i] - '0';
        }
        Poly c = a * b;
        for (int i = c.size() - 1; i >= 1; --i) {
            c[i - 1] += c[i] / 10; // 向前进位
            c[i] %= 10;            // 保留个位数
        }
        std::string res = pToS(c);
        if (neg && res != "0") {
            res = "-" + res;
        }

        return res;
    }
    std::string mul(const std::string &a, const std::string &b) {
        if (a.empty() || b.empty()) {
            return "0";
        }
        bool neg = false;
        std::string n1 = a, n2 = b;
        if (a[0] == '-') {
            neg = !neg;
            n1 = a.substr(1);
        }
        if (b[0] == '-') {
            neg = !neg;
            n2 = b.substr(1);
        }
        if (n1 == "0" || n2 == "0") {
            return "0";
        }
        int len1 = n1.size();
        int len2 = n2.size();
        std::vector<int> res(len1 + len2, 0);
        for (int i = len1 - 1; i >= 0; --i) {
            for (int j = len2 - 1; j >= 0; --j) {
                int c = (n1[i] - '0') * (n2[j] - '0');
                int sum = c + res[i + j + 1];

                res[i + j + 1] = sum % 10; // 当前位
                res[i + j] += sum / 10;    // 进位
            }
        }
        std::string ans;
        for (int a : res) {
            if (!(ans.empty() && a == 0))
            { // 跳过前导零
                ans += std::to_string(a);
            }
        }
        // 处理全零的情况（理论上不会发生）
        if (ans.empty()) {
            return "0";
        }
        // 处理符号
        if (neg) {
            ans = "-" + ans;
        }
        return ans;
    }
    std::string add(const std::string &a, const std::string &b) {
        if (a.empty())
            return b;
        if (b.empty())
            return a;
        // 处理两个数都是负数的情况
        if (a[0] == '-' && b[0] == '-') {
            return "-" + add(a.substr(1), b.substr(1));
        }
        // 处理只有一个数是负数的情况（转换为减法）
        if (a[0] == '-') {
            return subtract(b, a.substr(1));
        }
        if (b[0] == '-') {
            return subtract(a, b.substr(1));
        }
        // 确保num1是较长的数字
        if (a.length() < b.length()) {
            return add(b, a);
        }
        std::string res;
        int carry = 0;
        int diff = a.length() - b.length();
        // 从最低位开始相加
        for (int i = a.length() - 1; i >= 0; --i) {
            int d1 = a[i] - '0';
            int d2 = (i >= diff) ? b[i - diff] - '0' : 0;

            int sum = d1 + d2 + carry;
            carry = sum / 10;
            res.push_back(sum % 10 + '0');
        }
        if (carry > 0) {
            res.push_back(carry + '0');
        }
        // 反转结果字符串
        std::reverse(res.begin(), res.end());
        // 去除前导零
        return norm(res);
    }
    std::string subtract(const std::string &a, const std::string &b) {
        // 检查输入是否为空
        if (b.empty())
            return a;
        if (a.empty())
            return (b[0] == '-') ? b.substr(1) : "-" + b;
        // 处理两个数都是负数的情况
        if (a[0] == '-' && b[0] == '-') {
            return subtract(b.substr(1), a.substr(1));
        }
        // 处理被减数是负数的情况
        if (a[0] == '-') {
            return "-" + add(a.substr(1), b);
        }
        // 处理减数是负数的情况
        if (b[0] == '-') {
            return add(a, b.substr(1));
        }
        // 比较两个数的大小
        int cmp = compare(a, b);
        if (cmp == 0) {
            return "0";
        }
        bool neg = (cmp < 0);
        std::string ma = neg ? b : a;
        std::string mi = neg ? a : b;

        std::string res;
        int borrow = 0;
        int diff = ma.length() - mi.length();

        // 从最低位开始相减
        for (int i = ma.length() - 1; i >= 0; --i) {
            int d1 = ma[i] - '0' - borrow;
            int d2 = (i >= diff) ? mi[i - diff] - '0' : 0;

            borrow = 0;

            if (d1 < d2) {
                d1 += 10;
                borrow = 1;
            }
            res.push_back(d1 - d2 + '0');
        }
        // 反转结果字符串
        std::reverse(res.begin(), res.end());
        // 去除前导零
        res = norm(res);
        // 添加负号（如果需要）
        if (neg) {
            res = "-" + res;
        }
        return res;
    }

private:
    int compare(const std::string &a, const std::string &b) const {
        if (a.length() != b.length()) {
            return a.length() > b.length() ? 1 : -1;
        }
        for (size_t i = 0; i < a.length(); ++i) {
            if (a[i] != b[i]) {
                return a[i] > b[i] ? 1 : -1;
            }
        }
        return 0;
    }
    /**
     * @brief 去除字符串中的前导零
     * @param a 数字字符串
     * @return 去除前导零后的字符串
     */
    std::string norm(const std::string &a) const {
        size_t start = 0;
        while (start < a.length() - 1 && a[start] == '0') {
            start++;
        }
        return a.substr(start);
    }
    /**
     * @brief 将多项式转换为字符串
     * @param p 多项式
     * @return 转换后的字符串
     */
    std::string pToS(const Poly &p) const {
        std::string res;
        bool leadZero = true; // 标记是否还在处理前导零

        for (auto d : p) {
            if (d == 0 && leadZero) {
                continue; // 跳过前导零
            }
            leadZero = false;
            res += std::to_string(d);
        }
        // 如果结果全为零，返回"0"
        if (res.empty()) {
            return "0";
        }
        return res;
    }
};
bigInt calc;
