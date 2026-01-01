int calc(int x) {

}
int search(int l, int r) {
    const int corner = 2;
    while (r - l > corner)
    { // 精度到达三分间隔时停止
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if (calc(m1) > calc(m2)) {
            r = m2; // 左侧更优
} else {
            l = m1; // 右侧更优
        }
    }
    int res = l;
    for (int i = l + 1; i <= r; ++i) {
        if (calc(i) > calc(res)) {
            res = i;
        }
    }
    return res;
}