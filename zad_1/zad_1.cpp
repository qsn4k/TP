#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Глобальные переменные

// Имя класса окна.
static TCHAR szWindowClass[] = _T("win32app");
// Строка, которая появляется в строке заголовка приложения.
static TCHAR szTitle[] = _T("Приложение Win32 ");

HINSTANCE hInst;

// Оконная функция
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,     // Функция WinMain для регистрации типа 
	//оконного приложения.
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;// структура окна

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;//указатель на функцию окна
	wcex.cbClsExtra = 0;//кол-во дополнительно выделяемых байт для доп.стр
	wcex.cbWndExtra = 0;//для прилож-я
	wcex.hInstance = hInstance;// экземпляр
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));// пиктограмма
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// указатель на строку идентификатора меню
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Зарегистрировать класс не удалось!"),
			_T("Справочник по Win32"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Хранить экземпляр в  глобальной переменной
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)// идентификатор созданного окна с помощью  CreateWindow
	{
		MessageBox(NULL,
			_T("Ошибка вызова CreateWindow!"),
			_T("Справочник по Win32"),
			NULL);

		return 1;
	}
	//вывод окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	// цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
// функция окна выводит сообщение
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps; // структура с инф. о клиентской части окна
	HDC hdc;		// идентификатор конечного изображения
	TCHAR greeting1[] = _T("Денисенко Даниил");
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, greeting1, _tcslen(greeting1));
		// Завершение раздела макета приложения
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		// освобождает очередь сообщений
		break;
	}
	return 0;
}
