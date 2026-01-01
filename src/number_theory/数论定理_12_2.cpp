
int calc(int a, int b, int c, int n) { //(ai+b)/c 对i属于[0,n]求和
    if (a == 0) {
        return b / c * (n + 1);
} else if (a >= c || b >= c) {
        return (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1) + calc(a % c, b % c, c, n);
} else {
        return (a * n + b) / c * n - calc(c, c - b - 1, a, (a * n + b) / c - 1);
    }
}