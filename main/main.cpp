//电子科技工作室2024-2030©版权所有
//NEWpassword命令行版本主文件
#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )

#include "../include/PasswordManager.hpp"
#include "../include/RSA.hpp"
#include "../include/sha256.hpp"
#include "../include/text.h"

using namespace std;

int main() 
{
    init();
#if BUILD_VISION==BUILD
    info("DEBUG", "程序正在启动...");

    hash_context ctx;

    uint8_t hash[32]; // SHA-256 输出长度为 32 字节
    clock_t start, end;

    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(NULL)));
    //printf("1");
    uint8_t* data = (uint8_t*)malloc(DATA_SIZE); // 分配数据缓冲区

    // 生成随机数据填充到 data 数组中
    for (unsigned long long i = 0; i < DATA_SIZE; i++) // 使用 unsigned long long
    {
        data[i] = rand() & 0xFF;
    }
    //printf("2");
    // 开始计时
    start = clock();
    for (unsigned long long i = 0; i < ROUNDS; i++) // 使用 unsigned long long
    {
       // printf("%d",i+3);
        hash_start(&ctx);
        hash_update(&ctx, data, DATA_SIZE);
        hash_finish(&ctx, hash);
    }
    // 结束计时
    //printf("114514\n");
    end = clock();

    // 释放分配的内存
    free(data);

    // 计算总运行时间和每秒处理的数据量
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    double computing_speed = (static_cast<double>(DATA_SIZE * ROUNDS * (unsigned long long)8 / 1000) / 1000) / time;
    //这里要改成info（）的，但没时间了，下次记得改
    printf("运行时间： %f seconds\n", time);
    printf("运算速度: %f Mbps\n", computing_speed);
    cout << endl << endl;
    return 200;
#else

    PasswordManager pm;
    int choice;

    while (true) {
        cout << "1. 添加第三方账号密码\n";
        cout << "2. 删除第三方账号密码\n";
        cout << "3. 查找第三方账号密码\n";
        cout << "4. 修改第三方账号密码\n";
        cout << "5. 修改管理器密码\n";
        cout << "6. 显示所有弱密码\n";
        cout << "7. 显示重复密码\n";
        cout << "0. 退出\n";
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
        case 1: pm.addAccount(); break;
        case 2: pm.deleteAccount(); break;
        case 3: pm.findAccount(); break;
        case 4: pm.modifyAccount(); break;
        case 5: pm.changeMasterPassword(); break;
        case 6: pm.showWeakPasswords(); break;
        case 7: pm.showDuplicatePasswords(); break;
        case 0: return 0;
        default: cout << "无效选项。" << endl; break;
        }
    }
    return 0;
#endif
}
void error_out()
{
    exit(-114);
}