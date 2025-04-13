#include <windows.h> 

// �������� ������� ��������� ��������� ����
LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

// ����� ����� Windows-����������
int WINAPI WinMain(HINSTANCE hInst,      // ���������� ���������� ����������
    HINSTANCE hPrevInst,                // �� ������������ (���������� ��������)
    LPSTR pCommandLine,                // ��������� ������
    int nCommandShow)                  // ������ ����������� ����
{
    TCHAR className[] = "��� �����";   // ��� ������ ����
    HWND hWindow;                      // ���������� ����
    MSG message;                       // ��������� ��� �������� ���������
    WNDCLASSEX windowClass;           // ��������� ������ ����

    // ���������� ��������� ������ ����
    windowClass.cbSize = sizeof(windowClass);       // ������ ���������
    windowClass.style = CS_HREDRAW | CS_VREDRAW;    // ����� �����������
    windowClass.lpfnWndProc = WindowProcess;        // ��������� �� ������� ��������� ���������
    windowClass.lpszMenuName = NULL;                // ��� ����
    windowClass.lpszClassName = className;          // ��� ������
    windowClass.cbWndExtra = NULL;                  // ���. ������ ��� ����
    windowClass.cbClsExtra = NULL;                  // ���. ������ ��� ������
    windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // ������ ����
    windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // ��������� ������
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // ������
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ����� ���
    windowClass.hInstance = hInst;                  // ���������� ����������

    // ����������� ������ ����
    if (!RegisterClassEx(&windowClass))
    {
        MessageBox(NULL, "�� ���������� ���������������� �����!", "������", MB_OK);
        return NULL;
    }

    // �������� ����
    hWindow = CreateWindow(className,
        "��������� ����� ��������",    // ��������� ����
        WS_OVERLAPPEDWINDOW,          // ����� ����
        CW_USEDEFAULT,                // ������� X �� ���������
        NULL,                         // ������� Y �� ���������
        CW_USEDEFAULT,                // ������ �� ���������
        NULL,                         // ������ �� ���������
        (HWND)NULL,                   // ������������ ����
        NULL,                         // ����
        HINSTANCE(hInst),             // ���������� ����������
        NULL                          // �������������� ���������
    );

    if (!hWindow) {
        MessageBox(NULL, "�� ���������� ������� ����!", "������", MB_OK);
        return NULL;
    }

    // ����������� � ���������� ����
    ShowWindow(hWindow, nCommandShow);
    UpdateWindow(hWindow);

    // ���� ��������� ���������
    while (GetMessage(&message, NULL, NULL, NULL)) {
        TranslateMessage(&message);   // �������������� ��������� ����������
        DispatchMessage(&message);    // �������� ��������� � WindowProcess
    }

    return message.wParam;            // ������� ���� ����������
}

// ������� ��������� ��������� ����
LRESULT CALLBACK WindowProcess(HWND hWindow, UINT uMessage,
    WPARAM wParameter, LPARAM lParameter)
{
    HDC hDeviceContext;               // �������� ����������
    PAINTSTRUCT paintStruct;          // ��������� ��� ���������
    RECT rectPlace;                   // ������������� ���������� �������
    HFONT hFont;                      // �����

    static int sec = 0;               // ������� ������ ������
    TCHAR workTime[10];               // ����� ��� ������ �������

    static PTCHAR text;               // ����� ��� ��������� ������
    static int size = 0;              // ������ ���������� ������

    switch (uMessage)
    {
    case WM_CREATE:  // �������� ����
        SetTimer(hWindow, 1, 1000, NULL);  // ��������� ������� (1 ���)
        text = (PTCHAR)GlobalAlloc(GPTR, 50000 * sizeof(TCHAR)); // ��������� ������ ��� �����
        MessageBox(NULL, "����������, ������� ������� � ��� ����� ������������ �� ������!",
            "��������!!!", MB_ICONASTERISK | MB_OK);  // �������������� ���������
        SetForegroundWindow(hWindow);  // ��������� ����
        break;

    case WM_PAINT:  // ����������� ����
        hDeviceContext = BeginPaint(hWindow, &paintStruct);  // ������ ���������
        GetClientRect(hWindow, &rectPlace);  // ��������� �������� ���������� �������
        SetTextColor(hDeviceContext, NULL);  // ���� ������ �� ���������

        // �������� ������
        hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0,
            DEFAULT_CHARSET,
            0, 0, 0, VARIABLE_PITCH,
            "Times New Roman");
        SelectObject(hDeviceContext, hFont);  // ����� ������

        // ��������� ������ (���� �� ������ Enter)
        if (wParameter != VK_RETURN)
            DrawText(hDeviceContext,
                (LPCSTR)text,
                size, &rectPlace,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);  // ��������� �� ������

        EndPaint(hWindow, &paintStruct);  // ���������� ���������
        break;

    case WM_CHAR:  // ��������� ����� ��������
        switch (wParameter)
        {
        case VK_RETURN:  // ������� Enter - ������� ������
            size = 0;
            break;
        case VK_BACK:    // ������� Backspace - �������� �������
            if (size != 0)
                size--;
            break;
        default:        // ���� �������� �������
            text[size] = (char)wParameter;
            size++;
            break;
        }
        InvalidateRect(hWindow, NULL, TRUE);  // ������ �� �����������
        break;

    case WM_TIMER:  // ��������� �������
        sec++;      // ���������� �������� ������
        break;

    case WM_DESTROY:  // �������� ����
        KillTimer(hWindow, 1);  // �������� �������
        _itoa_s(sec, workTime, 10, 10);  // �������������� ������ � ������
        MessageBox(NULL, (LPCSTR)workTime, "����� ������ ��������� (���.):", MB_ICONASTERISK | MB_OK);  // ����� ������� ������
        PostQuitMessage(NULL);  // ���������� ����������
        GlobalFree((HGLOBAL)text);  // ������������ ������
        break;

    default:  // ��������� ��������� �� ���������
        return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
    }
    return NULL;
}