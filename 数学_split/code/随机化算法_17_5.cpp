static inline ll sq(ll v) { return v * v; }
// 计算两点平方距离
static inline ll dist2(const Point &a, const Point &b) {
    return sq(a.x - b.x) + sq(a.y - b.y);
}
void solve(std::vector<std::pair<int, int>> &p) {
    int n = p.size();
    // idx: 以 x 优先、y 次之排序后的点编号（用于按 x 分治的“切分边界”）
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (p[i].x != p[j].x) return p[i].x < p[j].x;
        return p[i].y < p[j].y; });

    // ord: 与 idx 同一集合，但每段在递归返回时保持按 y 升序
    std::vector<int> ord = idx;
    // 分治：在 [l, r) 这段（元素集合等于 idx[l..r)），返回最小平方距离；
    // 递归结束时，保证 ord[l..r) 按 y 升序，便于父层用 inplace_merge 合并
    std::function<ll(int, int)> dc = [&](int l, int r) -> ll {
        int mlen = r - l;
        if (mlen <= 25)
        { // 小块直接暴力 + 就地按 y 排序
            std::sort(ord.begin() + l, ord.begin() + r, [&](int i, int j) {
                if (p[i].y != p[j].y) return p[i].y < p[j].y;
                return p[i].x < p[j].x; });
            ll best = 9e18;
            for (int i = l; i < r; ++i)
                for (int j = i + 1; j < r; ++j) {
                    // 利用 y 排序做个小剪枝
                    ll dy = p[ord[j]].y - p[ord[i]].y;
                    if (dy * dy >= best)
                        break;
                    best = std::min(best, dist2(p[ord[i]], p[ord[j]]));
                }
            return best;
        }
        int m = (l + r) >> 1;
        // 中线 x（按 idx 的中点划分）
        ll midx = p[idx[m]].x;

        ll dl = dc(l, m);
        ll dr = dc(m, r);
        ll best = std::min(dl, dr);

        // 合并子段的“按 y 升序”到父段：用内置 inplace_merge
        std::inplace_merge(ord.begin() + l, ord.begin() + m, ord.begin() + r, [&](int i, int j) {
            if (p[i].y != p[j].y) return p[i].y < p[j].y;
            return p[i].x < p[j].x; });

        // 构建条带：ord[l..r) 已按 y 升序
        std::vector<int> strip;
        strip.reserve(r - l);
        for (int k = l; k < r; ++k) {
            int id = ord[k];
            if (sq(p[id].x - midx) < best) {
                // 只需与前面最多 7~8 个候选比
                for (int t = (int)strip.size() - 1, cnt = 0; t >= 0 && cnt < 8; --t, ++cnt) {
                    best = std::min(best, dist2(p[id], p[strip[t]]));
                }
                strip.push_back(id);
            }
        }
        return best;
    };
    return dc(0, n);
}