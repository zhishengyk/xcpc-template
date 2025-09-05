#include "DS/SegmentBeat.h"
#include "IO/FastIO.h"

/*
[P6242 【模板】线段树 3](https://www.luogu.com.cn/problem/P6242)
*/
/**
 * 模板里已经有能区间最小化、区间加的结点
 * 现在要给这个结点添加一个记录历史最大值的功能，要点就是记录某个结点最近的最大值以及最近的最大加值
 * 【最近：指的是自从上一次 pushdown 到现在的这一段时间】
 * map(Chmin, ...) 这个直接继承就行，因为不会影响到历史最大值
 * map(Add, ...) 这个在继承之后简单修改一下历史最大值、最近最大值、最近最大加值
 * pushup 这个在继承之后简单维护一下历史最大值
 * pushdown 是最烧脑的。必须要想明白一件事：在 pushdown 中发生的修改，一定是能快速修改的修改
 *      自从上一次 pushdown 以来，当前结点所受的修改一定分为两类：
 *      第一类是最大值，接受 Chmin 类型修改；
 *      第二类是最大值、次大值以及更小的值，接受 Add 类型修改。
 *      不可能有次大值以及更小的值接受 Chmin 类型修改的情况，因为这个属于不能快速修改的修改。
 *      m_recent_max 记录着最大值的变化信息；m_recent_max_inc 记录着次大值以及更小的值的变化信息；
 *      能分析到这里，就可以写出合理的 pushdown 了。 
*/

// 为了方便后人使用，我就不继承了，直接重新写一个结点
template <typename ValueType, typename CountType, typename SumType>
struct ChminHistoryNode {
    static constexpr ValueType min = std::numeric_limits<ValueType>::min() / 2;
    using node_type = ChminHistoryNode<ValueType, CountType, SumType>;
    struct Chmin {
        ValueType m_chmin_by;
    };
    struct Add {
        ValueType m_add_by;
    };
    struct MaxGetter {
        using value_type = ValueType;
        value_type operator()(node_type *x) const { return x->m_max1; }
        value_type operator()(value_type x, value_type y) const { return std::max(x, y); }
    };
    struct SumGetter {
        using value_type = SumType;
        value_type operator()(node_type *x) const { return x->m_sum; }
        value_type operator()(value_type x, value_type y) const { return x + y; }
    };
    struct HistoryMaxGetter {
        using value_type = ValueType;
        value_type operator()(node_type *x) const { return x->m_history_max; }
        value_type operator()(value_type x, value_type y) const { return std::max(x, y); }
    };
    static bool map(const Chmin &chmin, node_type *x, CountType len) {
        if (x->m_max1 <= chmin.m_chmin_by) return true;
        if (x->m_max2 < chmin.m_chmin_by) return x->chmin_by(chmin.m_chmin_by), true;
        return false;
    }
    static bool map(const Add &inc, node_type *x, CountType len) {
        x->add_by(inc.m_add_by, len);
        x->m_history_max = std::max(x->m_history_max, x->m_max1);
        x->m_recent_max = std::max(x->m_recent_max, x->m_max1);
        x->m_recent_max_inc = std::max(x->m_recent_max_inc, x->m_inc);
        return true;
    }
    ValueType m_max1, m_max2, m_inc, m_history_max, m_recent_max, m_recent_max_inc;
    CountType m_max_cnt;
    SumType m_sum;
    void set(ValueType val) { m_sum = m_max1 = m_history_max = m_recent_max = val, m_max2 = min, m_max_cnt = 1; }
    const ValueType &get() const { return m_max1; }
    void add_by(ValueType inc, CountType len) {
        m_sum += SumType(inc) * len, m_max1 += inc, m_inc += inc;
        if (m_max2 != min) m_max2 += inc;
    }
    void chmin_by(ValueType val) { m_sum += SumType(val - m_max1) * m_max_cnt, m_max1 = val; }
    void pushup(node_type *lchild, node_type *rchild) {
        m_sum = lchild->m_sum + rchild->m_sum;
        if (lchild->m_max1 == rchild->m_max1) {
            m_max1 = lchild->m_max1;
            m_max2 = std::max(lchild->m_max2, rchild->m_max2);
            m_max_cnt = lchild->m_max_cnt + rchild->m_max_cnt;
        } else if (lchild->m_max1 > rchild->m_max1) {
            m_max1 = lchild->m_max1;
            m_max_cnt = lchild->m_max_cnt;
            m_max2 = std::max(lchild->m_max2, rchild->m_max1);
        } else {
            m_max1 = rchild->m_max1;
            m_max_cnt = rchild->m_max_cnt;
            m_max2 = std::max(lchild->m_max1, rchild->m_max2);
        }
        m_recent_max = m_max1, m_recent_max_inc = 0, m_history_max = std::max(lchild->m_history_max, rchild->m_history_max);
    }
    void pushdown(node_type *lchild, node_type *rchild, CountType len) {
        if (m_recent_max_inc) {
            lchild->m_recent_max = std::max(lchild->m_recent_max, std::min(lchild->m_max1 + m_recent_max_inc, m_recent_max));
            lchild->m_history_max = std::max(lchild->m_history_max, lchild->m_recent_max);
            lchild->m_recent_max_inc = std::max(lchild->m_recent_max_inc, lchild->m_inc + m_recent_max_inc);
            rchild->m_recent_max = std::max(rchild->m_recent_max, std::min(rchild->m_max1 + m_recent_max_inc, m_recent_max));
            rchild->m_history_max = std::max(rchild->m_history_max, rchild->m_recent_max);
            rchild->m_recent_max_inc = std::max(rchild->m_recent_max_inc, rchild->m_inc + m_recent_max_inc);
        }
        m_recent_max = m_max1, m_recent_max_inc = 0;
        if (m_inc) lchild->add_by(m_inc, len >> 1), rchild->add_by(m_inc, len >> 1), m_inc = 0;
        if (m_max1 < lchild->m_max1) lchild->chmin_by(m_max1);
        if (m_max1 < rchild->m_max1) rchild->chmin_by(m_max1);
    }
};

using Tree = OY::SegBeat::Tree<ChminHistoryNode<int, int, int64_t>>;
using node = Tree::node;
int main() {
    uint32_t n, m;
    cin >> n >> m;
    auto read = [](auto...) {
        int32_t x;
        cin >> x;
        return x;
    };
    Tree S(n, read);
    for (uint32_t i = 0; i < m; i++) {
        char op;
        uint32_t l, r;
        cin >> op >> l >> r;
        if (op == '1') {
            int x;
            cin >> x;
            S.add(l - 1, r - 1, node::Add{x});
        } else if (op == '2') {
            int x;
            cin >> x;
            S.add(l - 1, r - 1, node::Chmin{x});
        } else if (op == '3')
            cout << S.query<node::SumGetter>(l - 1, r - 1) << endl;
        else if (op == '4')
            cout << S.query<node::MaxGetter>(l - 1, r - 1) << endl;
        else
            cout << S.query<node::HistoryMaxGetter>(l - 1, r - 1) << endl;
    }
}
