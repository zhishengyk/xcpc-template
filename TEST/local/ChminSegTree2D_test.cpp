#include "DS/ChminSegTree2D.h"
#include "IO/FastIO.h"

int main() {
    using Tree = OY::RectChMin2D::VectorChMinSeg2D<int>;
    Tree S(4, 5);

    // initialize whole grid cap to 100
    S.chmin(0, S.row() - 1, 0, S.column() - 1, 100);
    cout << "after chmin(all,100):\n";
    for (uint64_t i = 0; i < S.row(); i++) {
        for (uint64_t j = 0; j < S.column(); j++) cout << (j ? ' ' : '[') << S.cap(i, j) << (j + 1 == S.column() ? ']' : ',');
        cout << '\n';
    }

    // chmin rectangle [1..3] x [2..4] by 12
    S.chmin(1, 3, 2, 4, 12);
    cout << "after chmin(1..3,2..4,12):\n";
    for (uint64_t i = 0; i < S.row(); i++) {
        for (uint64_t j = 0; j < S.column(); j++) cout << (j ? ' ' : '[') << S.cap(i, j) << (j + 1 == S.column() ? ']' : ',');
        cout << '\n';
    }

    // chmin rectangle [0..2] x [0..1] by 3
    S.chmin(0, 2, 0, 1, 3);
    cout << "after chmin(0..2,0..1,3):\n";
    for (uint64_t i = 0; i < S.row(); i++) {
        for (uint64_t j = 0; j < S.column(); j++) cout << (j ? ' ' : '[') << S.cap(i, j) << (j + 1 == S.column() ? ']' : ',');
        cout << '\n';
    }

    return 0;
}


