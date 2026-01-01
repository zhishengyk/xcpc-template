// 拉格朗日插值函数：通过已知的k个点值，计算多项式在n处的值
// 参数：
//   f: 向量，存储多项式在x=1,2,...,k处的函数值（f[1]到f[k]）
//   k: 已知点的数量（多项式次数m = k-1）
//   n: 要求解的x值
// 返回值：多项式在x=n处的值f(n)
int lagrange(std::vector<int> f, int k, int n) {
    int res = 0; // 存储最终结果

    // 预处理前缀积和后缀积
    int pre[k + 2], suf[k + 2]; // pre[i] = (n-1)(n-2)...(n-i), suf[i] = (n-i)(n-(i+1))...(n-k)
    pre[0] = 1;                 // 前缀积初始化
    suf[k + 1] = 1;             // 后缀积初始化

    // 计算前缀积：pre[i] = Π_{j=1}^i (n-j)
    for (int i = 1; i <= k; ++i) {
        pre[i] = 1ll * pre[i - 1] * (n - i) % p; // 递推计算前缀积
    }

    // 计算后缀积：suf[i] = Π_{j=i}^k (n-j)
    for (int i = k; i >= 1; --i) {
        suf[i] = 1ll * suf[i + 1] * (n - i) % p; // 递推计算后缀积
    }

    // 组合所有部分计算拉格朗日插值结果
    for (int i = 1; i <= k; ++i) {
        // 计算拉格朗日基函数L_i(n)的分子部分：pre[i-1] * suf[i+1]
        // 即 Π_{j≠i} (n-j) = (n-1)(n-2)...(n-(i-1)) * (n-(i+1))...(n-k)
        int numerator = 1ll * pre[i - 1] * suf[i + 1] % p;

        // 计算拉格朗日基函数的分母部分：fac[i-1] * fac[k-i] * (-1)^{k-i}
        // 其中fac[i]是i的阶乘，inv()是模逆元函数
        int denominator = 1ll * inv(fac[i - 1]) * inv(fac[k - i]) % p;

        // 根据(k-i)的奇偶性决定符号
        if ((k - i) & 1) {
            // 当(k-i)为奇数时，符号为负
            res = (res - 1ll * f[i] * numerator % p * denominator % p + p) % p;
} else {
            // 当(k-i)为偶数时，符号为正
            res = (res + 1ll * f[i] * numerator % p * denominator % p + p) % p;
        }
    }

    return res; // 返回插值结果f(n)
}