
using ll = long long;
using ld = long double;

const ld PI = acosl(-1);
const ld EPS = 1e-12;

struct Point {
    ld x, y;
    // 向量加减
    Point operator+(const Point &o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
    Point operator*(ld k) const { return {x * k, y * k}; }
    Point operator/(ld k) const { return {x / k, y / k}; }
};
// 向量叉积
inline ld cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
// 向量旋转
inline Point rotate(const Point &a, ld ang) {
    return {a.x * cosl(ang) - a.y * sinl(ang), a.x * sinl(ang) + a.y * cosl(ang)};
}
// 距离
inline ld dist(const Point &a, const Point &b) {
    return std::hypotl(a.x - b.x, a.y - b.y);
}
struct Circle {
    Point c; // 圆心
    ld r;    // 半径
};
// 直线交点：a + t*u 与 b + s*v
Point line_intersection(Point a, Point u, Point b, Point v) {
    ld t = cross(b - a, v) / cross(u, v);
    return a + u * t;
}
std::pair<Point, Point> midperp(const Point &a, const Point &b) {
    return {(a + b) / 2.0L, rotate(b - a, PI / 2)};
}
// 两点圆
Circle circle_from(const Point &a, const Point &b) {
    return {(a + b) / 2.0L, dist(a, b) / 2.0L};
}
// 三点外接圆
Circle circle_from(const Point &a, const Point &b, const Point &c) {
    auto u = midperp(a, b);
    auto v = midperp(a, c);
    Point o = line_intersection(u.first, u.second, v.first, v.second);
    return {o, dist(o, a)};
}
// 随机增量法
Circle work(std::vector<Point> &p) {
    std::mt19937_64 rng((unsigned long long)(new char));
    std::shuffle(p.begin(), p.end(), rng);
    Circle C{p[0], 0};
    int n = (int)p.size();
    for (int i = 1; i < n; ++i) {
        if (dist(C.c, p[i]) <= C.r + EPS)
            continue;
        C = {p[i], 0};
        for (int j = 0; j < i; ++j) {
            if (dist(C.c, p[j]) <= C.r + EPS)
                continue;
            C = circle_from(p[i], p[j]);
            for (int k = 0; k < j; ++k) {
                if (dist(C.c, p[k]) <= C.r + EPS)
                    continue;
                C = circle_from(p[i], p[j], p[k]);
            }
        }
    }
    return C;
}
