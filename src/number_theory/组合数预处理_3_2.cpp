void gospersHack(int n, int k) { // 一共n个位 保证其中有k个1
    int cur = (1 << k) - 1;
    int limit = 1 << n;
    while (cur < limit) {
        std::cerr << cur << '\n';
        // cur是我们想要的数字
        int lb = cur & (-cur);
        int r = cur + lb;
        cur = ((r ^ cur)) >> __builtin_ctz(lb) + 2 | r;
    }
}