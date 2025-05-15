
// MFC_Laba_5.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMyApp:
// Сведения о реализации этого класса: MFC_Laba_5.cpp
//

class CMyApp : public CWinApp
{
public:
	CMyApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMyApp theApp;
