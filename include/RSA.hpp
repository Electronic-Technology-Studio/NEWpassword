//

#ifndef RSA_H
#define RSA_H
#include "include.h"
/*
RSA 类使用说明
概述
RSA 类实现了一个基本的 RSA 加密/解密机制。通过这个类，用户可以生成 RSA 密钥对，对字符串进行加密和解密，并查看公钥和私钥。

包含头文件
在使用 RSA 类之前，需要包含相应的头文件：

#include "RSA.hpp"

构造函数
RSA::RSA(const char* a);

参数：const char* a —— 需要加密的明文字符串。
作用：初始化 RSA 对象，生成密钥对，并准备明文数据。

公共方法
加密字符串

std::string RSA::to_miwen();
返回值：加密后的密文字符串。
作用：使用公钥对明文字符串进行加密。
解密字符串

std::string RSA::to_mingwen();
返回值：解密后的明文字符串。
作用：使用私钥对密文字符串进行解密。
更改字符串

void RSA::change(std::string new_mingwen);
参数：std::string new_mingwen —— 新的明文字符串。
作用：更新明文字符串并重新生成密文。
重置

void RSA::reset();
作用：重置 RSA 对象的所有成员变量，使其回到初始状态。
查看公钥

std::string RSA::showpublic();
返回值：公钥的字符串表示。
作用：返回当前的公钥。
查看私钥

std::string RSA::showprivate();
返回值：私钥的字符串表示。
作用：返回当前的私钥。
示例代码
以下是一个完整的示例代码，展示了如何使用 RSA 类进行字符串的加密和解密：

#include <iostream>
#include "RSA.hpp"

int main()
{
    // 原始明文字符串
    const char* original_message = "HELLO";

    // 创建 RSA 对象
    RSA rsa(original_message);

    // 输出原始明文
    std::cout << "原始明文: " << original_message << std::endl;

    // 加密字符串
    std::string encrypted_message = rsa.to_miwen();
    std::cout << "加密后的密文: " << encrypted_message << std::endl;

    // 解密字符串
    std::string decrypted_message = rsa.to_mingwen();
    std::cout << "解密后的明文: " << decrypted_message << std::endl;

    // 查看公钥
    std::string public_key = rsa.showpublic();
    std::cout << "公钥: " << public_key << std::endl;

    // 查看私钥
    std::string private_key = rsa.showprivate();
    std::cout << "私钥: " << private_key << std::endl;

    // 更改明文字符串
    rsa.change("WORLD");
    std::cout << "更改后的明文: " << "WORLD" << std::endl;

    // 重新加密和解密
    encrypted_message = rsa.to_miwen();
    std::cout << "加密后的密文: " << encrypted_message << std::endl;

    decrypted_message = rsa.to_mingwen();
    std::cout << "解密后的明文: " << decrypted_message << std::endl;

    // 重置 RSA 对象
    rsa.reset();
    if (rsa.mingwen == nullptr && rsa.miwen == nullptr) {
        std::cout << "对象已成功重置" << std::endl;
    } else {
        std::cout << "重置失败" << std::endl;
    }

    return 0;
}
注意事项
随机数生成：
RSA 类使用了安全的随机数生成器（如 std::random_device 和 std::mt19937），确保生成的密钥对是安全的。
内存管理：
RSA 类内部管理了动态分配的内存，确保在析构函数中释放内存，避免内存泄漏。
错误处理：
在生成私钥 d 时，如果找不到合适的 d，会抛出 std::runtime_error 异常。用户需要捕获并处理这种异常。
性能：
对于非常大的数（例如 2048 位或更高），模幂运算可能会较慢。可以考虑使用更高效的算法（如滑动窗口技术）来加速模幂运算。
*/
class RSA
{
    #if BUILD_VISION==BUILD
    public:
    #else
    private:
    #endif
        const int MAX = 2e4;
        int size;
        int* miwen; // 为加密后的数字密文
        char* mingwen; 
        size_t privatekey;
        size_t publickey;
        size_t n;

        // 判断两个数是否互为素数
        bool gcd(int, int);
        
        // 判断输入的数是否为素数
        bool sushu(int);
        
        // 求私钥d
        int siyao(int, int);
        
        // 随机生成与 t 互质的数 e
        int getrand(int, int);
        
        // 加密函数
        std::string jiami(int, int);
        
        // 解密函数
        std::string jiemi(int, int);
        
        // 生成随机奇数
        unsigned int ProduceRandomOdd();
        
        // 模重复平方算法求 (b^n) % m
        size_t repeatMod(size_t, size_t, size_t);
        
        // Miller-Rabin 素数检测
        bool rabinmiller(size_t, size_t);
    public:
        // 构造函数
        RSA(const char*);
        
        // 复制构造函数
        RSA(const RSA &);
        
        // 析构函数
        ~RSA();
        
        // 禁用默认构造函数
        RSA() = delete;

        // 加密字符串
        std::string to_miwen();

        // 解密字符串
        std::string to_mingwen();

        // 更改字符串
        void change(std::string);

        // 重置
        void reset();

        // 查看公钥
        std::string showpublic();

        // 查看私钥
        std::string showprivate();
};

