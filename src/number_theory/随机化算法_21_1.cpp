long double calc(long double x) {
}

long double search(long double l, long double r, long double epsilon = 1e-9) {
    while (r - l > epsilon) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r - (r - l) / 3;
        if (calc(m1) > calc(m2)) {
            r = m2; // 左侧更优
} else {
            l = m1; // 右侧更优
        }
    }
    return (l + r) / 2; // 返回最优点
}