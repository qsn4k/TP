
// l5z1View.h: интерфейс класса Cl5z1View
//

#pragma once


class Cl5z1View : public CView
{
protected: // создать только из сериализации
	Cl5z1View() noexcept;
	DECLARE_DYNCREATE(Cl5z1View)

// Атрибуты
public:
	Cl5z1Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~Cl5z1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в l5z1View.cpp
inline Cl5z1Doc* Cl5z1View::GetDocument() const
   { return reinterpret_cast<Cl5z1Doc*>(m_pDocument); }
#endif

