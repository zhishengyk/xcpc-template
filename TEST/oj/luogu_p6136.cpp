#include "DS/AVL.h"
#include "DS/FHQCounter.h"
#include "DS/GlobalHashBIT.h"
#include "DS/MonoAVL.h"
#include "DS/MonoSplay.h"
#include "DS/SegCounter.h"
#include "DS/Splay.h"
#include "DS/StaticBufferWrapWithCollect.h"
#include "DS/StaticBufferWrapWithoutCollect.h"
#include "IO/FastIO.h"

/*
[P6136 【模板】普通平衡树（数据加强版）](https://www.luogu.com.cn/problem/P6136)
*/
/**
 * 本题为 P3369 加强版
 * 为二叉平衡树模板题
 */

uint32_t buf[100000];
void solve_avl() {
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) cin >> buf[i];
    std::sort(buf, buf + n);
    using AVL = OY::AVLMultiset<uint32_t, std::less<uint32_t>, OY::StaticBufferWrapWithCollect<1100000>::type>;
    auto S = AVL::from_sorted(buf, buf + n);
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            S.insert_by_key(x ^ last);
        else if (op == '2')
            S.erase_by_key(x ^ last);
        else if (op == '3')
            last = S.rank(x ^ last) + 1;
        else if (op == '4')
            last = S.kth((x ^ last) - 1)->get();
        else if (op == '5')
            last = S.smaller_bound(x ^ last)->get();
        else
            last = S.upper_bound(x ^ last)->get();
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

void solve_splay() {
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) cin >> buf[i];
    std::sort(buf, buf + n);
    using Splay = OY::SplayMultiset<uint32_t, std::less<uint32_t>, OY::StaticBufferWrapWithCollect<1100000>::type>;
    auto S = Splay::from_sorted(buf, buf + n);
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            S.insert_by_key(x ^ last);
        else if (op == '2')
            S.erase_by_key(x ^ last);
        else if (op == '3')
            last = S.rank(x ^ last) + 1;
        else if (op == '4')
            last = S.kth((x ^ last) - 1)->get();
        else if (op == '5')
            last = S.smaller_bound(x ^ last)->get();
        else
            last = S.upper_bound(x ^ last)->get();
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

void solve_mono_avl() {
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) cin >> buf[i];
    std::sort(buf, buf + n);
    using Tree = OY::MonoAVLSequence<uint32_t, false, OY::StaticBufferWrapWithoutCollect<1100000>::type>;
    auto S = Tree::from_sorted(buf, buf + n);
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            S.insert_by_comparator(x ^ last);
        else if (op == '2')
            S.erase_by_comparator(x ^ last);
        else if (op == '3')
            last = S.lower_bound_by_comparator(x ^ last).m_rank + 1;
        else if (op == '4')
            last = S.query((x ^ last) - 1);
        else if (op == '5')
            last = S.query(S.lower_bound_by_comparator(x ^ last).m_rank - 1);
        else
            last = S.lower_bound_by_comparator((x ^ last) + 1).m_ptr->m_val;
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

void solve_mono_splay() {
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) cin >> buf[i];
    std::sort(buf, buf + n);
    using Tree = OY::MonoSplaySequence<uint32_t, false, OY::StaticBufferWrapWithoutCollect<1100000>::type>;
    auto S = Tree::from_sorted(buf, buf + n);
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            S.insert_by_comparator(x ^ last);
        else if (op == '2')
            S.erase_by_comparator(x ^ last);
        else if (op == '3')
            last = S.lower_bound_by_comparator(x ^ last).m_rank + 1;
        else if (op == '4')
            last = S.query((x ^ last) - 1);
        else if (op == '5')
            last = S.query(S.lower_bound_by_comparator(x ^ last).m_rank - 1);
        else
            last = S.lower_bound_by_comparator((x ^ last) + 1).m_ptr->m_val;
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

OY::GBIT::Tree<uint32_t, uint32_t, false, false, 11200007> Gbit(1 << 30);
void solve_hash_bit() {
    // 本方法无法通过测试点 2
    uint32_t n, m;
    cin >> n >> m;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x;
        cin >> x;
        Gbit.add(x, 1);
    }
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            Gbit.add(x ^ last, 1);
        else if (op == '2')
            Gbit.add(x ^ last, -1);
        else if (op == '3')
            last = Gbit.presum((x ^ last) - 1) + 1;
        else if (op == '4')
            last = Gbit.kth((x ^ last) - 1);
        else if (op == '5')
            last = Gbit.kth(Gbit.presum((x ^ last) - 1) - 1);
        else
            last = Gbit.kth(Gbit.presum(x ^ last));
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

void solve_counter() {
    uint32_t n, m;
    cin >> n >> m;
    OY::SEGCNT::Table<uint32_t, uint32_t, true, false, false, OY::StaticBufferWrapWithCollect<2200000>::type> S;
    // OY::FHQCNT::Table<uint32_t, uint32_t, true, false, OY::StaticBufferWrapWithCollect<1100000>::type> S;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x;
        cin >> x;
        S.add(x, 1);
    }
    uint32_t last = 0, sum = 0;
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t x;
        cin >> op >> x;
        if (op == '1')
            S.add(x ^ last, 1);
        else if (op == '2')
            S.add(x ^ last, -1);
        else if (op == '3')
            last = x != last ? S.presum((x ^ last) - 1) + 1 : 1;
        else if (op == '4')
            last = S.kth((x ^ last) - 1)->key();
        else if (op == '5')
            last = S.smaller_bound(x ^ last)->key();
        else
            last = S.upper_bound(x ^ last)->key();
        if (op >= '3') sum ^= last;
    }
    cout << sum;
}

int main() {
    solve_avl();
    // solve_splay();
    // solve_mono_avl();
    // solve_mono_splay();
    // solve_hash_bit();
    // solve_counter();
}