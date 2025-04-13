// Подключаем необходимые заголовочные файлы Windows API
#include <windows.h>    // Основной заголовочный файл Windows
#include <windowsx.h>   // Дополнительные макросы и функции Windows
#include <tchar.h>      // Для работы с Unicode/ANSI строками

// Идентификаторы для дочерних окон
#define ID_FIRSTCHILD   100  // Идентификатор первого дочернего окна
#define ID_SECONDCHILD  101  // Идентификатор второго дочернего окна
#define ID_THIRDCHILD   102  // Идентификатор третьего дочернего окна

// Объявляем прототипы оконных процедур
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);       // Для главного окна
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);     // Для дочерних окон

HINSTANCE hinst;  // Глобальная переменная для хранения дескриптора экземпляра приложения

// Точка входа Windows-приложения
int APIENTRY WinMain(HINSTANCE hInstance,    // Дескриптор текущего экземпляра приложения
	HINSTANCE hPrevInstance, // Дескриптор предыдущего экземпляра (не используется)
	LPSTR lpCmdLine,        // Командная строка
	int nCmdShow)           // Как показывать окно (свернуто/развернуто)
{
	HWND hwnd;      // Дескриптор главного окна
	MSG msg;        // Структура для хранения сообщений
	WNDCLASS w;     // Структура класса окна

	hinst = hInstance; // Сохраняем дескриптор экземпляра в глобальной переменной

	// Заполняем структуру класса окна
	memset(&w, 0, sizeof(WNDCLASS)); // Обнуляем структуру
	w.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна - перерисовка при изменении размеров
	w.lpfnWndProc = WndProc;           // Указатель на оконную процедуру
	w.hInstance = hInstance;           // Дескриптор экземпляра приложения
	w.hbrBackground = GetStockBrush(WHITE_BRUSH); // Белый фон окна
	w.lpszClassName = TEXT("Мой класс");          // Имя класса окна
	w.hCursor = LoadCursor(NULL, IDC_ARROW);      // Стандартный курсор

	// Регистрируем класс окна
	RegisterClass(&w);

	// Создаем главное окно
	hwnd = CreateWindow(
		TEXT("Мой класс"),             // Имя класса окна
		TEXT("Главное окно"),          // Заголовок окна
		WS_OVERLAPPEDWINDOW,           // Стиль окна - стандартное перекрывающееся окно
		10, 10, 600, 480,             // Позиция (x,y) и размеры (ширина, высота)
		NULL,                          // Родительское окно (отсутствует)
		NULL,                          // Меню (отсутствует)
		hInstance,                     // Дескриптор экземпляра
		NULL);                         // Дополнительные параметры

	// Показываем и обновляем окно
	ShowWindow(hwnd, nCmdShow);  // Отображаем окно
	UpdateWindow(hwnd);          // Обновляем клиентскую область

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))  // Получаем сообщение из очереди
	{
		TranslateMessage(&msg);  // Преобразуем сообщения клавиш в символы
		DispatchMessage(&msg);   // Отправляем сообщение оконной процедуре
	}

	return msg.wParam;  // Возвращаем параметр завершения
}

// Оконная процедура для главного окна
LRESULT CALLBACK WndProc(HWND hwnd,       // Дескриптор окна
	UINT Message,    // Номер сообщения
	WPARAM wparam,   // Параметр сообщения
	LPARAM lparam)   // Дополнительный параметр
{
	switch (Message)  // Анализируем тип сообщения
	{
	case WM_CREATE:  // Сообщение создания окна
		// Создаем три дочерних окна
		for (int i = 0; i < 3; i++)
		{
			WNDCLASS w;  // Структура класса окна для дочерних окон
			memset(&w, 0, sizeof(WNDCLASS));  // Обнуляем структуру

			// Заполняем параметры класса окна
			w.lpfnWndProc = ChildProc;        // Оконная процедура для дочерних окон
			w.hInstance = hinst;              // Дескриптор экземпляра
			w.hbrBackground = GetStockBrush(WHITE_BRUSH); // Белый фон
			w.lpszClassName = TEXT("Дочерний");           // Имя класса
			w.hCursor = LoadCursor(NULL, IDC_CROSS);      // Курсор в виде креста

			RegisterClass(&w);  // Регистрируем класс дочернего окна

			// Создаем дочернее окно
			HWND child;
			child = CreateWindowEx(
				0,                       // Расширенный стиль
				TEXT("Дочерний"),         // Имя класса
				(LPCTSTR)NULL,           // Заголовок окна (отсутствует)
				WS_CHILD | WS_BORDER | WS_VISIBLE, // Стиль - дочернее с рамкой и видимое
				75 + i * 175, 120,          // Позиция (x,y) - смещаем каждое следующее окно
				100, 100,                  // Размеры (ширина, высота)
				hwnd,                    // Родительское окно
				(HMENU)(int)(ID_FIRSTCHILD + i), // Идентификатор (100, 101, 102)
				hinst,                   // Дескриптор экземпляра
				NULL);                   // Дополнительные параметры

			// Показываем и обновляем дочернее окно
			ShowWindow(child, SW_NORMAL);
			UpdateWindow(child);
		}
		return 0;  // Возвращаем 0, так как сообщение обработано

	case WM_DESTROY:  // Сообщение о закрытии окна
		PostQuitMessage(0);  // Помещаем сообщение WM_QUIT в очередь
		break;
	}

	// Передаем все необработанные сообщения стандартной процедуре
	return DefWindowProc(hwnd, Message, wparam, lparam);
}

// Оконная процедура для дочерних окон
LRESULT CALLBACK ChildProc(HWND hwnd,      // Дескриптор окна
	UINT Message,   // Номер сообщения
	WPARAM wparam,  // Параметр сообщения
	LPARAM lparam)  // Дополнительный параметр
{
	if (Message == WM_DESTROY)  // Сообщение о закрытии окна
	{
		return 0;  // Возвращаем 0, так как сообщение обработано
	}

	// Передаем все необработанные сообщения стандартной процедуре
	return DefWindowProc(hwnd, Message, wparam, lparam);
}