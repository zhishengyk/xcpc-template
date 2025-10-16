/*
最后修改:
20251012
测试环境:
gcc11.2,c++11
clang12.0,C++11
msvc14.2,C++14
*/
#ifndef __OY_CHMINSEGTREE2D__
#define __OY_CHMINSEGTREE2D__

#include <cstdint>
#include <limits>

#include "VectorBufferWithoutCollect.h"

namespace OY {
    namespace RectChMin2D {
        using size_type = uint32_t;
        template <typename Tp, typename SizeType = uint64_t, template <typename> typename BufferType1 = VectorBufferWithoutCollect, template <typename> typename BufferType2 = VectorBufferWithoutCollect>
        struct Tree {
            using value_type = Tp;
            static value_type _minv(const value_type &x, const value_type &y) { return x < y ? x : y; }
            struct ColNode {
                value_type m_cap;
                size_type m_lc, m_rc;
            };
            struct RowNode {
                size_type m_id, m_lc, m_rc;
            };
            using col_buffer = BufferType1<ColNode>;
            using row_buffer = BufferType2<RowNode>;
            static constexpr value_type _inf() { return std::numeric_limits<value_type>::max(); }
            static ColNode *_col_ptr(size_type cur) { return col_buffer::data() + cur; }
            static RowNode *_row_ptr(size_type cur) { return row_buffer::data() + cur; }
            static void _reserve(size_type colnode_capacity, size_type rownode_capacity) {
                static_assert(col_buffer::is_vector_buffer && row_buffer::is_vector_buffer, "Only In Vector Mode");
                col_buffer::s_buf.reserve(colnode_capacity), row_buffer::s_buf.reserve(rownode_capacity);
            }
        private:
            size_type m_rt;
            SizeType m_row, m_column;
            static size_type _new_colnode() {
                size_type c = col_buffer::newnode();
                _col_ptr(c)->m_cap = _inf();
                _col_ptr(c)->m_lc = _col_ptr(c)->m_rc = 0;
                return c;
            }
            static size_type _new_rownode(SizeType, SizeType) {
                size_type c = row_buffer::newnode();
                _row_ptr(c)->m_id = _row_ptr(c)->m_lc = _row_ptr(c)->m_rc = 0;
                return c;
            }
            static size_type _ensure_lrow(size_type cur, SizeType row_floor, SizeType row_ceil, SizeType mid) {
                if (!_row_ptr(cur)->m_lc) _row_ptr(cur)->m_lc = _new_rownode(row_floor, mid);
                return _row_ptr(cur)->m_lc;
            }
            static size_type _ensure_rrow(size_type cur, SizeType row_floor, SizeType row_ceil, SizeType mid) {
                if (!_row_ptr(cur)->m_rc) _row_ptr(cur)->m_rc = _new_rownode(mid + 1, row_ceil);
                return _row_ptr(cur)->m_rc;
            }
            static void _col_chmin(size_type &cur, SizeType column_floor, SizeType column_ceil, SizeType column1, SizeType column2, const value_type &v) {
                if (!cur) cur = _new_colnode();
                if (column_floor == column1 && column_ceil == column2) {
                    _col_ptr(cur)->m_cap = _minv(_col_ptr(cur)->m_cap, v);
                } else {
                    SizeType mid = (column_floor + column_ceil) >> 1;
                    if (column2 <= mid)
                        _col_chmin(_col_ptr(cur)->m_lc, column_floor, mid, column1, column2, v);
                    else if (column1 > mid)
                        _col_chmin(_col_ptr(cur)->m_rc, mid + 1, column_ceil, column1, column2, v);
                    else
                        _col_chmin(_col_ptr(cur)->m_lc, column_floor, mid, column1, mid, v), _col_chmin(_col_ptr(cur)->m_rc, mid + 1, column_ceil, mid + 1, column2, v);
                }
            }
            static value_type _col_query(size_type cur, SizeType column_floor, SizeType column_ceil, SizeType j, value_type cap) {
                if (!cur) return cap;
                cap = _minv(cap, _col_ptr(cur)->m_cap);
                if (column_floor == column_ceil) return cap;
                SizeType mid = (column_floor + column_ceil) >> 1;
                return j <= mid ? _col_query(_col_ptr(cur)->m_lc, column_floor, mid, j, cap) : _col_query(_col_ptr(cur)->m_rc, mid + 1, column_ceil, j, cap);
            }
            void _row_chmin(size_type cur, SizeType row_floor, SizeType row_ceil, SizeType row1, SizeType row2, SizeType column1, SizeType column2, const value_type &v) {
                if (row_floor == row1 && row_ceil == row2) {
                    _col_chmin(_row_ptr(cur)->m_id, 0, m_column - 1, column1, column2, v);
                } else {
                    SizeType mid = (row_floor + row_ceil) >> 1;
                    if (row2 <= mid)
                        _row_chmin(_ensure_lrow(cur, row_floor, row_ceil, mid), row_floor, mid, row1, row2, column1, column2, v);
                    else if (row1 > mid)
                        _row_chmin(_ensure_rrow(cur, row_floor, row_ceil, mid), mid + 1, row_ceil, row1, row2, column1, column2, v);
                    else
                        _row_chmin(_ensure_lrow(cur, row_floor, row_ceil, mid), row_floor, mid, row1, mid, column1, column2, v), _row_chmin(_ensure_rrow(cur, row_floor, row_ceil, mid), mid + 1, row_ceil, mid + 1, row2, column1, column2, v);
                }
            }
            value_type _row_query(size_type cur, SizeType row_floor, SizeType row_ceil, SizeType i, SizeType j, value_type cap) const {
                if (!cur) return cap;
                cap = _col_query(_row_ptr(cur)->m_id, 0, m_column - 1, j, cap);
                if (row_floor == row_ceil) return cap;
                SizeType mid = (row_floor + row_ceil) >> 1;
                return i <= mid ? _row_query(_row_ptr(cur)->m_lc, row_floor, mid, i, j, cap) : _row_query(_row_ptr(cur)->m_rc, mid + 1, row_ceil, i, j, cap);
            }
        public:
            Tree() = default;
            Tree(SizeType row, SizeType column) { resize(row, column); }
            void resize(SizeType row, SizeType column) {
                m_row = row, m_column = column;
                m_rt = _new_rownode(0, m_row ? m_row - 1 : 0);
            }
            static void reserve(size_type colnode_capacity, size_type rownode_capacity) { _reserve(colnode_capacity, rownode_capacity); }
            SizeType row() const { return m_row; }
            SizeType column() const { return m_column; }
            void chmin(SizeType row1, SizeType row2, SizeType column1, SizeType column2, const value_type &v) { if (row1 <= row2 && column1 <= column2) _row_chmin(m_rt, 0, m_row - 1, row1, row2, column1, column2, v); }
            void chmin(SizeType row, SizeType column, const value_type &v) { chmin(row, row, column, column, v); }
            value_type cap(SizeType row, SizeType column) const { return _row_query(m_rt, 0, m_row - 1, row, column, _inf()); }
            value_type query(SizeType row, SizeType column) const { return cap(row, column); }
        };
        template <typename Tp, typename SizeType = uint64_t>
        using VectorChMinSeg2D = Tree<Tp, SizeType>;
    }
}

#endif


