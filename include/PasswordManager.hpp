#ifndef PASSWORD_MANGAGER_HPP
#define PASSWORD_MANGAGER_HPP
#include "include.h"

// 数据结构
struct Account {
    int id=0;
    string platform;
    string username;
    string password;
};

// 密码管理器
class PasswordManager {
private:
    string masterPassword;
    vector<Account> accounts;
    const string dataFileName = "data.txt";
    const string passwordFileName = "password.dat";
    const int maxAttempts = 3;

    // 密码安全性检查
    char checkPasswordStrength(const string& password) {
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        for (char ch : password) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else hasSpecial = true;
        }

        int score = (hasUpper ? 1 : 0) + (hasLower ? 1 : 0) + (hasDigit ? 1 : 0) + (hasSpecial ? 1 : 0);
        if (score < 2) return 0;
        if (score == 2) return 1;
        return 2;
    }

    // 计算密码破解时间
    double calculateCrackTime(const string& password) {
        // 假设每秒破解4000000000个密码
        double possibilities = 1;
        for (char ch : password) {
            if (isdigit(ch) || isalpha(ch)) possibilities *= 62;  // 数字 + 大小写字母
            else possibilities *= 95;  // 包含特殊符号
        }
        return possibilities / 4000000000.0;
    }

    // 保存管理器密码到文件
    void saveMasterPassword() const {
        ofstream file(passwordFileName);
        if (file.is_open()) {
            file << masterPassword << endl;
            file.close();
        }
    }

    // 从文件加载管理器密码
    void loadMasterPassword() {
        ifstream file(passwordFileName);
        if (file.is_open()) {
            getline(file, masterPassword);
            file.close();
        }
    }

    // 检查密码是否匹配
    bool verifyPassword(const string& password) const {
        return password == masterPassword;
    }

    // 保存数据到文件
    void saveData() {
        ofstream file(dataFileName);
        if (file.is_open()) {
            for (const auto& acc : accounts) {
                file << acc.id << " " << acc.platform << " " << acc.username << " " << acc.password << endl;
            }
            file.close();
        }
    }

    // 显示所有弱密码
    void displayWeakPasswords() {
        for (const auto& acc : accounts) {
            if (checkPasswordStrength(acc.password) == 0) {
                cout << "ID: " << acc.id << ", 平台: " << acc.platform
                     << ", 账号: " << acc.username << ", 密码: " << acc.password << " (弱)" << endl;
            }
        }
    }

    // 显示重复的密码
    void displayDuplicatePasswords() {
        map<string, vector<Account>> platformAccounts;
        for (const auto& acc : accounts) {
            platformAccounts[acc.platform].push_back(acc);
        }

        for (const auto& pair : platformAccounts) {
            const auto& accList = pair.second;
            if (accList.size() > 1) {
                cout << "平台: " << pair.first << endl;
                for (const auto& acc : accList) {
                    cout << "ID: " << acc.id << ", 账号: " << acc.username << ", 密码: " << acc.password << endl;
                }
                cout << "-----------------------------" << endl;
            }
        }
    }

public:
    PasswordManager() {
        // 检查是否需要创建管理器密码
        loadMasterPassword();
        if (masterPassword.empty()) {
            cout << "首次启动，请设置管理器密码: ";
            cin >> masterPassword;
            saveMasterPassword();
        }
        else {
            // 校验管理器密码
            int attempts = 0;
            string password;
            while (attempts < maxAttempts) {
                cout << "press the key";
                cin >> password;
                if (verifyPassword(password)) {
                    break;
                } else {
                    cout << "密码错误" << endl;
                    attempts++;
                }
            }
            if (attempts == maxAttempts) {
                cout << "you warn" << endl;
                exit(1);
            }
        }

        // 从文件加载数据
        ifstream file(dataFileName);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                Account acc;
                istringstream iss(line);
                iss >> acc.id >> acc.platform >> acc.username >> acc.password;
                accounts.push_back(acc);
            }
            file.close();
        }
    }

    // 添加第三方账号密码数据
    void addAccount() {
        Account acc;
        cout << "输入ID(按0选择顺序ID): ";
        cin >> acc.id;
        if(acc.id==0)
        {
            
        }
        // 检查ID是否重复
        for (const auto& a : accounts) {
            if (a.id == acc.id) {
                cout << "ID " << acc.id <<"is not yes,请使用其他ID." << endl;
                ;
                return;
            }
        }

        cout << "输入平台: ";
        cin >> acc.platform;
        cout << "输入账号: ";
        cin >> acc.username;
        cout << "输入密码: ";
        cin >> acc.password;

        char strength = checkPasswordStrength(acc.password);
        double crackTime = calculateCrackTime(acc.password);

        cout << "密码强度: " << strength << endl;
        cout << "估计破解time:" << fixed << setprecision(2) << crackTime << " sec." << endl;
        ;
        accounts.push_back(acc);
        saveData();
    }

    // 删除第三方账号密码数据
    void deleteAccount() {
        int id;
        cout << "输入要删除的账号ID: ";
        cin >> id;

        auto it = remove_if(accounts.begin(), accounts.end(), [id](const Account& acc) {
            return acc.id == id;
        });
        accounts.erase(it, accounts.end());
        saveData();
    }

    // 查找第三方账号密码数据
    void findAccount() {
        string platform;
        cout << "输入平台名称: ";
        cin >> platform;

        for (const auto& acc : accounts) {
            if (acc.platform.find(platform) != string::npos) {
                cout << "ID: " << acc.id << ", 平台: " << acc.platform
                     << ", 账号: " << acc.username << ", 密码: " << acc.password << endl;
            }
        }
    }

    // 修改第三方账号密码数据
    void modifyAccount() {
        int id;
        cout << "输入要修改的账号ID: ";
        cin >> id;

        for (auto& acc : accounts) {
            if (acc.id == id) {
                cout << "输入新的平台: ";
                cin >> acc.platform;
                cout << "输入新的账号: ";
                cin >> acc.username;
                cout << "输入新的密码: ";
                cin >> acc.password;
                saveData();
                return;
            }
        }
        cout << "no id for" << id << "address" << endl;
    }

    // 修改管理器密码
    void changeMasterPassword() {
        string oldPassword, newPassword;
        cout << "输入当前密码: ";
        cin >> oldPassword;

        if (oldPassword != masterPassword) {
            cout << "密码错误." << endl;
            ; return;
        }

        cout << "输入新密码: ";
        cin >> newPassword;
        masterPassword = newPassword;
        saveMasterPassword();
    }

    // 显示所有弱密码
    void showWeakPasswords() {
        displayWeakPasswords();
    }

    // 显示重复的密码
    void showDuplicatePasswords() {
        displayDuplicatePasswords();
    }
};

#endif