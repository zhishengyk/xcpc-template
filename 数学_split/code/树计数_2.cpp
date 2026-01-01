int MatrixTree(std::vector<std::array<int, 3>> &g, int type, int root, int n) {
    std::vector Mat(n, std::vector<int>(n, 0));
    if (type == 0) // 无向图 {
        for (auto [u, v, w] : g) {
            if (u < n) {
                Mat[u][u] += w;
            }
            if (v < n) {
                Mat[v][v] += w;
            }
            if (u < n and v < n) {
                Mat[u][v] -= w;
                Mat[v][u] -= w;
            }
        }
        return determinant(Mat, n - 1);
} else if (type == 1)          // 外向树
    {                            // 我们想办法把root换成n即可
        for (auto [u, v, w] : g) // u->v {
            if (u == root) {
                u = n;
} else if (u == n) {
                u = root;
            }
            if (v == root) {
                v = n;
} else if (v == n) {
                v = root;
            }
            if (v < n) {
                Mat[v][v] += w;
            }
            if (v < n and u < n) {
                Mat[u][v] -= w;
            }
        }
        return determinant(Mat, n - 1);
} else {
        for (auto [u, v, w] : g) // u->v {
            if (u == root) {
                u = n;
} else if (u == n) {
                u = root;
            }
            if (v == root) {
                v = n;
} else if (v == n) {
                v = root;
            }
            if (u < n) {
                Mat[u][u] += w;
            }
            if (v < n and u < n) {
                Mat[u][v] -= w;
            }
        }
        return determinant(Mat, n - 1);
    }
}