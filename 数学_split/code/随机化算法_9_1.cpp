sg[0] = 0; // 0是输 1是赢 初值根据题目变化
sg[1] = 1;
for (int i = 2; i <= N; i++) {
    std::set<int> mex;
    int s = 0;
    for (int j = 1; j < i; j++) {
        if (满足条件) { // 说明 i能到i-j
            mex.insert(sg[i - j]);
        }
    }
    while (mex.count(s)) {
        s++;
    }
    sg[i] = s;
}
for (int i = 1; i <= N; i += 1) {
    cout << "sg " << i << ": " << sg(i) << "\n";
}