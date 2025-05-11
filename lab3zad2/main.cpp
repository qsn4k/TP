#include <windows.h>
#include <tchar.h>
#include <stdio.h> // ��� _stprintf_s

// ��������� �������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND hwnd);
void OnStudentButtonClick(HWND hwnd);

// ���������� ���������� ��� ��������� ����������
HWND hLastName, hFirstName, hMiddleName, hResult;
HWND hStudentButton;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow)
{
    const TCHAR szClassName[] = TEXT("StudentDataWindow");
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
        TEXT("��������� ����� ������ ��������"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
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
        CreateContr
            ols(hWnd);
        break;

    case WM_COMMAND:
        if ((HWND)lParam == hStudentButton)
        {
            OnStudentButtonClick(hWnd);
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
    CreateWindow(TEXT("STATIC"), TEXT("�������:"),
        WS_VISIBLE | WS_CHILD,
        50, 50, 100, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("���:"),
        WS_VISIBLE | WS_CHILD,
        50, 100, 100, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("��������:"),
        WS_VISIBLE | WS_CHILD,
        50, 150, 100, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("���������:"),
        WS_VISIBLE | WS_CHILD,
        50, 250, 100, 25, hWnd, NULL, NULL, NULL);

    // ������� ���� �����
    hLastName = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 50, 300, 25, hWnd, NULL, NULL, NULL);

    hFirstName = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 100, 300, 25, hWnd, NULL, NULL, NULL);

    hMiddleName = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 150, 300, 25, hWnd, NULL, NULL, NULL);

    hResult = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
        150, 250, 300, 25, hWnd, NULL, NULL, NULL);

    // ������� ������
    hStudentButton = CreateWindow(TEXT("BUTTON"), TEXT("�������"),
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        200, 200, 200, 30, hWnd, NULL, NULL, NULL);
}

void OnStudentButtonClick(HWND hWnd)
{
    TCHAR lastName[100] = { 0 };
    TCHAR firstName[100] = { 0 };
    TCHAR middleName[100] = { 0 };
    TCHAR result[300] = { 0 };

    // �������� ����� �� ����� �����
    GetWindowText(hLastName, lastName, 100);
    GetWindowText(hFirstName, firstName, 100);
    GetWindowText(hMiddleName, middleName, 100);

    // ��������� ���������
    _sntprintf_s(result, 300, _TRUNCATE, TEXT("%s %s %s"), lastName, firstName, middleName);

    // ������������� ����� � ���� ����������
    SetWindowText(hResult, result);
}