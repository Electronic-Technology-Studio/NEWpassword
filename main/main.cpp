//电子科技工作室2024-2030??版权所有
//NEWpassword命令行版本主文件
#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )

#include "../include/PasswordManager.hpp"
#include "../include/RSA.hpp"
using namespace std;

int main() {
#if BUILD_VISION==BUILD
    std::cout << "程序开始运行..." << std::endl;

    int *prime=new int[10];
    primegenerator(prime);
    int seed, p, q;
    seed = time(0);
    srand((unsigned int)seed);                              //生成在范围内的随机素数p，q
    p = rand() % 10;
    do {
        q = rand() % 10;
    } while (q == p);
    int e, d, n, fi_n, r, nu, w1, w2;

    int a;
    cout << "请选择加密/解密" << endl;
    cout << "输入0代表加密" << ' ' << "输入1代表解密" << endl;
    cin >> a;
    char* minwen=new char[1000];

    int i, j, mi;
    if (a == 0) {
        n = prime[p] * prime[q];
        fi_n = (prime[p] - 1) * (prime[q] - 1);
        for (r = fi_n / 2; r >= 1; r--) {                                                 //求得公钥
            if (exgcd(r, fi_n, w1, w2) == 1) {
                e = r;
                break;
            }
        }
        r = exgcd(e, fi_n, d, nu);
        cout << "请输入明文" << endl;
        scanf("%s", minwen);
        vector<int> shuma_minwen(strlen(minwen));
        for (i = 0; i < strlen(minwen); i++) {
            shuma_minwen[i] = minwen[i];
        }
        vector<int> shuma_miwen(strlen(minwen));                                         //录入结束，开始加密
        for (i = 0; i < strlen(minwen); i++) {
            mi = shuma_minwen[i];
            shuma_miwen[i] = 1;
            for (j = 1; j <= e; j++) {
                shuma_miwen[i] = (shuma_miwen[i] * mi) % n;
            }
        }
        cout << "密文为" << endl;
        for (i = 0; i < strlen(minwen); i++) {
            cout << shuma_miwen[i] << ' ';                                       //加密结束，输出密文，私钥
        }
        cout << endl << "密文长度为" << i << endl;
        cout << endl << "加密公钥为" << endl<<e<<' '<<n << endl;
        cout << endl << "解密私钥为" << endl;
        cout << d <<' '<< n << endl;
        delete[] prime;
        delete[] minwen;
    }
    else if (a == 1) {
        int* shuma_jiemiwen = new int[10000];

        cout << "请输入密文长度" << endl;
        int k;
        cin >> k;
        cout << "请输入密文" << endl;                                                      //录入密文
        int t = 0;
        for (i = 0; i < k; i++) {
            cin >> shuma_jiemiwen[i];
        }
        int sizel = k;

        cout << "请输入私钥（d，n） （分别输入d，n用空格隔开）" << endl;
        int d1, n1;
        cin >> d1 >> n1;
        int ming;
        vector<int> shuma_jieminwen(sizel);                                                    //开始解密
        for (i = 0; i < sizel; i++) {
            ming = shuma_jiemiwen[i];
            shuma_jieminwen[i] = 1;
            for (j = 0; j < d1; j++) {
                shuma_jieminwen[i] = shuma_jieminwen[i] * ming % n1;
            }
        }

        vector<char> jieminwen(sizel);
        for (i = 0; i < sizel; i++) {
            jieminwen[i] = shuma_jieminwen[i];
        }
        cout << "明文为" << endl;                                                        //输出明文
        for (i = 0; i < sizel; i++) {
            cout << jieminwen[i];
        }
        delete[] shuma_jiemiwen;
       
    }
    cin.get();
    cin.get();
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
    return -1;
}


/*// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // 注册窗口类
    const char* CLASS_NAME = "test";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 创建窗口
    HWND hwnd = CreateWindow(
        CLASS_NAME,                   // 窗口类名
        "我的第一个windows",          // 窗口标题
        WS_OVERLAPPEDWINDOW,          // 窗口样式
        CW_USEDEFAULT,                // X 位置
        CW_USEDEFAULT,                // Y 位置
        CW_USEDEFAULT,                // 宽度
        CW_USEDEFAULT,                // 高度
        NULL,                         // 父窗口句柄
        NULL,                         // 菜单句柄
        hInstance,                    // 应用程序实例句柄
        NULL                          // 创建参数
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 显示窗口
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
*/

