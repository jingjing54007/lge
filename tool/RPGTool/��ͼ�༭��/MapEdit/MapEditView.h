// MapEditView.h : interface of the CMapEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPEDITVIEW_H__073CA4B4_B8EF_43F7_B0CD_396E3AF256CE__INCLUDED_)
#define AFX_MAPEDITVIEW_H__073CA4B4_B8EF_43F7_B0CD_396E3AF256CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MapEditDoc.h"
#include "QieHuanCode.h"


extern int m_x,m_y,npcstate,npcstoptime,m_qiehuancode;
extern float m_zoomin,m_zoomout;
class CMapEditView : public CScrollView
{
protected: // create from serialization only
	CMapEditView();
	DECLARE_DYNCREATE(CMapEditView)

// Attributes
public:
	CMapEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DelNpcPoint(CPoint pt);
	void MoveNpcPoint(CPoint pt);
	void DelThingPoint(CPoint pt);
	void MoveThingPoint(CPoint pt);

	void DelNpc(CPoint pt);
	void AddNpc(CPoint pt);
	void DelThing(CPoint pt);
	void AddThing(CPoint pt);
	void ChangeAreaAttrib(CPoint pt);
	void DelArea(CPoint pt);
	void DelPoint(CPoint pt);
	void MovePoint(CPoint pt);
	
	void DrawLine(POINT pt1,POINT pt2,int tp);
	void Drawtemp(CPoint pt);
	void MyInvalid(POINT fpt,POINT spt,int w,int h);
	void MarkPoint(CPoint pt,int line,COLORREF color);
	void AddPoint(BOOL starta,int statein,int stateout,CPoint pt);
	virtual ~CMapEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapEditView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapEditView.cpp
inline CMapEditDoc* CMapEditView::GetDocument()
   { return (CMapEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITVIEW_H__073CA4B4_B8EF_43F7_B0CD_396E3AF256CE__INCLUDED_)
