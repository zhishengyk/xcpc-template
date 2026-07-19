template <int B>
struct xor_space {
    int cnt;
    i64 data[B];
    int time[B];
    constexpr xor_space() { reset(); }
    constexpr void reset() {
        cnt = 0;
        fill(data, data + B,  0);
        fill(time, time + B, -1);
    }
    bool add(i64 x, int t) {
        for (int i = B - 1; i >= 0 && x; i--) {
            if (!(x >> i & 1)) continue;
            if (!data[i]) return data[i] = x, time[i] = t, cnt++, true;
            if (time[i] < t) {
                swap(data[i], x);
                swap(time[i], t);
            }
            x ^= data[i];
        }
        return false;
    }
    i64 ask_max(i64 x = 0, int l = 0) {
        for (int i = B - 1; i >= 0; i--) {
            if (time[i] < l) continue;
            if (~x >> i & 1) x ^= data[i];
        }
        return x;
    }
    i64 ask_min(i64 x = 0, int l = 0) {
        for (int i = B - 1; i >= 0; i--) {
            if (time[i] < l) continue;
            if (x >> i & 1) x ^= data[i];
        }
        return x;
    }
    friend constexpr xor_space operator| (const xor_space& lhs, const xor_space& rhs) {
        xor_space res{lhs};
        for (int i = 0; i < B; i++)
            res.add(rhs.data[i], res.time[i]);
        return res;
    }
    friend constexpr xor_space operator& (const xor_space& lhs, const xor_space& rhs) {
        xor_space<B * 2> tmp;
        for (int i = 0; i < B; i++) {
            tmp.add((lhs.data[i] << B) | lhs.data[i], lhs.time[i]);
            tmp.add(rhs.data[i], rhs.time[i]);
        }
        xor_space res{};
        for (int i = 0; i < B; i++) {
            if (tmp.data[i]) {
                res.data[i] = tmp.data[i];
                res.time[i] = tmp.time[i];
                res.cnt++;
            }
        }
        return res;
    }
};