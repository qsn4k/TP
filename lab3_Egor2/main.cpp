#include <windows.h>
#include <tchar.h>
#include <stdio.h>
//egor good blowjob
// ��������� �������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND hwnd);
void OnConvertButtonClick(HWND hwnd);

// ���������� ���������� ��� ��������� ����������
HWND hExchangeRate, hRublesAmount, hResult;
HWND hConvertButton;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow)
{
    const TCHAR szClassName[] = TEXT("CurrencyConverter");
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };

    // ��������� ��������� ������ ����
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = szClassName;

    // ������������ ����� ����
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("������ ����������� ������ ����!"), TEXT("������"), MB_ICONERROR);
        return 0;
    }

    // ������� ������� ����
    hWnd = CreateWindowEx(
        0,
        szClassName,
        TEXT("��������� �����"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
        NULL, NULL, hInst, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, TEXT("������ �������� ����!"), TEXT("������"), MB_ICONERROR);
        return 0;
    }

    // ���������� ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // ���� ���������
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateControls(hWnd);
        break;

    case WM_COMMAND:
        if ((HWND)lParam == hConvertButton)
        {
            OnConvertButtonClick(hWnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void CreateControls(HWND hWnd)
{
    // ������� �����
    CreateWindow(TEXT("STATIC"), TEXT("���� �������:"),
        WS_VISIBLE | WS_CHILD,
        20, 20, 120, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("����� � ������:"),
        WS_VISIBLE | WS_CHILD,
        20, 60, 120, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("��������� ($):"),
        WS_VISIBLE | WS_CHILD,
        20, 100, 120, 25, hWnd, NULL, NULL, NULL);

    // ������� ���� �����
    hExchangeRate = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 20, 200, 25, hWnd, NULL, NULL, NULL);

    hRublesAmount = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 60, 200, 25, hWnd, NULL, NULL, NULL);

    hResult = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
        150, 100, 200, 25, hWnd, NULL, NULL, NULL);

    // ������� ������
    hConvertButton = CreateWindow(TEXT("BUTTON"), TEXT("�� �����"),
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        150, 150, 200, 30, hWnd, NULL, NULL, NULL);
}

void OnConvertButtonClick(HWND hWnd)
{
    TCHAR rateText[50] = { 0 };
    TCHAR rublesText[50] = { 0 };
    TCHAR resultText[50] = { 0 };
    double exchangeRate = 0.0;
    double rublesAmount = 0.0;
    double dollarsAmount = 0.0;

    // �������� ������ �� ����� �����
    GetWindowText(hExchangeRate, rateText, 50);
    GetWindowText(hRublesAmount, rublesText, 50);

    // ����������� ����� � �����
    exchangeRate = _ttof(rateText);
    rublesAmount = _ttof(rublesText);

    // ��������� ����� � ��������
    if (exchangeRate > 0)
    {
        dollarsAmount = rublesAmount / exchangeRate;
        // ����������� ��������� � 2 ������� ����� �������
        _sntprintf_s(resultText, 50, _TRUNCATE, TEXT("%.2f"), dollarsAmount);
    }
    else
    {
        _tcscpy_s(resultText, 50, TEXT("�������� ����"));
    }

    // ������������� ����� � ���� ����������
    SetWindowText(hResult, resultText);
}