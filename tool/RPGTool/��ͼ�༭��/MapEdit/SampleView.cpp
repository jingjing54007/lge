// SampleView.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "SampleView.h"
#include "MapEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CScrollView)

CSampleView::CSampleView()
{
}

CSampleView::~CSampleView()
{
}


BEGIN_MESSAGE_MAP(CSampleView, CScrollView)
	//{{AFX_MSG_MAP(CSampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView drawing

void CSampleView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CSampleView::OnDraw(CDC* pDC)
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
//	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CMapEditDoc)));
	if(!pDoc->m_newwupic)
		return;
	else
	{
		CRect rc,rect;
		float rate1,rate2,rate;
		int picw,pich;
		GetClientRect(rc);
		
		CBrush brush;
		brush.CreateSolidBrush(RGB(0,0,0));
		pDC->FillRect(&rc, &brush);
	    brush.DeleteObject();

		GetClientRect(rect);

		rate1=float(pDoc->m_samSize.cx)/float(rect.Width());
		rate2=float(pDoc->m_samSize.cy)/float(rect.Height());

		if(rate1<1.0 && rate2<1.0)
		{
			rect.left=(rect.right-pDoc->m_samSize.cx)/2;
			rect.top=(rect.bottom-pDoc->m_samSize.cy)/2;
			
			//pDoc->m_sample.ShowBmp(pDC,rect.left,rect.top,pDoc->m_sample.GetBmpWidth(),pDoc->m_sample.GetBmpHeight(),1,SRCCOPY);
			pDC->StretchBlt(rect.left,rect.top,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->SampleDC,0,0,pDoc->m_samSize.cx,pDoc->m_samSize.cy,SRCCOPY);
		}
		else
		{
			rate=rate1>rate2?rate1:rate2;
			if(rate==rate1)
			{
				picw=rect.Width();
				pich=int((float(pDoc->m_samSize.cy)/float(pDoc->m_samSize.cx))*picw+1);

			}
			else
			{
				pich=rect.Height();
				picw=int((float(pDoc->m_samSize.cx)/float(pDoc->m_samSize.cy))*pich+1);
			}
			rect.left=(rect.Width()-picw)/2;
			rect.top=(rect.Height()-pich)/2;
			rect.right=rect.left+picw;
			rect.bottom=rect.top+pich;
			//pDoc->m_sample.ShowBmp(pDC,rect.left,rect.top,rect.Width(),rect.Height(),0,SRCCOPY);
			pDC->StretchBlt(rect.left,rect.top,picw,pich,&pDoc->SampleDC,0,0,pDoc->m_samSize.cx,pDoc->m_samSize.cy,SRCCOPY);
		}
		
	} 
	
	
}

/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers

void CSampleView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
  Invalidate();
}
