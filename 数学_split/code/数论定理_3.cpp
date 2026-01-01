for (int i = 1; i <= N; ++i)//预处理[1,N]内所有数的所有因数 {
    for (int j = i; j <= N; j += i) {
        f[j].push_back(i);
    }
}