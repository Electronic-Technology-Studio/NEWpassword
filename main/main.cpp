//���ӿƼ�������2024-2030??��Ȩ����
//NEWpassword�����а汾���ļ�
#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )

#include "../include/PasswordManager.hpp"
#include "../include/RSA.hpp"
using namespace std;

int main() {
#if BUILD_VISION==BUILD
    std::cout << "����ʼ����..." << std::endl;

    int *prime=new int[10];
    primegenerator(prime);
    int seed, p, q;
    seed = time(0);
    srand((unsigned int)seed);                              //�����ڷ�Χ�ڵ��������p��q
    p = rand() % 10;
    do {
        q = rand() % 10;
    } while (q == p);
    int e, d, n, fi_n, r, nu, w1, w2;

    int a;
    cout << "��ѡ�����/����" << endl;
    cout << "����0�������" << ' ' << "����1�������" << endl;
    cin >> a;
    char* minwen=new char[1000];

    int i, j, mi;
    if (a == 0) {
        n = prime[p] * prime[q];
        fi_n = (prime[p] - 1) * (prime[q] - 1);
        for (r = fi_n / 2; r >= 1; r--) {                                                 //��ù�Կ
            if (exgcd(r, fi_n, w1, w2) == 1) {
                e = r;
                break;
            }
        }
        r = exgcd(e, fi_n, d, nu);
        cout << "����������" << endl;
        scanf("%s", minwen);
        vector<int> shuma_minwen(strlen(minwen));
        for (i = 0; i < strlen(minwen); i++) {
            shuma_minwen[i] = minwen[i];
        }
        vector<int> shuma_miwen(strlen(minwen));                                         //¼���������ʼ����
        for (i = 0; i < strlen(minwen); i++) {
            mi = shuma_minwen[i];
            shuma_miwen[i] = 1;
            for (j = 1; j <= e; j++) {
                shuma_miwen[i] = (shuma_miwen[i] * mi) % n;
            }
        }
        cout << "����Ϊ" << endl;
        for (i = 0; i < strlen(minwen); i++) {
            cout << shuma_miwen[i] << ' ';                                       //���ܽ�����������ģ�˽Կ
        }
        cout << endl << "���ĳ���Ϊ" << i << endl;
        cout << endl << "���ܹ�ԿΪ" << endl<<e<<' '<<n << endl;
        cout << endl << "����˽ԿΪ" << endl;
        cout << d <<' '<< n << endl;
        delete[] prime;
        delete[] minwen;
    }
    else if (a == 1) {
        int* shuma_jiemiwen = new int[10000];

        cout << "���������ĳ���" << endl;
        int k;
        cin >> k;
        cout << "����������" << endl;                                                      //¼������
        int t = 0;
        for (i = 0; i < k; i++) {
            cin >> shuma_jiemiwen[i];
        }
        int sizel = k;

        cout << "������˽Կ��d��n�� ���ֱ�����d��n�ÿո������" << endl;
        int d1, n1;
        cin >> d1 >> n1;
        int ming;
        vector<int> shuma_jieminwen(sizel);                                                    //��ʼ����
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
        cout << "����Ϊ" << endl;                                                        //�������
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
        cout << "1. ��ӵ������˺�����\n";
        cout << "2. ɾ���������˺�����\n";
        cout << "3. ���ҵ������˺�����\n";
        cout << "4. �޸ĵ������˺�����\n";
        cout << "5. �޸Ĺ���������\n";
        cout << "6. ��ʾ����������\n";
        cout << "7. ��ʾ�ظ�����\n";
        cout << "0. �˳�\n";
        cout << "��ѡ��: ";
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
        default: cout << "��Чѡ�" << endl; break;
        }
    }
    return 0;
#endif
    return -1;
}


/*// ���ڹ��̺���
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
    // ע�ᴰ����
    const char* CLASS_NAME = "test";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // ��������
    HWND hwnd = CreateWindow(
        CLASS_NAME,                   // ��������
        "�ҵĵ�һ��windows",          // ���ڱ���
        WS_OVERLAPPEDWINDOW,          // ������ʽ
        CW_USEDEFAULT,                // X λ��
        CW_USEDEFAULT,                // Y λ��
        CW_USEDEFAULT,                // ���
        CW_USEDEFAULT,                // �߶�
        NULL,                         // �����ھ��
        NULL,                         // �˵����
        hInstance,                    // Ӧ�ó���ʵ�����
        NULL                          // ��������
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // ��ʾ����
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
*/

