#include "framework.h"
#include "MetalSlug.h"
#include "Bitmap.h"

#define MAX_LOADSTRING 100
#define TIMER_MAIN 1
#define TIMER_ANI 2

/*
    TODO:
    플레이어 죽는 애니메이션 재생 및 비활성화
    적 배치
*/

RECT rect = { 0,0,1280,720 };
HDC g_hdc;
HWND g_hWnd;

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_METALSLUG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_METALSLUG));

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if(GetGameMode() == EGameMode::InGame)
                UpdateKeyInput();
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_METALSLUG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_METALSLUG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
      CW_USEDEFAULT, 0, rect.right, rect.bottom, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);
   CreateSoundManager();
   CreateBgmSound();

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT point;
    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rect);
        UpdateRectView(rect);
        CreateCamera(rect);
        InitBitmap();
        Gdi_Init();
        SetTimer(hWnd, TIMER_MAIN, 16, NULL);
        break;

    case WM_MOUSEMOVE:
        if (GetGameMode() == EGameMode::Title)
        {
            point.x = GET_X_LPARAM(lParam) + GetCamera()->GetCameraViewport().left;
            point.y = GET_Y_LPARAM(lParam) + GetCamera()->GetCameraViewport().top;
            if(IsSelectSoldier() == false)
                SetMousePos(point);
        }
        break;

    case WM_LBUTTONDOWN:
        point.x = GET_X_LPARAM(lParam) + GetCamera()->GetCameraViewport().left;
        point.y = GET_Y_LPARAM(lParam) + GetCamera()->GetCameraViewport().top;
        SetMouseClickPos(point);
        if (GetGameMode() == EGameMode::Title)
        {
            SelectSoldier();
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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

    case WM_TIMER:
        switch (wParam)
        {
        case TIMER_MAIN:
            break;
        }
        InvalidateRgn(hWnd, NULL, FALSE);
        break;
    case WM_CHAR:
        switch (wParam)
        {
        case '1': SetDebugMode(!IsDebugMode()); break;
        case '2': DebugDestroyRuin(); break;
        case '3': DebugSpawnEnemy(); break;
        case '4': ActivePlayer();  break;
        case '5': break;
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            g_hdc = BeginPaint(hWnd, &ps);

            UpdateObject();
            DrawBitmapDoubleBuffering(hWnd, g_hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        Gdi_End();

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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