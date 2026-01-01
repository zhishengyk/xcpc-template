std::vector<int> treePru(std::vector<int> &fa, int n) { // n为根 fa是[1,n-1]的父亲节点
    std::vector<int> deg(n + 1, 0);
    std::vector<int> pru(n - 1, 0);
    for (int i = 1; i < n; ++i) {
        ++deg[fa[i]];
    }
    for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
        while (deg[j]) {
            ++j;
        }
        pru[i] = fa[j];
        while (i < n - 2 && !--deg[pru[i]] && pru[i] < j) {
            pru[i + 1] = fa[pru[i]];
            ++i;
        }
    }
    return pru; // n-2个点
}
std::vector<int> pruTree(std::vector<int> &pru, int n) {
    std::vector<int> deg(n + 1, 0);
    std::vector<int> fa(n + 1, 0);
    pru.resize(n);
    for (int i = 1; i <= n - 2; ++i) {
        ++deg[pru[i]];
    }
    pru[n - 1] = n;
    for (int i = 1, j = 1; i < n - 1; ++i, ++j) {
        while (deg[j]) {
            ++j;
        }
        fa[j] = pru[i];
        while (i < n - 1 && !--deg[pru[i]] && pru[i] < j) {
            fa[pru[i]] = pru[i + 1];
            ++i;
        }
    }
    fa.resize(n);
    return fa;
}