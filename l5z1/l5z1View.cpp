
// l5z1View.cpp: реализация класса Cl5z1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "l5z1.h"
#endif

#include "l5z1Doc.h"
#include "l5z1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cl5z1View

IMPLEMENT_DYNCREATE(Cl5z1View, CView)

BEGIN_MESSAGE_MAP(Cl5z1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cl5z1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение Cl5z1View

Cl5z1View::Cl5z1View() noexcept
{
	// TODO: добавьте код создания

}

Cl5z1View::~Cl5z1View()
{
}

BOOL Cl5z1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование Cl5z1View

void Cl5z1View::OnDraw(CDC* /*pDC*/)
{
	Cl5z1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать Cl5z1View


void Cl5z1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cl5z1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Cl5z1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Cl5z1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void Cl5z1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cl5z1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика Cl5z1View

#ifdef _DEBUG
void Cl5z1View::AssertValid() const
{
	CView::AssertValid();
}

void Cl5z1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cl5z1Doc* Cl5z1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cl5z1Doc)));
	return (Cl5z1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений Cl5z1View
