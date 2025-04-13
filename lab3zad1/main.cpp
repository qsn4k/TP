#include <windows.h> 

// Прототип функции обработки сообщений окна
LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);

// Точка входа Windows-приложения
int WINAPI WinMain(HINSTANCE hInst,      // Дескриптор экземпляра приложения
    HINSTANCE hPrevInst,                // Не используется (устаревший параметр)
    LPSTR pCommandLine,                // Командная строка
    int nCommandShow)                  // Способ отображения окна
{
    TCHAR className[] = "Мой класс";   // Имя класса окна
    HWND hWindow;                      // Дескриптор окна
    MSG message;                       // Структура для хранения сообщений
    WNDCLASSEX windowClass;           // Структура класса окна

    // Заполнение структуры класса окна
    windowClass.cbSize = sizeof(windowClass);       // Размер структуры
    windowClass.style = CS_HREDRAW | CS_VREDRAW;    // Стиль перерисовки
    windowClass.lpfnWndProc = WindowProcess;        // Указатель на функцию обработки сообщений
    windowClass.lpszMenuName = NULL;                // Нет меню
    windowClass.lpszClassName = className;          // Имя класса
    windowClass.cbWndExtra = NULL;                  // Доп. память для окна
    windowClass.cbClsExtra = NULL;                  // Доп. память для класса
    windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Иконка окна
    windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // Маленькая иконка
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Курсор
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Белый фон
    windowClass.hInstance = hInst;                  // Дескриптор приложения

    // Регистрация класса окна
    if (!RegisterClassEx(&windowClass))
    {
        MessageBox(NULL, "Не получилось зарегистрировать класс!", "Ошибка", MB_OK);
        return NULL;
    }

    // Создание окна
    hWindow = CreateWindow(className,
        "Программа ввода символов",    // Заголовок окна
        WS_OVERLAPPEDWINDOW,          // Стиль окна
        CW_USEDEFAULT,                // Позиция X по умолчанию
        NULL,                         // Позиция Y по умолчанию
        CW_USEDEFAULT,                // Ширина по умолчанию
        NULL,                         // Высота по умолчанию
        (HWND)NULL,                   // Родительское окно
        NULL,                         // Меню
        HINSTANCE(hInst),             // Дескриптор приложения
        NULL                          // Дополнительные параметры
    );

    if (!hWindow) {
        MessageBox(NULL, "Не получилось создать окно!", "Ошибка", MB_OK);
        return NULL;
    }

    // Отображение и обновление окна
    ShowWindow(hWindow, nCommandShow);
    UpdateWindow(hWindow);

    // Цикл обработки сообщений
    while (GetMessage(&message, NULL, NULL, NULL)) {
        TranslateMessage(&message);   // Преобразование сообщений клавиатуры
        DispatchMessage(&message);    // Отправка сообщений в WindowProcess
    }

    return message.wParam;            // Возврат кода завершения
}

// Функция обработки сообщений окна
LRESULT CALLBACK WindowProcess(HWND hWindow, UINT uMessage,
    WPARAM wParameter, LPARAM lParameter)
{
    HDC hDeviceContext;               // Контекст устройства
    PAINTSTRUCT paintStruct;          // Структура для рисования
    RECT rectPlace;                   // Прямоугольник клиентской области
    HFONT hFont;                      // Шрифт

    static int sec = 0;               // Счетчик секунд работы
    TCHAR workTime[10];               // Буфер для строки времени

    static PTCHAR text;               // Буфер для вводимого текста
    static int size = 0;              // Размер введенного текста

    switch (uMessage)
    {
    case WM_CREATE:  // Создание окна
        SetTimer(hWindow, 1, 1000, NULL);  // Установка таймера (1 сек)
        text = (PTCHAR)GlobalAlloc(GPTR, 50000 * sizeof(TCHAR)); // Выделение памяти под текст
        MessageBox(NULL, "Пожалуйста, вводите символы и они будут отображаться на экране!",
            "ВНИМАНИЕ!!!", MB_ICONASTERISK | MB_OK);  // Информационное сообщение
        SetForegroundWindow(hWindow);  // Активация окна
        break;

    case WM_PAINT:  // Перерисовка окна
        hDeviceContext = BeginPaint(hWindow, &paintStruct);  // Начало рисования
        GetClientRect(hWindow, &rectPlace);  // Получение размеров клиентской области
        SetTextColor(hDeviceContext, NULL);  // Цвет текста по умолчанию

        // Создание шрифта
        hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0,
            DEFAULT_CHARSET,
            0, 0, 0, VARIABLE_PITCH,
            "Times New Roman");
        SelectObject(hDeviceContext, hFont);  // Выбор шрифта

        // Отрисовка текста (если не нажата Enter)
        if (wParameter != VK_RETURN)
            DrawText(hDeviceContext,
                (LPCSTR)text,
                size, &rectPlace,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);  // Отрисовка по центру

        EndPaint(hWindow, &paintStruct);  // Завершение рисования
        break;

    case WM_CHAR:  // Обработка ввода символов
        switch (wParameter)
        {
        case VK_RETURN:  // Нажатие Enter - очистка текста
            size = 0;
            break;
        case VK_BACK:    // Нажатие Backspace - удаление символа
            if (size != 0)
                size--;
            break;
        default:        // Ввод обычного символа
            text[size] = (char)wParameter;
            size++;
            break;
        }
        InvalidateRect(hWindow, NULL, TRUE);  // Запрос на перерисовку
        break;

    case WM_TIMER:  // Обработка таймера
        sec++;      // Увеличение счетчика секунд
        break;

    case WM_DESTROY:  // Закрытие окна
        KillTimer(hWindow, 1);  // Удаление таймера
        _itoa_s(sec, workTime, 10, 10);  // Преобразование секунд в строку
        MessageBox(NULL, (LPCSTR)workTime, "Время работы программы (сек.):", MB_ICONASTERISK | MB_OK);  // Вывод времени работы
        PostQuitMessage(NULL);  // Завершение приложения
        GlobalFree((HGLOBAL)text);  // Освобождение памяти
        break;

    default:  // Обработка сообщений по умолчанию
        return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
    }
    return NULL;
}