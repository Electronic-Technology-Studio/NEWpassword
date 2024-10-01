#ifndef RSA_H
#define RSA_H
#include "include.h"

// 拓展欧几里得算法
int exgcd(int a, int b, int& x, int& y) {
    int x0 = 1, y0 = 0;
    int x1 = 0, y1 = 1;
    int q, r, t;

    while (b != 0) {
        q = a / b;
        r = a % b;
        a = b;
        b = r;

        t = x0 - q * x1;
        x0 = x1;
        x1 = t;

        t = y0 - q * y1;
        y0 = y1;
        y1 = t;
    }

    x = x0;
    y = y0;
    return a; // 返回最大公约数
}
/*
一个数能整除另一个数，那么必能整除另一个数的因数
一个数不能整除另一个数，那么必不能整除另一个数的倍数

从5开始，6n、6n+1、6n+2、6n+3、6n+4、6n+5中，6n、6n+2、6n+3、6n+4都可以整除2，则这些数不是素数；
只需判断剩下的6n+1、6n+5（即6m-1、6m+1，6m两侧的数）是不是素数即可；
6n+1、6n+5不能整除2，则这些数不能整除2i（即6i、6i+2、6i+3、6i+4），
所以只需进一步判断能否整除6i+1、6i+5（不包括1，从5开始；即5+6i、5+6i+2）即可（循环的步长变为6）
*/
// 预先计算的300以内的所有质数
std::vector<int> smallPrimes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
    251, 257, 263, 269, 271, 277, 281, 283, 293
};

bool isprime1(int num) {
    if (num < 2) return false;
    // 检查是否在预处理的小质数列表中
    for (int p : smallPrimes) {
        if (p * p > num) break;
        if (num % p == 0) return false;
    }
    // 对于大于31的数，使用6k±1的方法
    int tmp = sqrt(num);
    for (int i = 35; i <= tmp; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// 快速幂取模
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;  // 确保 base 小于 mod

    while (exp > 0) {
        if (exp & 1) {  // 如果 exp 是奇数
            result = (result * base) % mod;
        }
        exp >>= 1;  // exp = exp >> 1
        base = (base * base) % mod;
    }
    return result;
}

// Miller-Rabin 素性测试
bool isprime2(long long n, int k = 5) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    // 写成 n-1 = 2^r * d 的形式
    long long r = 0;
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // 进行 k 轮测试
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = modExp(a, d, n);
        if (x == 1 || x == n - 1) continue;

        for (int j = 0; j < r - 1; j++) {
            x = modExp(x, 2, n);
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}
inline bool isprime(int a)
{
    if (a > 2000)
    {
        return isprime2(a,a/500+3);
    }
    else
    {
        return isprime1(a);
    }
}
void primegenerator(int prime[10])                             //生成素数表
{
    int i, j = 0;
    for (i = 91; i <= 1000; i++) {
        if (isprime(i) == 0) {
            prime[j] = i;
            j++;
        }
        if (j > 9)break;
    }
}

#endif