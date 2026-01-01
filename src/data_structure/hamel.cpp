template <int B>
struct xor_space {
    int cnt;
    i64 data[B];
    constexpr xor_space() { reset(); }
    constexpr void reset() {
        cnt = zro = 0;
        fill(data, data + B, 0);
    }
    void rebuild() {
        for (int i = B - 1; i >= 0; i--) {
            if (!data[i]) continue;
            for (int j = i - 1; j >= 0; j--)
                if (data[i] >> j & 1) data[i] ^= data[j];
        }
    }
    bool add(i64 x) {
        for (int i = B - 1; i >= 0 && x; i--) {
            if (~x >> i & 1) continue;
            if (!data[i]) return data[i] = x, cnt++, true;
            x ^= data[i];
        }
        return false;
    }
    i64 ask_max(i64 x = 0) {
        for (int i = B - 1; i >= 0; i--)
            if (~x >> i & 1) x ^= data[i];
        return x;
    }
    i64 ask_min(i64 x = 0) {
        for (int i = B - 1; i >= 0; i--)
            if (x >> i & 1) x ^= data[i];
        return x;
    }
    i64 ask_kth(i64 k = 0) {
        if (k <= 0 || k >= (1ULL << cnt)) return -1;
        i64 res = 0;
        for (int i = 0; i < B; i++) {
            if (!data[i]) continue;
            if (k & 1) res ^= data[i];
            k >>= 1;
        }
        return res;
    }
    i64 aks_rnk(i64 x = 0) {
        i64 res = 0;
        i64 k = 1;
        for (int i = 0; i < B; i++) {
            if (!data[i]) continue;
            if (x >> i & 1) res |= k;
            k <<= 1;
        }
        return res;
    }
    friend constexpr xor_space operator|(const xor_space &lhs, const xor_space &rhs) {
        xor_space res{lhs};
        for (int i = 0; i < B; i++)
            res.add(rhs.data[i]);
        return res;
    }
    friend constexpr xor_space operator&(const xor_space &lhs, const xor_space &rhs) {
        xor_space<B * 2> tmp;
        for (int i = 0; i < B; i++) {
            tmp.add((lhs.data[i] << B) | lhs.data[i]);
            tmp.add(rhs.data[i] << B);
        }
        xor_space res{};
        for (int i = 0; i < B; i++)
            if (tmp.data[i]) res.data[i] = tmp.data[i], res.cnt++;
        return res;
    }
};




