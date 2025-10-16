#pragma once
#include <array>
#include <limits>
#include <type_traits>
#include <algorithm>

/*
    O(bit) 空间线性基（支持前缀位置标记）
    每个实例仅保存 1 份基向量 + 其出现位置，
    insert/merge/sub/has/mx 等接口与原版本兼容的精简实现。
*/

template <typename T,
          int K = std::numeric_limits<std::make_unsigned_t<T>>::digits - 1>
struct LB {
    static_assert(std::is_integral_v<T>);
    using A = std::array<T, K + 1>;   // 基向量
    using P = std::array<int, K + 1>; // 对应出现位置

    A b{};   // 当前基向量
    P p{};   // 对应出现深度 / 位置

    /* 在当前基里插入 (val,pos) */
    void insert(T val, int pos) { ins(b, p, val, pos); }

    /* 区间 [l,r] 提取：仅保留 pos∈[l,r] 的向量 */
    LB sub(int l, int r) const {
        LB res = *this;                // 直接复制整条基
        for (int k = 0; k <= K; ++k)   // O(K) 过滤
            if (res.p[k] < l || res.p[k] > r)
                res.b[k] = 0;          // 清掉区间外向量
        return res;
    }

    /* 合并另一条线性基 */
    void merge(const LB& oth) {
        for (int k = K; k >= 0; --k)
            if (oth.b[k]) ins(b, p, oth.b[k], oth.p[k]);
    }

    /* 判断区间 [l,r] 是否能异或得 x （简化：先提取再判） */
    bool has(int l, int r, T x) const {
        return sub(l, r).has(x);
    }

    /* 使用当前整条基判断 */
    bool has(T x) const {
        for (int k = K; k >= 0; --k)
            if (x >> k & 1) {
                if (!b[k]) return false;
                x ^= b[k];
            }
        return true;
    }

    /* 区间 [l,r] 最大异或，可带初值 x */
    T mx(int l, int r, T x = 0) const {
        LB tmp = sub(l, r);
        return tmp.mx(x);
    }

    /* 使用整条基求最大异或 */
    T mx(T x = 0) const {
        for (int k = K; k >= 0; --k)
            x = std::max(x, x ^ b[k]);
        return x;
    }

private:
    /* 在基 (b,p) 中插入 (v,pos) */
    static void ins(A& b, P& p, T v, int pos) {
        for (int k = K; k >= 0; --k) {
            if (!(v >> k & 1)) continue;
            if (!b[k]) {
                b[k] = v; p[k] = pos; return;
            }
            if (p[k] < pos) {
                std::swap(b[k], v);
                std::swap(p[k], pos);
            }
            v ^= b[k];
        }
    }
};
