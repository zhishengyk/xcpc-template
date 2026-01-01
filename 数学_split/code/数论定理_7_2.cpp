template <class T>
class ExtendGcd {
public:
    ExtendGcd(T a, T b, T c)
        : a(a), b(b), c(c), hasSolution(false) {
        Work();
    }
    // 传入 ax+by=c的参数 a b c
    std::pair<T, T> particularSolution() const {
        return std::make_pair(x_, y_);
    }
    std::array<T, 4> generalSolution() const {
        auto [x, y] = particularSolution();
        return {x, b / gcd, y, a / gcd};
        // 返回通解 {x+k*b/gcd,y+k*a/gcd}
    }

private:
    T a;              // 方程系数a
    T b;              // 方程系数b
    T c;              // 方程右侧常数c
    T gcd;            // a和b的最大公约数
    T x_;             // 特解x
    T y_;             // 特解y
    bool hasSolution; // 方程是否有解

    static T extendGcd(T a, T b, T &x, T &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        T tx, ty;
        T gcd = extendGcd(b, a % b, tx, ty);
        x = ty;
        y = tx - (a / b) * ty;
        return gcd;
    }
    void Work() {
        // 特殊情况处理
        if (a == 0 && b == 0) {
            hasSolution = (c == 0);
            return;
        }

        // 计算gcd(a,b)和特解
        gcd = extendGcd(std::abs(a), std::abs(b), x_, y_);
        // 调整符号
        if (a < 0)
            x_ = -x_;
        if (b < 0)
            y_ = -y_;

        // 检查是否有解
        if (c % gcd != 0) {
            hasSolution = false;
            return;
        }
        // 调整特解以满足 ax + by = c
        T factor = c / gcd;
        x_ *= factor;
        y_ *= factor;

        hasSolution = true;
    }
};