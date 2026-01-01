using ld = long double;

// ===================== 非递归自适应辛普森法 =====================
// F: 被积函数类型
// a, b: 积分区间
// eps: 精度要求（可选）
template <typename F>
ld adaptiveSimpsonIter(F f, ld a, ld b, ld eps = 1e-12) {
    struct Node {
        ld l, r; // 区间 [l, r]
        ld S;    // 该区间辛普森积分
        ld eps;  // 当前误差要求
    };

    auto simpson = [&](ld l, ld r) -> ld {
        ld m = (l + r) / 2;
        return (r - l) / 6 * (f(l) + 4 * f(m) + f(r));
    };

    std::stack<Node> stk;
    ld result = 0;

    // 初始化区间
    stk.push({a, b, simpson(a, b), eps});

    while (!stk.empty()) {
        Node cur = stk.top();
        stk.pop();

        ld l = cur.l, r = cur.r, S = cur.S, e = cur.eps;
        ld m = (l + r) / 2;
        ld Sleft = simpson(l, m);
        ld Sright = simpson(m, r);

        // 精度满足，累加积分
        if (std::abs(Sleft + Sright - S) <= 15 * e) {
            result += Sleft + Sright + (Sleft + Sright - S) / 15.0;
} else {
            // 左右子区间继续细分，误差按比例分配
            stk.push({m, r, Sright, e / 2});
            stk.push({l, m, Sleft, e / 2});
        }
    }

    return result;
}

// ===================== 示例使用 =====================
int main() {
    auto f = [](ld x) {
        return std::sin(x);
    };
    ld res = adaptiveSimpsonIter(f, 0, acosl(-1));
    std::cout << std::setprecision(20) << res << "\n"; // 理论值为 2
}
