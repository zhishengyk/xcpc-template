struct matrix {
    int Mat[N + 1][N + 1];
    matrix() {
        memset(Mat, 0, sizeof Mat);
    }
};
matrix operator*(matrix x, matrix y) {
    matrix t;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 1; k <= N; ++k) {
                t.Mat[i][j] = (t.Mat[i][j] + 1ll * x.Mat[i][k] * y.Mat[k][j] % p) % p;
            }
        }
    }
    return t;
}
matrix qmi(matrix a, int b) {
    matrix res;
    for (int i = 1; i <= N; ++i) {
        res.Mat[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}