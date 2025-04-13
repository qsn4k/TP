#include <Windows.h>

// Идентификатор для кнопки
#define IDB_BUTTON1 100

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegisterWndClass(LPCWSTR lpszClassName, WNDPROC wndProc);

// Глобальные переменные
HINSTANCE g_hInst = NULL;
HWND g_ChildWnd = NULL;

// Главная функция приложения
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, INT nCmdShow)
{
	g_hInst = hInst;
	LPCWSTR lpszClassName = L"MainWndClass";
	LPCWSTR lpszWndText = L"Главное окно";

	// Регистрация класса главного окна
	if (!RegisterWndClass(lpszClassName, WndProc)) {
		MessageBoxW(NULL, L"Ошибка регистрации класса главного окна!",
			L"Критическая ошибка", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Создание главного окна
	HWND hWnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		lpszClassName,
		lpszWndText,
		WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL,
		g_hInst, NULL);

	if (!hWnd) {
		MessageBoxW(NULL, L"Ошибка создания главного окна!",
			L"Критическая ошибка", MB_OK | MB_ICONERROR);
		return 2;
	}

	// Отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Рисование фигур
	HDC hdc = GetWindowDC(hWnd);
	Rectangle(hdc, 250, 250, 400, 400);
	Ellipse(hdc, 100, 100, 200, 200);
	Ellipse(hdc, 450, 100, 550, 200);
	Ellipse(hdc, 300, 450, 400, 550);
	ReleaseDC(hWnd, hdc);

	// Цикл обработки сообщений
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return (INT)msg.wParam;
}

// Функция регистрации класса окна
ATOM RegisterWndClass(LPCWSTR lpszClassName, WNDPROC wndProc)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = g_hInst;
	wc.lpfnWndProc = wndProc;
	wc.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
	wc.lpszClassName = lpszClassName;
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

	return RegisterClassW(&wc);
}

// Обработчик сообщений главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static BOOL childWndRegister = FALSE;
	static LPCWSTR lpszChildClassName = L"ChildWindow";
	static LPCWSTR lpszChildWndText = L"Дочернее окно";

	switch (msg) {
	case WM_CREATE:
		// Создание кнопки
		if (!CreateWindowW(
			L"BUTTON",
			L"Открыть окно",
			WS_CHILD | WS_VISIBLE,
			30, 25, 120, 30,
			hWnd,
			(HMENU)IDB_BUTTON1,
			g_hInst,
			NULL))
		{
			MessageBoxW(hWnd,
				L"Ошибка создания кнопки",
				L"Ошибка",
				MB_OK | MB_ICONWARNING);
		}
		break;

	case WM_COMMAND:
		// Обработка нажатия кнопки
		if (LOWORD(wParam) == IDB_BUTTON1 && !g_ChildWnd) {
			if (!childWndRegister) {
				if (!RegisterWndClass(lpszChildClassName, ChildWndProc)) {
					MessageBoxW(hWnd,
						L"Ошибка регистрации класса дочернего окна",
						L"Ошибка",
						MB_OK | MB_ICONWARNING);
					break;
				}
				childWndRegister = TRUE;
			}

			g_ChildWnd = CreateWindowW(
				lpszChildClassName,
				lpszChildWndText,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, 0,
				400, 400,
				hWnd,
				NULL,
				g_hInst,
				NULL);

			if (!g_ChildWnd) {
				MessageBoxW(hWnd,
					L"Ошибка создания дочернего окна",
					L"Ошибка",
					MB_OK | MB_ICONWARNING);
			}
			else {
				ShowWindow(g_ChildWnd, SW_SHOW);
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений дочернего окна
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_ERASEBKGND:
	{
		// Создаем красную кисть
		HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 0, 0));

		// Получаем размеры клиентской области
		RECT rect;
		GetClientRect(hWnd, &rect);

		// Заливаем фон красным цветом
		FillRect((HDC)wParam, &rect, hRedBrush);

		// Удаляем кисть (во избежание утечки ресурсов)
		DeleteObject(hRedBrush);

		return 1; // Сообщаем, что фон обработан
	}

	case WM_DESTROY:
		// При уничтожении окна сбрасываем дескриптор
		g_ChildWnd = NULL;
		break;

	default:
		// Обработка по умолчанию для остальных сообщений
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	return 0;
}