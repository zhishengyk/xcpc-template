std::vector<std::pair<ll, ll>> floorBlock(ll n, ll m)
 // n/i i从1到m的整除分块区间 {
    std::vector<std::pair<ll, ll>> res;
    for (ll l = 1, r; l <= std::min(n, m); l = r + 1) {
        r = std::min(n / (n / l), std::min(n, m));
        res.emplace_back(l, r);
    }
    return res;
}