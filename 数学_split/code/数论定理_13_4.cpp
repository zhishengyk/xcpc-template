const int inv2=
const int inv6=
const int P=
struct val {
    int f; //(ai+b)/c 对i属于[0,n]求和
    int g; //[(ai+b)/c]*[(ai+b)/c]对i属于[0,n]求和
    int h; //[(ai+b)/c]*i对i属于[0,n]求和
};
val calc(int a, int b, int c, int n) {
    val ans, prec;
    if (a == 0) {
        ans.f = b / c * (n + 1);
        ans.g = b / c * n * (n + 1) * inv2;
        ans.h = b / c * (b / c) * (n + 1);
} else if (a >= c || b >= c) {
        prec = calc(a % c, b % c, c, n);
        ans.f = (prec.f + n * (n + 1) * inv2 * (a / c) + (n + 1) * (b / c));
        ans.g = ((a / c) * n * (n + 1) * (2 * n + 1) * inv6 + (b / c) * n * (n + 1) * inv2 + prec.g);
        ans.h = (prec.h + (a / c) * (a / c) * n * (n + 1) * (2 * n + 1) * inv6 + (n + 1) * (b / c) * (b / c) + 2 * (a / c) * prec.g + 2 * (b / c) * prec.f + 2 * (a / c) * (b / c) * n * (n + 1) * inv2);
} else {
        int m = (a * n + b) / c;
        prec = calc(c, c - b - 1, a, m - 1);
        ans.f = (n * m-prec.f);
        ans.g = (n * (n + 1) * m-prec.f - prec.h) * inv2;
        ans.h = (n * m * (m + 1) - 2 * prec.g - 2 * prec.f - ans.f);
    }
    return ans;
}