#include "../include/PasswordManager.hpp"
#include "../include/RSA.hpp"
using namespace std;

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
/*
int main() {
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
            case 8: pm.showDuplicatePasswords(); break;
            case 0: return 0;
            default: cout << "无效选项。" << endl; break;
        }
    }
}
*/