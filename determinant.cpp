#pragma once

#include <vector>
#include <utility>

template <typename T>
T determinant(std::vector<std::vector<T>> a, const T& MOD) {
    int n = a.size();
    if (n == 0) return 1;

    T res = 1;
    long long w = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[i][i] != 0) {
                long long div = a[j][i] / a[i][i];
                for (int k = i; k < n; k++) {
                    a[j][k] = (a[j][k] - div * a[i][k] % MOD + MOD) % MOD;
                }
                std::swap(a[i], a[j]);
                w = -w;
            }
            std::swap(a[i], a[j]);
            w = -w;
        }
    }

    for (int i = 0; i < n; i++) {
        res = (long long)res * a[i][i] % MOD;
    }

    res = (long long)res * w % MOD;
    return (res + MOD) % MOD;
}