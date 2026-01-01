    ll n, c, m;
    std::cin >> n >> c >> m;
    Poly a(n);
    for (auto &x : a) {
        std::cin >> x;
    }
    Poly s(n), t(n + m - 1);
    auto calc = [&](ll x) -> ll {
        return 1ll * x * (x - 1) / 2;
    };
    for (int i = 0; i < n; ++i) {
        s[i] = 1ll * a[n - 1 - i] * inv(qmi(c, calc(n - i - 1))) % P;
    }
    for (int i = 0; i < n + m - 1; ++i) {
        t[i] = qmi(c, calc(i));
    }
    s = s * t;
    for (int i = 0; i < m; ++i) {
        int ans = 1ll * inv(qmi(c, calc(i))) * s[n + i - 1] % P;
        std::cout << ans << " \n"[i + 1 == m];
    }