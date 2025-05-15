
// MFC_Laba_5.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "MFC_Laba_5.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CMyApp

CMyApp::CMyApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMyApp

CMyApp theApp;


// Инициализация CMyApp

BOOL CMyApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();
	CShellManager* pShellManager = new CShellManager;
	// Активация визуального диспетчера "Классический Windows" для включения 
//элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	SetRegistryKey(_T("UIR"));	// имя проекта используется реестром
	CMainDlg dlg; 			//создается объект диалога dlg (конструктор), но
	// на экране наш диалог не отображается
	m_pMainWnd = &dlg;		// создатся указатель m_pMainWnd на главное 
	// окно экрана 
	INT_PTR nResponse = dlg.DoModal();// вызов функции DoModal для отображения
	// окна диалога на экране
	// Возвращает код нажатой клавиши
		// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}


