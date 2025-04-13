#include <windows.h>
#include <tchar.h>
#include <stdio.h>
//egor good blowjob
// Прототипы функций
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND hwnd);
void OnConvertButtonClick(HWND hwnd);

// Глобальные переменные для элементов управления
HWND hExchangeRate, hRublesAmount, hResult;
HWND hConvertButton;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow)
{
    const TCHAR szClassName[] = TEXT("CurrencyConverter");
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };

    // Заполняем структуру класса окна
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = szClassName;

    // Регистрируем класс окна
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"), TEXT("Ошибка"), MB_ICONERROR);
        return 0;
    }

    // Создаем главное окно
    hWnd = CreateWindowEx(
        0,
        szClassName,
        TEXT("Конвертер валют"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
        NULL, NULL, hInst, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, TEXT("Ошибка создания окна!"), TEXT("Ошибка"), MB_ICONERROR);
        return 0;
    }

    // Отображаем окно
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Цикл сообщений
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
    // Создаем метки
    CreateWindow(TEXT("STATIC"), TEXT("Курс доллара:"),
        WS_VISIBLE | WS_CHILD,
        20, 20, 120, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("Сумма в рублях:"),
        WS_VISIBLE | WS_CHILD,
        20, 60, 120, 25, hWnd, NULL, NULL, NULL);

    CreateWindow(TEXT("STATIC"), TEXT("Результат ($):"),
        WS_VISIBLE | WS_CHILD,
        20, 100, 120, 25, hWnd, NULL, NULL, NULL);

    // Создаем поля ввода
    hExchangeRate = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 20, 200, 25, hWnd, NULL, NULL, NULL);

    hRublesAmount = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        150, 60, 200, 25, hWnd, NULL, NULL, NULL);

    hResult = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
        150, 100, 200, 25, hWnd, NULL, NULL, NULL);

    // Создаем кнопку
    hConvertButton = CreateWindow(TEXT("BUTTON"), TEXT("По курсу"),
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

    // Получаем данные из полей ввода
    GetWindowText(hExchangeRate, rateText, 50);
    GetWindowText(hRublesAmount, rublesText, 50);

    // Преобразуем текст в числа
    exchangeRate = _ttof(rateText);
    rublesAmount = _ttof(rublesText);

    // Вычисляем сумму в долларах
    if (exchangeRate > 0)
    {
        dollarsAmount = rublesAmount / exchangeRate;
        // Форматируем результат с 2 знаками после запятой
        _sntprintf_s(resultText, 50, _TRUNCATE, TEXT("%.2f"), dollarsAmount);
    }
    else
    {
        _tcscpy_s(resultText, 50, TEXT("Неверный курс"));
    }

    // Устанавливаем текст в поле результата
    SetWindowText(hResult, resultText);
}