// 构造函数
RSA::RSA(const char* a)
{
    mingwen = new char[strlen(a) + 1];
    strcpy(mingwen, a);

    const size_t k = 80; // 进行80轮测试
    unsigned int p, q;
    do {
        p = ProduceRandomOdd();
    } while (!rabinmiller(p, k));

    do {
        q = ProduceRandomOdd();
    } while (!rabinmiller(q, k));

    n = p * q;
    size_t phi_n = (p - 1) * (q - 1);
    publickey = getrand(p, q);
    privatekey = siyao(publickey, phi_n);

    size = strlen(mingwen);
    miwen = new int[size];
}

// 复制构造函数
RSA::RSA(const RSA & ptr)
{
    size = ptr.size;
    privatekey = ptr.privatekey;
    publickey = ptr.publickey;
    n = ptr.n;

    mingwen = new char[size + 1];
    strcpy(mingwen, ptr.mingwen);

    miwen = new int[size];
    for (int i = 0; i < size; ++i) {
        miwen[i] = ptr.miwen[i];
    }
}

// 析构函数
RSA::~RSA()
{
    delete[] mingwen;
    delete[] miwen;
}

// 判断两个数是否互为素数
bool RSA::gcd(int p, int q)
{
    while (q != 0) {
        int temp = q;
        q = p % q;
        p = temp;
    }
    return p == 1;
}

// 判断输入的数是否为素数
bool RSA::sushu(int s)
{
    if (s <= 1) return false;
    if (s <= 3) return true;
    if (s % 2 == 0 || s % 3 == 0) return false;
    for (int i = 5; i * i <= s; i += 6) {
        if (s % i == 0 || s % (i + 2) == 0) return false;
    }
    return true;
}

// 求私钥d
int RSA::siyao(int e, int t)  // t: 欧拉函数
{
    int d;
    for (d = 1; d < t; ++d) {
        if ((e * d) % t == 1) {
            return d;
        }
    }
    throw std::runtime_error("无法找到合适的私钥d");
}

// 随机生成与 t 互质的数 e
int RSA::getrand(int p, int q)
{
    int t = (p - 1) * (q - 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(2, t - 1);

    while (true) {
        int e = dis(gen);
        if (gcd(e, t) == 1) {
            return e;
        }
    }
}

// 加密函数
std::string RSA::jiami(int e, int n)
{
    int ming[size];
    for (int i = 0; i < size; ++i) {
        ming[i] = mingwen[i];
    }

    for (int i = 0; i < size; ++i) {
        miwen[i] = repeatMod(ming[i], e, n);
    }
    std::ostringstream oss;
    for (int i = 0; i < size; ++i) {
        oss << miwen[i] << " ";
    }
    return oss.str();
}

// 解密函数
std::string RSA::jiemi(int d, int n)
{
    int de_mingwen[size];
    char de_ming[size + 1];

    for (int i = 0; i < size; ++i) {
        de_mingwen[i] = repeatMod(miwen[i], d, n);
        de_ming[i] = static_cast<char>(de_mingwen[i]);
    }

    de_ming[size] = '\0';
    return std::string(de_ming);
}

// 生成随机奇数
unsigned int RSA::ProduceRandomOdd()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(100000000, MAX);

    unsigned int RandomNumber;
    do {
        RandomNumber = dis(gen);
    } while (RandomNumber % 2 == 0);

    return RandomNumber;
}

// 模重复平方算法求 (b^n) % m
size_t RSA::repeatMod(size_t base, size_t n, size_t mod)
{
    size_t a = 1;
    while (n) {
        if (n & 1) {
            a = (a * base) % mod;
        }
        base = (base * base) % mod;
        n >>= 1;
    }
    return a;
}

// Miller-Rabin 素数检测
bool RSA::rabinmiller(size_t n, size_t k)
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    int s = 0;
    size_t d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }

    for (size_t i = 0; i < k; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(2, n - 2);
        size_t a = dis(gen);
        size_t x = repeatMod(a, d, n);

        if (x == 1 || x == n - 1) continue;

        for (int j = 0; j < s - 1; ++j) {
            x = repeatMod(x, 2, n);
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}

// 加密字符串
std::string RSA::to_miwen()
{
    return jiami(publickey, n);
}

// 解密字符串
std::string RSA::to_mingwen()
{
    return jiemi(privatekey, n);
}

// 更改字符串
void RSA::change(std::string new_mingwen)
{
    delete[] mingwen;
    mingwen = new char[new_mingwen.length() + 1];
    strcpy(mingwen, new_mingwen.c_str());

    size = new_mingwen.length();
    delete[] miwen;
    miwen = new int[size];
    jiami(publickey, n); // 重新加密
}

// 重置
void RSA::reset()
{
    delete[] mingwen;
    delete[] miwen;

    mingwen = nullptr;
    miwen = nullptr;
    size = 0;
    privatekey = 0;
    publickey = 0;
    n = 0;
}

// 查看公钥
std::string RSA::showpublic()
{
    return std::to_string(publickey);
}

// 查看私钥
std::string RSA::showprivate()
{
    return std::to_string(privatekey);
}

#endif