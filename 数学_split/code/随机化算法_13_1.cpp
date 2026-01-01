const long double eps = 1e-8;
int gauss(std::vector<std::vector<long double>> &a, int n) {
    int col, row;
    for (col = 0, row = 0; col < n; col++) { // 注意下标是从0开始的 n是未知数的个数
        int tmp = row;
        for (int i = row; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[tmp][col])) {
                tmp = i;
            }
        }
        if (fabs(a[tmp][col]) < eps) { // 为0
            continue;
        }
        // tmp是绝对值最大的位置
        // row是最上面的位置
        // 把这两行完全交换
        for (int i = col; i <= n; i++) {
            std::swap(a[tmp][i], a[row][i]);
        }
        for (int i = n; i >= col; i--) {
            a[row][i] /= a[row][col];
        }
        for (int i = row + 1; i < n; i++) {
            if (fabs(a[i][col]) > eps) {
                for (int j = n; j >= col; j--) {
                    a[i][j] -= a[row][j] * a[i][col];
                }
            }
        }
        row++;
    } // 这个循环的作用是消成上三角
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            a[i][n] -= a[i][j] * a[j][n]; // 得到正确的解
        }
    }
    if (row < n) { // 这里说明[row,n-1]的行已经没系数了
        for (int i = row; i < n; i++) {
            if (fabs(a[i][n]) > eps) { // 此刻还有值就是无解
                return -1; // 无解
            }
        }
        return 1; // 有无穷多组解 因为存在自由元
    }
    return 0; // 有唯一解  a[i][n]为各个解(i从0到n-1)
}
