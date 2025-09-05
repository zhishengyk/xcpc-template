#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;
// bitset 的大小必须是一个编译时常量
const int MAXN = 1000000500; // 例如，筛选到 1 亿

// is_prime[i] = 1 表示 i 是质数, 0 表示不是
std::bitset<MAXN + 1> is_prime;
// int is_prime[MAXN];
std::vector<int> primes; // 用来存储找到的质数

/**
 * @brief 使用 bitset 优化的埃氏筛
 * @param n 筛选的上限（不能超过 MAXN）
 */
 int cnt = 0;
void sieve_with_bitset(int n) {
    
    // // 2. 标记已知非质数
    // is_prime[0] = is_prime[1] = 0;

    // // 3. 标记所有大于 2 的偶数为非质数
    // // (这一步可以省略，但逻辑更清晰)
    for (int i = 4; i <= n; i += 2) {
        is_prime[i] = 1;
    }

    // 4. 遍历奇数，进行筛选
    // 任何合数的最小质因子一定不大于 sqrt(n)
    for (int p = 3; p <= n/p; p += 2) {
        // 如果 p 是一个质数
        if (!is_prime[p]) {
           
            // 那么 p 的所有奇数倍都不是质数
            // 从 p*p 开始标记，因为小于 p*p 的合数已经被更小的质因子筛掉了
            for (int i = p*p; i <= n; i += 2*p) {
                is_prime[i] = 1;
            }
        }
    }
}


int main() {
    int limit = 1e9; 
    
    sieve_with_bitset(limit);
    
    

    return 0;
}