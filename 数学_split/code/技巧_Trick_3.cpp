template <class T>
struct PollardRho : public MillerRabin<T> {
    std::mt19937 myrand;
    PollardRho(const i64 seed = time(0)) : myrand(seed) {}

    constexpr T rd(T l, T r) {
        return std::uniform_int_distribution<T>(l, r)(myrand);
    }
    constexpr T operator()(T n)
    { // 返回 n 的随机一个[2, n-1]内的因子, 或者判定是质数
        if (n == 4) {
            return 2;
        }
        MillerRabin<T> &super = *this;
        if (super(n)) {
            return n; // 如果 n 是质数直接返回 n
        } // Miller-Rabbin 判质数
        while (true) {
            T c = rd(1, n - 1);
            auto f = [&](T x)
            { return (super.mulp(x, x, n) + c) % n; };
            T t = 0, r = 0, p = 1, q;
            do {
                for (int i = 0; i < 128; i++) {
                    t = f(t), r = f(f(r));
                    if (t == r || (q = super.mulp(p, std::abs(t - r), n)) == 0) {
                        break;
                    }
                    p = q;
                }
                T d = std::gcd<T>(p, n);
                if (d > 1) {
                    return d;
                }
            } while (t != r);
        }
    }
};
PollardRho<i64> findDiv;