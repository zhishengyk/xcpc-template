#include "DS/AVL.h"
#include "DS/Splay.h"
#include "DS/GlobalHashMap.h"
#include "DS/StaticBufferWrapWithCollect.h"
#include "IO/FastIO.h"

/*
[P3879 [TJOI2010] 阅读理解](https://www.luogu.com.cn/problem/P3879)
*/
// 显然，本题为哈希模板题
// 然而，文本字符串过多，很容易爆空间
// 不如把查询的字符串插入哈希表，然后扫描文本字符串

using AVL = OY::SplayMultiset<uint32_t, std::less<uint32_t>, OY::StaticBufferWrapWithCollect<10000000>::type>;
// using AVL = OY::AVLMultiset<uint32_t, std::less<uint32_t>, OY::StaticBufferWrapWithCollect<10000000>::type>;
OY::GHASH::UnorderedMap<std::string, AVL, false, 1 << 16> GS;
void solve_hash() {
    uint32_t n;
    cin >> n;
    std::vector<std::string> contents[n];
    for (uint32_t i = 0; i < n; i++) {
        uint32_t k;
        cin >> k;
        contents[i].resize(k);
        for (auto &s : contents[i]) cin >> s;
    }

    uint32_t m;
    cin >> m;
    std::vector<decltype(GS)::node *> pos(m);
    for (uint32_t i = 0; i < m; i++) {
        std::string s;
        cin >> s;
        pos[i] = GS.insert(s).m_ptr;
    }
    for (uint32_t i = 0; i < n; i++)
        for (auto &s : contents[i]) {
            auto ptr = GS.find(s);
            if (ptr) {
                ptr->m_mapped.modify_or_insert(i, [](auto...) {});
            }
        }
    for (auto e : pos) {
        e->m_mapped.do_for_each([](auto p) { cout << p->get() + 1 << ' '; });
        cout << endl;
    }
}

int main() {
    solve_hash();
}