
using ll = long long;
using ld = long double;

const ld EPS = 1e-12;

struct P {
    ld x, y, z;
    P operator+(const P &o) const { return {x + o.x, y + o.y, z + o.z}; }
    P operator-(const P &o) const { return {x - o.x, y - o.y, z - o.z}; }
    P operator*(ld k) const { return {x * k, y * k, z * k}; }
    P operator/(ld k) const { return {x / k, y / k, z / k}; }
};
inline ld dot(const P &a, const P &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline P cross(const P &a, const P &b) {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}
inline ld norm2(const P &a) { return dot(a, a); }
inline ld dist(const P &a, const P &b) { return std::sqrt(norm2(a - b)); }
struct Sphere {
    P c;
    ld r;
};
inline bool check(const Sphere &s, const P &p) {
    return dist(s.c, p) <= s.r + EPS;
}
// 两点球
Sphere calc(const P &a, const P &b) {
    P o = (a + b) / 2.0L;
    return {o, dist(a, b) / 2.0L};
}

// 三点球（唯一确定一个外接圆，球心在平面内）
Sphere calc(const P &a, const P &b, const P &c) {
    P ab = b - a, ac = c - a;
    P abXac = cross(ab, ac);
    ld d = 2 * norm2(abXac);
    if (d < EPS)
    { // 三点共线
        Sphere s1 = calc(a, b);
        Sphere s2 = calc(a, c);
        Sphere s3 = calc(b, c);
        Sphere res = s1;
        if (s2.r > res.r)
            res = s2;
        if (s3.r > res.r)
            res = s3;
        return res;
    }
    P ab_mid = (a + b) / 2.0L;
    P ac_mid = (a + c) / 2.0L;
    P n = abXac;

    // 球心计算公式
    P num = cross(abXac, ab) * norm2(ac) - cross(abXac, ac) * norm2(ab);
    P o = a + num / d;
    return {o, dist(o, a)};
}

// 四点外接球
Sphere calc(const P &a, const P &b, const P &c, const P &d) {
    ld a1 = b.x - a.x, a2 = b.y - a.y, a3 = b.z - a.z;
    ld b1 = c.x - a.x, b2 = c.y - a.y, b3 = c.z - a.z;
    ld c1 = d.x - a.x, c2 = d.y - a.y, c3 = d.z - a.z;

    ld a_len = norm2(b) - norm2(a);
    ld b_len = norm2(c) - norm2(a);
    ld c_len = norm2(d) - norm2(a);

    ld det = a1 * (b2 * c3 - b3 * c2) - a2 * (b1 * c3 - b3 * c1) + a3 * (b1 * c2 - b2 * c1);

    if (fabsl(det) < EPS) {
        // 退化成三点球
        Sphere s1 = calc(a, b, c);
        if (!check(s1, d)) {
            Sphere s2 = calc(a, b, d);
            if (!check(s2, c)) {
                Sphere s3 = calc(a, c, d);
                if (!check(s3, b)) {
                    return calc(b, c, d);
                }
                return s3;
            }
            return s2;
        }
        return s1;
    }
    P o;
    o.x = (a_len * (b2 * c3 - b3 * c2) - b_len * (a2 * c3 - a3 * c2) + c_len * (a2 * b3 - a3 * b2)) / (2 * det);
    o.y = (a_len * (b3 * c1 - b1 * c3) - b_len * (a3 * c1 - a1 * c3) + c_len * (a3 * b1 - a1 * b3)) / (2 * det);
    o.z = (a_len * (b1 * c2 - b2 * c1) - b_len * (a1 * c2 - a2 * c1) + c_len * (a1 * b2 - a2 * b1)) / (2 * det);

    return {o, dist(o, a)};
}
// 随机增量法
Sphere work(std::vector<P> pts) {
    std::mt19937_64 rng((unsigned long long)(new char));
    std::shuffle(pts.begin(), pts.end(), rng);
    Sphere s{pts[0], 0};
    int n = pts.size();
    for (int i = 1; i < n; ++i) {
        if (check(s, pts[i]))
            continue;
        s = {pts[i], 0};
        for (int j = 0; j < i; ++j) {
            if (check(s, pts[j]))
                continue;
            s = calc(pts[i], pts[j]);
            for (int k = 0; k < j; ++k) {
                if (check(s, pts[k]))
                    continue;
                s = calc(pts[i], pts[j], pts[k]);
                for (int l = 0; l < k; ++l) {
                    if (check(s, pts[l]))
                        continue;
                    s = calc(pts[i], pts[j], pts[k], pts[l]);
                }
            }
        }
    }
    return s;
}