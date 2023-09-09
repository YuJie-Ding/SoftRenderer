// Sandbox.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Sandbox.h"

#include <sstream>
#include <ctime>
#include <iostream>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SANDBOX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SANDBOX));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SANDBOX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SANDBOX);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   SetTimer(hWnd,             // handle to main window 
       NULL,            // timer identifier 
       1,                 // 0.001-second interval 
       (TIMERPROC)NULL);     // no timer callback 

   srand(time(0));

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//


unsigned char* backBuffer = nullptr;

void setPixel(unsigned x, unsigned y, unsigned width, unsigned char r, unsigned char g, unsigned char b)
{
    backBuffer[(y * width + x) * 4] = b;
    backBuffer[(y * width + x) * 4 + 1] = g;
    backBuffer[(y * width + x) * 4 + 2] = r;
}

unsigned long long lastTime = GetTickCount64();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            unsigned long long  timeNow = GetTickCount64();
            std::cout << 1000.0 / (timeNow - lastTime) << std::endl;
            lastTime = timeNow;
            PAINTSTRUCT ps;

            // 获取工作区大小
            RECT rect;
            GetClientRect(hWnd, &rect);
            LONG width = rect.right - rect.left;
            LONG height = rect.bottom - rect.top;
            if (backBuffer == nullptr)
            {
                backBuffer = new unsigned char[width * height * 4];
            }

            ZeroMemory(backBuffer, width * height * 4 * sizeof(unsigned char));
            // 开始绘制
            HDC hdc = BeginPaint(hWnd, &ps);

            //HDC mdc = CreateCompatibleDC(hdc);
            //HBITMAP hbmp;
            //hbmp = CreateCompatibleBitmap(mdc, width, height);
            //SelectObject(mdc, hbmp);
            //Rectangle(mdc, 100, 100, 200, 200);
            //Rectangle(mdc, 300, 300, 200, 200);
            //SR::Vector3f vec3(5, 6, 7);
            //float vec3Len = vec3.Magnitude();
            //std::ostringstream text;
            //text << vec3.ToString();
            //std::string textStr = text.str();
            //RECT textRect{ 0, 0, 100, 100 };
            //DrawTextA(mdc, textStr.c_str(), textStr.size(), &textRect, DT_CENTER);
            //BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY);


            BITMAPINFO bitmapInfo;
            ZeroMemory(&bitmapInfo, sizeof(BITMAPINFO));
            bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bitmapInfo.bmiHeader.biWidth = width;
            bitmapInfo.bmiHeader.biHeight = height;
            bitmapInfo.bmiHeader.biPlanes = 1;
            bitmapInfo.bmiHeader.biBitCount = 32;
            bitmapInfo.bmiHeader.biCompression = BI_RGB;

            for (unsigned int i = 0; i < width; i++)
            {
                for (unsigned int j = 0; j < height; j++)
                {
                    setPixel(i, j, width, 255, 255, 0);
                }
            }

            StretchDIBits(hdc,
                0, 0, width, height,
                0, height, width, -height,
                backBuffer,
                &bitmapInfo,
                DIB_RGB_COLORS,
                SRCCOPY);

            // 绘制结束
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
        RECT rect;
        GetClientRect(hWnd, &rect);
        InvalidateRect(hWnd, &rect, FALSE);
        UpdateWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
