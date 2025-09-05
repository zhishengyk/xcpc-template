#include "DS/DynamicBitset.h"
#include "DS/LazyBitset.h"
#include "DS/ZkwBitset.h"
#include "IO/LeetcodeIO.h"
using namespace std;

/*
[2166. 设计位集](https://leetcode.cn/problems/design-bitset/)
*/
/**
 * 本题为 Bitset 模板题
 */

using MyBitset = OY::LazyBitset::Tree<uint32_t, false>; // 155ms
auto global_init = [] {
    OY::LazyBitset::Tree<uint32_t, false>::_reserve(200000);
    return 0;
}();
// using MyBitset = OY::ZkwTreeBitset<false>;//203ms
// using MyBitset = OY::DynamicBitset; // 586ms
class Bitset {
    MyBitset m_table;

public:
    Bitset(int size) : m_table(size) {}
    void fix(int idx) { m_table.set(idx); }
    void unfix(int idx) { m_table.reset(idx); }
    void flip() { m_table.flip(); }
    bool all() { return m_table.all(); }
    bool one() { return m_table.any(); }
    int count() { return m_table.count(); }
    string toString() {
        string s;
        for (int i = 0; i < m_table.size(); i++) s += '0' + m_table[i];
        return s;
    }
};

#ifdef OY_LOCAL
int main() {
    REGISTER_CONSTRUCTOR_CLASS(Bitset, int);
    REGISTER_MEMBERFUNCTION_CLASS(Bitset, fix, unfix, flip, all, one, count, toString);

    while (true) {
        executor.constructClass();
        while (executor) {
            executor.executeClass();
        }
    }
}
#endif