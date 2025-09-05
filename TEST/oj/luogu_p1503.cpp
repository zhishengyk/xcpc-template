#include "DS/ChthollySegTree.h"
#include "DS/ChthollyZkwTree.h"
#include "DS/DynamicBitset.h"
#include "DS/LazyBitset.h"
#include "DS/MonoAVL.h"
#include "DS/MonoSplay.h"
#include "DS/RangeManager.h"
#include "DS/ZkwBitset.h"
#include "IO/FastIO.h"

/*
[P1503 鬼子进村](https://www.luogu.com.cn/problem/P1503)
*/
/**
 * 显然，本题为位集模板题，用位集模拟 set
 * 也可以用平衡树模拟 set
 */

void solve_avl() {
    uint32_t n, m;
    cin >> n >> m;
    using Tree = OY::MonoAVLSequence<uint32_t, false>; // 45ms
    // using Tree = OY::MonoSplaySequence<uint32_t, false>; // 48ms
    Tree::_reserve(m + 1);
    Tree S;
    S.insert(0, n + 1);
    std::vector<uint32_t> stack;
    for (uint32_t i = 0; i != m; i++) {
        char op;
        cin >> op;
        if (op == 'D') {
            uint32_t x;
            cin >> x;
            stack.push_back(x);
            S.insert_by_comparator(x);
        } else if (op == 'R') {
            S.erase_by_comparator(stack.back());
            stack.pop_back();
        } else {
            uint32_t x;
            cin >> x;
            auto lb = S.lower_bound_by_comparator(x);
            if (lb.m_ptr->m_val == x)
                cout << "0\n";
            else {
                uint32_t pre = lb.m_rank ? S.query(lb.m_rank - 1) : 0;
                cout << lb.m_ptr->m_val - pre - 1 << endl;
            }
        }
    }
}

void solve_czkw() {
    uint32_t n, m;
    cin >> n >> m;
    OY::ChthollyZkwTree<bool> S(n, true); // 56ms
    // OY::VectorChthollySegTree<bool, uint32_t> S(n, true); // 84ms
    std::vector<uint32_t> stack;
    for (uint32_t i = 0; i != m; i++) {
        char op;
        cin >> op;
        if (op == 'D') {
            uint32_t x;
            cin >> x;
            stack.push_back(x - 1);
            S.modify(x - 1, false);
        } else if (op == 'R') {
            S.modify(stack.back(), true);
            stack.pop_back();
        } else {
            uint32_t x;
            cin >> x;
            auto [l, r] = S.belong(x - 1);
            if (!S.query(l))
                cout << "0\n";
            else
                cout << r - l + 1 << endl;
        }
    }
}

void solve_rm() {
    uint32_t n, m;
    cin >> n >> m;
    OY::RangeManager<uint32_t> rm; // 47ms
    rm.add_range({1, n});
    std::vector<uint32_t> stack;
    for (uint32_t i = 0; i != m; i++) {
        char op;
        cin >> op;
        if (op == 'D') {
            uint32_t x;
            cin >> x;
            stack.push_back(x);
            rm.remove_range({x, x});
        } else if (op == 'R') {
            rm.add_range({stack.back(), stack.back()});
            stack.pop_back();
        } else {
            uint32_t x;
            cin >> x;
            auto it = rm.any_of({x, x});
            if (it == rm.end())
                cout << "0\n";
            else
                cout << it->second - it->first + 1 << endl;
        }
    }
}

void solve_bitset() {
    uint32_t n, m;
    cin >> n >> m;
    OY::ZkwTreeBitset<false> B(n); // 61ms
    // OY::VectorLazyBitset<uint32_t, false> B(n); // 63ms
    // OY::DynamicBitset B(n); // 84ms
    B.set();
    std::vector<uint32_t> stack;
    for (uint32_t i = 0; i != m; i++) {
        char op;
        cin >> op;
        if (op == 'D') {
            uint32_t x;
            cin >> x;
            stack.push_back(--x);
            B.reset(x);
        } else if (op == 'R') {
            B.set(stack.back());
            stack.pop_back();
        } else {
            uint32_t x;
            cin >> x;
            if (!B[--x])
                cout << "0\n";
            else {
                uint32_t pre = B.prev_zero(x);
                uint32_t nxt = B.next_zero(x);
                cout << (~nxt ? nxt : n) - pre - 1 << endl;
            }
        }
    }
}

int main() {
    solve_avl();
    // solve_czkw();
    // solve_bitset();
    // solve_rm();
}