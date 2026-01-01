void fourSquares(int n) {
    for (int a = 0; a * a <= n; ++a)
        for (int b = 0; a * a + b * b <= n; ++b)
            for (int c = 0; a * a + b * b + c * c <= n; ++c) {
                int d2 = n - a * a - b * b - c * c;
                int d = sqrt(d2);
                if (d * d == d2) {
                    std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
                    return;
                }
            }
}