//使用此模板前 需要让字符串的下标为1index  ！！
//使用此模板前 需要让字符串的下标为1index  ！！
//使用此模板前 需要让字符串的下标为1index  ！！
struct Hash {
    const int mod1 = 998244353, mod2 = 1e9 + 7;
    int b1 = 131, b2 = 233, n;
    vector<int> f1, f2, B1, B2;
    Hash(){}
    Hash(string s):n(s.length()), f1(n + 1), f2(n + 1), B1(n + 1), B2(n + 1) {
        B1[0] = B2[0] = 1;
        for(int i = 1; i <= n; i++) {
            B1[i] = B1[i - 1] * b1 % mod1;
            B2[i] = B2[i - 1] * b2 % mod2;
            f1[i] = (f1[i - 1] * b1 + s[i] - '0') % mod1;
            f2[i] = (f2[i - 1] * b2 + s[i] - '0') % mod2; 
        }
    }
    pair<int, int> get(int l, int r) {
        int a1 = ((f1[r] - f1[l - 1] * B1[r - l + 1]) % mod1 + mod1) % mod1;
        int a2 = ((f2[r] - f2[l - 1] * B2[r - l + 1]) % mod2 + mod2) % mod2;
        return {a1, a2};
    } 
};