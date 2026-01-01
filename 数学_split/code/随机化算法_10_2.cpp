    std::map<std::pair<int, int>, int> mp;
    mp[{0, 0}] = 1; // 赋初值
    mp[{0, 1}] = 1;
    mp[{1, 0}] = 1;
    mp[{1, 1}] = 1;
    auto check = [&](auto check, int x, int y) -> int {
        if (mp[{x, y}]) {
            return mp[{x, y}];
        }
        for (int i = 1; i <= x / 2; ++i) {
            if (check(check, x - 2 * i, y + i) == 1) {
                mp[{x, y}] = 2;
                return 2;
            } // 前继状态
        }
        for (int i = 1; i <= y / 2; ++i) {
            if (check(check, x + i, y - 2 * i) == 1) {
                mp[{x, y}] = 2;
                return 2;
            } // 前继
        }
        mp[{x, y}] = 1;
        return 1;
    };