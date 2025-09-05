#include "IO/FastIO.h"
#include "MATH/Eratosthenes.h"
#include "MATH/Mobius.h"

/*
[炫酷反演魔术](https://ac.nowcoder.com/acm/problem/244326)
*/
/**
 *  上面的链接打不开
 *  请换用这个链接 https://ac.nowcoder.com/acm/contest/43058/E
 *  求                  \Sigma_{i=1}^n \Sigma_{j=1}^n \phi(gcd(a[i],a[j]^3))
 *  恰好 a[i] 值域也在 1~n，设 cnt(i) 为 a 数组里值 i 出现次数
 *  即                  \Sigma_{i=1}^n \Sigma_{j=1}^n \phi(gcd(i,j^3)) cnt(i) cnt(j)
 *  我们更习惯枚举 gcd
 *  即                  \Sigma_{d=1}^n \phi(d) \Sigma_{i=1}^n cnt(i) \Sigma_{j=1}^n cnt(j)*[d==gcd(i,j^3)]
 *  即                  \Sigma_{d=1}^n \phi(d) \Sigma_{i=1}^(n/d) cnt(i*d) \Sigma_{d|(j^3)} cnt(j)*[d==gcd(i*d,j^3)]
 *
 *  这里由于 j 是三次方，化不开了。不管了，继续下一步
 *  即                  \Sigma_{d=1}^n \phi(d) \Sigma_{i=1}^(n/d) cnt(i*d) \Sigma_{d|(j^3)} cnt(j)*[1==gcd(i,j^3/d)]
 *  根据 [x==1]=\Sigma_{d|x} \mu(d)
 *  即                  \Sigma_{d=1}^n \phi(d) \Sigma_{i=1}^(n/d) cnt(i*d) \Sigma_{d|(j^3)} cnt(j) \Sigma_{e|gcd(i,j^3/d)} \mu(e)
 *  把枚举 e 往前放
 *  即                  \Sigma_{d=1}^n \phi(d) \Sigma_{e=1}^(n/d) \mu(e) \Sigma_{i=1}^(n/d/e) cnt(i*d*e) \Sigma_{(d*e)|(j^3)} cnt(j)
 *  把 d*e 设为一个整体 S=d*e
 *  即                  \Sigma_{S=1}^n \Sigma_{d|S} \phi(d) \mu(S/d) \Sigma_{i=1}^(n/S) cnt(i*S) \Sigma_{S|(j^3)} cnt(j)
 *  即                  \Sigma_{S=1}^n \Sigma_{d|S} \phi(d) \mu(S/d) \Sigma_{S|i) cnt(i) \Sigma_{S|(j^3)} cnt(j)
 *  设 f(x)=\Sigma_{d|x} \phi(d) \mu(x/d)
 *  设 g(x)=\Sigma_{x|i) cnt(i)
 *  设 h(x)=\Sigma_{x|(j^3)} cnt(j)
 *  原式等于            \Sigma_{S=1}^n f(S) g(S) h(S)
 */

static constexpr uint32_t N = 300000;
void solve_inex() {
    // 考虑莫比乌斯反演本质是容斥
    // 由于 gcd(a_i, a_j^3) 的范围是 [1,n]，所以考虑枚举 gcd 结果
    // 考虑枚举 f(x) =count(gcd==x) 的结果数很难算，不妨考虑 g(x)=count(x|gcd) 的结果数
    // 比如 x = 7*7*7*11*11
    // 那么要求 a_i 必须是 x 的倍数
    //         a_j 必须是 7*11 的倍数
    uint32_t n;
    cin >> n;
    OY::Eratosthenes::Sieve<N, true, true, false> es(n);
    std::vector<uint32_t> cnt(n + 1);
    std::vector<uint32_t> arr(n + 1);
    for (uint32_t i = 1; i <= n; i++) cin >> arr[i], cnt[arr[i]]++;

    // 做一下前缀和，令 cnt[x] 保存 x 的倍数的个数
    OY::MOBIUS::partial_sum_Dirichlet_multiple(n, cnt.data(), [&](uint32_t k) { return es.query_kth_prime(k); });

    std::vector<uint64_t> res(n + 1);
    for (uint32_t x = 1; x <= n; x++) {
        uint32_t cur = x, x2 = 1;
        while (cur != 1) {
            uint32_t p = es.query_smallest_factor(cur);
            uint32_t _cnt = 0;
            while (es.query_smallest_factor(cur) == p) _cnt++, cur /= p;
            for (_cnt = (_cnt + 2) / 3; _cnt--;) x2 *= p;
        }
        res[x] = uint64_t(cnt[x]) * cnt[x2];
    }

    // 做一下前缀和，令 cnt[x] 保存 x 的倍数的个数
    OY::MOBIUS::adjacent_difference_Dirichlet_multiple(n, res.data(), [&](uint32_t k) { return es.query_kth_prime(k); });

    uint64_t ans = 0;
    for (uint32_t x = 1; x <= n; x++)
        ans += res[x] * es.get_Euler_Phi(x);
    cout << ans;
}

uint32_t f[N + 1], g[N + 1];
void solve_mobius() {
    uint32_t n;
    cin >> n;
    OY::Eratosthenes::Sieve<N, false, true, false> es(n);
    std::vector<uint32_t> cnt(n + 1);
    std::vector<uint32_t> arr(n + 1);
    for (uint32_t i = 1; i <= n; i++) cin >> arr[i], cnt[arr[i]]++;

    // 预处理出 f
    auto calc_prime = [&](uint32_t p) { return p - 2; };
    auto calc_prime_pow = [&](uint32_t p, uint32_t cnt, uint32_t low) { return f[low] * p + (low == p); };
    OY::MOBIUS::Multiplicative<N>().solve(n, f, calc_prime, calc_prime_pow);
    // 预处理 g，可以使用迪利克雷后缀和方法，求每个倍数位置的和
    std::copy_n(cnt.data(), n + 1, g);
    OY::MOBIUS::partial_sum_Dirichlet_multiple(n, g, [&](uint32_t k) { return es.query_kth_prime(k); });
    // 预处理 h 没必要。比如 x = p1^10 * p2^3 * p3^5，那么 h[x] 直接去找 g[p1^4 * p2^1 * p3^2] 即可
    uint64_t ans{};
    for (uint32_t i = 1; i <= n; i++) {
        auto mp = es.decomposite(i);
        uint32_t i2 = 1;
        for (auto [p, cnt] : mp) {
            cnt = (cnt + 2) / 3;
            while (cnt--) i2 *= p;
        }
        ans += uint64_t(f[i]) * g[i] * g[i2];
    }
    cout << ans;
}

int main() {
    solve_inex();
    // solve_mobius();
}
