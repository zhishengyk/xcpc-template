const double InitT = 1e5, dec = 0.999998, END = 1e-12;
std::function<int(std::vector<int>&)> check = [&](std::vector<int> &p) {
    int res = 0, rem = k;
    for (auto i : p) {
        if (rem >= a[i]) {
            rem -= a[i];
            res += b[i];
        }
    }
    return res;
};

std::function<void()> solve = [&]() {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    double T = InitT;
    while (T > END) {
        int x = rng() % n, y = rng() % n;
        std::swap(p[x], p[y]);
        int tmpans = check(p), delta = tmpans - ans;
        if (delta > 0) {
            ans = tmpans;
        } else if (exp(-delta / T) * RAND_MAX < rand()) {
            std::swap(p[x], p[y]);
        }
        T *= dec;
    }
};