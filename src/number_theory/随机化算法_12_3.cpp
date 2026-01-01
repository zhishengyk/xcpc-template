int determinant(std::vector<std::vector<int>> a, int n) {
    int res = 1, w = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; ++j) {
            while (a[i][i]) {
                int div = a[j][i] / a[i][i];
                for (int k = i; k <= n; ++k) {
                    a[j][k] = (a[j][k] - 1ll * div * a[i][k] % p + p) % p;
                }
                swap(a[i], a[j]);
                w = -w;
            } // 对第 i 行和第 j 行做辗转相减。不断交换次序相减
            swap(a[i], a[j]);
            w = -w;
        }
    }
    for (int i = 1; i <= n; i++) { // 化成上三角
        res = 1ll * a[i][i] * res % p; // 全部乘起来
    }
    res = 1ll * w * res;  // 正负问题
    return (res + p) % p;
}
