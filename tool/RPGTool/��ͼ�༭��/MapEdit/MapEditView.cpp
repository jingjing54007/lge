// MapEditView.cpp : implementation of the CMapEditView class
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MapEditDoc.h"
#include "MapEditView.h"


#include "MainFrm.h"
#include "SampleView.h"
#include "NpcStateDlg.h"
#include "ZoomDlg.h"
#include "ToolsBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditView

IMPLEMENT_DYNCREATE(CMapEditView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditView, CScrollView)
	//{{AFX_MSG_MAP(CMapEditView)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditView construction/destruction

CMapEditView::CMapEditView()
{
	

	
}

CMapEditView::~CMapEditView()
{

}

BOOL CMapEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView drawing

void CMapEditView::OnDraw(CDC* pDC)
{
	CMapEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rc;

	if(pDoc->m_scenein ||pDoc->m_mapbmpin)
	{
		SIZE size;
		size.cx=pDoc->m_mapSize.cx;
		size.cy=pDoc->m_mapSize.cy;
		SetScrollSizes(MM_TEXT, size);
		pDC->BitBlt(0,0,size.cx,size.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}
}

void CMapEditView::OnInitialUpdate()
{
	CMapEditDoc* pDoc = GetDocument();
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	
	
	sizeTotal.cx =pDoc->m_mapSize.cx;
	sizeTotal.cy =pDoc->m_mapSize.cy;
	
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView printing

BOOL CMapEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapEditView diagnostics

#ifdef _DEBUG
void CMapEditView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditDoc* CMapEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditDoc)));
	return (CMapEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapEditView message handlers

BOOL CMapEditView::OnEraseBkgnd(CDC* pDC) 
{
	CMapEditDoc* pDoc = GetDocument();
    CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));

	//if(pDoc->m_mapbmpin ||pDoc->m_scenein)
		//return NULL;
	//else
		pDC->FillRect(&rect, &brush);
	brush.DeleteObject();
	return NULL;		
}

void CMapEditView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMapEditDoc* pDoc = GetDocument();
	CPoint pt;
	CRect rc;
	GetClientRect(&rc);
	pt =point + GetScrollPosition();
	CString strMousePos;
	
	strMousePos.Format("鼠标(X:%d,Y:%d)",pt.x,pt.y);
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();
	pMainFrame->SetMousePosText(strMousePos);
	
	if(pDoc->m_mstate==5 && pDoc->m_state==52)
	{
		CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
		CToolsBar* pView3 = (CToolsBar*)pMainWnd->m_wndSplitter2.GetPane(1,0);
		CString ss;
		ss.Format("X=%d,Y=%d",pt.x,pt.y);
		pView3->m_displaypos.SetWindowText(ss);
	}

	if(pDoc->m_newwupic)
	{
		pDoc->CurDC.BitBlt(pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->BakDC,pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,SRCCOPY);
		

	//	pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
		pDoc->CurDC.BitBlt(pt.x,pt.y-pDoc->m_samSize.cy,pDoc->SampleBm.bmWidth,pDoc->SampleBm.bmHeight,&pDoc->MaskDC,0,0,SRCINVERT);
		pDoc->m_oldpoint=pt;
		InvalidateRect(rc,true);
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CMapEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	
	if(pDoc->m_mstate==1)
	{
		switch(pDoc->m_state)
		{
			case 11:
				{
					AddPoint(pDoc->m_starta,1,0,point+GetScrollPosition());
					pDoc->m_scenechange=true;
					m_save=1;
				}
				break;
			case 12:
				{
					AddPoint(pDoc->m_starta,-1,1,point+GetScrollPosition());
					pDoc->m_scenechange=true;
					m_save=1;
				}
				break;
			case 13:
				{
					if(!pDoc->m_qiehuanstart)
					{
						CQieHuanCode dlg;
						strcpy(dlg.path,pDoc->m_WorkingPath);
						dlg.m_QieHuanCode=10000;
						if(dlg.DoModal()==IDOK)
						{
							AddPoint(pDoc->m_starta,m_qiehuancode,1,point+GetScrollPosition());
							pDoc->m_qiehuanstart=true;
						}
						else
						{
							pDoc->m_mstate=0;
						}
					}
					else
					{
						AddPoint(pDoc->m_starta,m_qiehuancode,1,point+GetScrollPosition());
						pDoc->m_scenechange=true;
						m_save=1;
					}
				}
				break;
		}
	}

	if(pDoc->m_mstate==2)
	{
		switch(pDoc->m_state)
		{
			case 21:    
				MovePoint(point+GetScrollPosition());
				break;
			case 22:
				DelPoint(point+GetScrollPosition());
				break;
			case 23:
				DelArea(point+GetScrollPosition());
				break;
			case 24:
				ChangeAreaAttrib(point+GetScrollPosition());
				break;
			case 25:
				{

				}
				break;
		}

	}
	if(pDoc->m_mstate==3)
	{
		switch(pDoc->m_state)
		{
			case 31:
				AddThing(point+GetScrollPosition());
				break;
			case 32:
				DelThing(point+GetScrollPosition());
				break;
			case 33:
				MoveThingPoint(point+GetScrollPosition());
				break;
			case 34:
				DelThingPoint(point+GetScrollPosition());
				break;
		}
	}
	if(pDoc->m_mstate==4)
	{
		CPoint pt;
		pt=point+GetScrollPosition();
		switch(pDoc->m_state)
		{
			case 41:
				AddNpc(pt);
				break;
			case 42:
				DelNpc(pt);
				break;
			case 43:
				MoveNpcPoint(pt);
				break;
			case 44:
				DelNpcPoint(pt);
				break;
		}	
					
	}
	if(pDoc->m_mstate==5)
	{
		CPoint pt;
		pt=point+GetScrollPosition();
		if(pDoc->m_state==52)
		{
			pDoc->m_myscene.m_position.x=pt.x;
			pDoc->m_myscene.m_position.y=pt.y;
			pDoc->m_mstate=0;
			pDoc->m_state=0;
			pDoc->m_scenechange=true;
			m_save=1;
		}
		
	}

		
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMapEditView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_mstate==1)
	{
		if(pDoc->m_myscene.m_arealist.m_head->m_pointlist.m_count<3)
		{
			if(!pDoc->m_firsthit)
			{
				AfxMessageBox("当前绘制了的点不能构成区域，请继续画点！或者右击鼠标来取消操作！");
				pDoc->m_firsthit=true;
				return;
			}
			else
			{	
				pDoc->m_myscene.m_arealist.Del();
				pDoc->m_firsthit=false;
				//从BakDC中拷贝
				
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
				pDoc->m_mstate=0;
				return;
			}
		
		}
		CPen mypen,*oldpen;
		mypen.CreatePen(PS_SOLID,1,pDoc->m_linecr);
		oldpen=pDoc->CurDC.SelectObject(&mypen);
		pDoc->m_qiehuanstart=false;
		pDoc->m_mstate=0;
		pDoc->m_state=0;
		pDoc->m_starta=false;
		
		pDoc->CurDC.LineTo(pDoc->m_firstpoint);
		InvalidateRect(rc,true);
		pDoc->CurDC.SelectObject(oldpen);
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}
	if(pDoc->m_mstate==2)
	{
		pDoc->m_firsthit=false;
		pDoc->m_mstate=0;
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}

	if(pDoc->m_mstate==3)
	{
		CPoint pt;
		pt=point+GetScrollPosition();
		if(pDoc->m_state==31)
		{
			if(pDoc->m_addstate==0)
			{
				pDoc->CurDC.BitBlt(pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->BakDC,pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,SRCCOPY);
				InvalidateRect(rc,true);
				pDoc->m_mstate=0;
				pDoc->m_state=0;
				pDoc->m_newwupic=false;
				return;
			}
			if(pDoc->m_tempthing.m_cover.m_count<3 && pDoc->m_tempthing.m_cover.m_count!=0)
			{
				AfxMessageBox("物体的遮盖区域不能少于三个点，请重新画区域！");
			
				return;
			}
			else if(pDoc->m_addstate>1)
			{
				pDoc->m_myscene.m_thinglist.Add(pDoc->m_tempthing);
				pDoc->m_scenechange=true;
				m_save=1;
				DrawLine(pDoc->m_oldpoint,pDoc->m_firstpoint,PS_SOLID);
			
				pDoc->m_tempthing.m_cover.ClearList();
			
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
				pDoc->m_newwupic=false;
				pDoc->m_addstate=0;
				return;
			}
		//	pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
		//	pDoc->DrawSceneInDC(&pDoc->CurDC);
			//pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
			pDoc->CurDC.BitBlt(pt.x,pt.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->BakDC,pt.x,pt.y-pDoc->m_samSize.cy,SRCCOPY);
			InvalidateRect(rc,true);
			pDoc->m_addstate=0;
			pDoc->m_newwupic=false;
			pDoc->m_mstate=0;
		}
		if(pDoc->m_state==32 || pDoc->m_state==33 || pDoc->m_state==34)
		{
			pDoc->m_mstate=0;
		}
		
	}
	if(pDoc->m_mstate==4)
	{
		if(pDoc->m_state==41 && (pDoc->m_addstate==1 || pDoc->m_addstate==0))
		{
			pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
			InvalidateRect(rc,true);
		}
		pDoc->m_newwupic=false;
		pDoc->m_mstate=0;
	}
	
	CScrollView::OnRButtonDown(nFlags, point);
}

void CMapEditView::AddPoint(BOOL starta, int statein, int stateout, CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	if(starta)
	{
		pDoc->m_myscene.m_arealist.Add();
		pDoc->m_myscene.m_arealist.m_head->m_statein=statein;
		pDoc->m_myscene.m_arealist.m_head->m_stateout=stateout;
		pDoc->m_myscene.m_arealist.m_head->m_pointlist.Add(pt);
		pDoc->m_scenein=true;
		pDoc->m_starta=false;
		DrawLine(pt,pt,PS_SOLID);
		
		pDoc->m_firstpoint=pDoc->m_oldpoint=pt;
	}
	else
	{
		pDoc->m_myscene.m_arealist.m_head->m_pointlist.Add(pt);
		DrawLine(pDoc->m_oldpoint,pt,PS_SOLID);
		pDoc->m_oldpoint=pt;
	}
}

void CMapEditView::MarkPoint(CPoint pt, int line, COLORREF color)
{
	CRect rc;
	GetClientRect(&rc);
	CMapEditDoc* pDoc = GetDocument();	
	CPen mypen,*oldpen;
	mypen.CreatePen(PS_SOLID,line,color);
   	oldpen=pDoc->CurDC.SelectObject(&mypen);

	pDoc->CurDC.MoveTo(pt+CPoint(-5,-5));
	pDoc->CurDC.LineTo(pt+CPoint(+5,+5));
	pDoc->CurDC.MoveTo(pt+CPoint(+5,-5));
	pDoc->CurDC.LineTo(pt+CPoint(-5,+5));
	pDoc->CurDC.SelectObject(oldpen);
	InvalidateRect(rc,true);
}

void CMapEditView::MyInvalid(POINT fpt, POINT spt, int w, int h)
{
	//fpt为前一个点　，spt为第二个点　，ｗ位图片宽，ｈ位图片高
	POINT temp1,temp2;
	CRect rc;
	if(fpt.x>spt.x || fpt.y<spt.y)
	{
		temp1.x=fpt.x;
		temp1.y=fpt.y-h;
		temp2.x=fpt.x+w;
		temp2.y=spt.y-h;
		rc.SetRect(temp1,temp2);
		InvalidateRect(rc,true);
		temp1.x=spt.x+w;
		temp1.y=spt.y-h;
		temp2.x=fpt.x+w;
		temp2.y=fpt.y;
		rc.SetRect(temp1,temp2);
		InvalidateRect(rc,true);
	}
	if(fpt.x<spt.x || fpt.y>spt.y)
	{
		temp1.x=fpt.x;
		temp1.y=spt.y;
		temp2.x=spt.x+w;
		temp2.y=fpt.y;
		rc.SetRect(temp1,temp2);
		InvalidateRect(rc,true);
		temp1.x=fpt.x;
		temp1.y=fpt.y-h;
		temp2.x=spt.x;
		temp2.y=spt.y;
		rc.SetRect(temp1,temp2);
		InvalidateRect(rc,true);
	}

}

void CMapEditView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMapEditView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMapEditView::Drawtemp(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CDC *dc;
	dc=GetDC();
	CRect rc,rect;
	GetClientRect(&rc);
	rect=rc;
	POINT pt1,pt2;
	pt1=pt;
	pt2.y=pt1.y;
	pt1.y=pt1.y-pDoc->m_sample.GetBmpHeight();
	pt2.x=pt1.x+pDoc->m_sample.GetBmpWidth();
	rc.SetRect(pt1,pt2);
	

	pDoc->m_sample.ShowBmp(dc,rc.left,rc.top,pDoc->m_sample.GetBmpWidth(),pDoc->m_sample.GetBmpHeight(),1,SRCCOPY);
	pt2=pt;
	
	//刷新无效区域
	MyInvalid(pDoc->m_oldpoint,pt2,pDoc->m_sample.GetBmpWidth(),pDoc->m_sample.GetBmpHeight());
	pDoc->m_oldpoint=pt;
}

void CMapEditView::DrawLine(POINT pt1, POINT pt2,int tp)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	CPen mypen,*oldpen;
	mypen.CreatePen(tp,1,pDoc->m_linecr);
	oldpen=pDoc->CurDC.SelectObject(&mypen);
	
	pDoc->CurDC.MoveTo(pt1);
	pDoc->CurDC.LineTo(pt2);
	pDoc->CurDC.Ellipse(pt2.x-3,pt2.y-3,pt2.x+3,pt2.y+3);
	InvalidateRect(rc,true);
	pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	pDoc->CurDC.SelectObject(oldpen);
	
}

void CMapEditView::MovePoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		if(!pDoc->m_firsthit)
		{
			if(!pDoc->m_myscene.m_arealist.FindPoint(pt,5))
			{
				AfxMessageBox("你现在进行的是移动点的操作，但你没有选定区域上的点!!\n\t\t请选定需要移动的点!!!!");
				return;
			}
			else
			{
				CPoint temp;
				temp=pDoc->m_myscene.m_arealist.m_curposi->m_pointlist.m_curposi->mypt;
				MarkPoint(temp,3,RGB(255,255,0));			
				pDoc->m_firsthit=true;
			}
		}
		else
		{
			pDoc->m_myscene.m_arealist.m_curposi->m_pointlist.Changecur(pt);
			pDoc->m_firsthit=false;
			pDoc->m_scenechange=true;
			m_save=1;
			pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
			pDoc->DrawSceneInDC(&pDoc->CurDC);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
			InvalidateRect(rc,true);
		}
	}
}


void CMapEditView::DelPoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		if(!pDoc->m_myscene.m_arealist.FindPoint(pt,5))
			AfxMessageBox("你现在做的是删除点链上点的操作，但你没点击到你想操作的点上!\n或者你还没有载入地图信息!请重新点击!");
		else
		{
			MarkPoint(pDoc->m_myscene.m_arealist.m_curposi->m_pointlist.m_curposi->mypt,3,RGB(255,255,0));
			
			if(MessageBox("你确定要删除选中的点?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
			{
				pDoc->m_myscene.m_arealist.m_curposi->m_pointlist.Delcur();
				pDoc->m_scenechange=true;
				m_save=1;
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
				pDoc->DrawSceneInDC(&pDoc->CurDC);
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
			else
			{
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
		}
	}

}

void CMapEditView::DelArea(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		if(!pDoc->m_myscene.m_arealist.FindPoint(pt,5))
			AfxMessageBox("你还未选定要删除的区域点链上的一点!请选定点链上的一个点；\n\t否则，右击鼠标来取消操作!!!");
		else
		{
			MarkPoint(pDoc->m_myscene.m_arealist.m_curposi->m_pointlist.m_curposi->mypt,3,RGB(255,255,0));
			if(MessageBox("你确定要删除选中区域?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
			{
				pDoc->m_myscene.m_arealist.Delcur();
				pDoc->m_scenechange=true;
				m_save=1;
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
			    pDoc->DrawSceneInDC(&pDoc->CurDC);
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
				InvalidateRect(rc,true); 
			}
			else
			{
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
		}
	}	

}

void CMapEditView::ChangeAreaAttrib(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		if(!pDoc->m_myscene.m_arealist.FindPoint(pt,5))
			AfxMessageBox("你还未选定要改变属性的区域上的任何一点!请选定一个点；\n\t否则，右击鼠标来取消操作!!!");
		else
		{
			if(pDoc->m_daonei!=-1 && pDoc->m_daowai!=-1)
			{
				pDoc->m_myscene.m_arealist.m_curposi->m_statein=pDoc->m_daonei;
				pDoc->m_myscene.m_arealist.m_curposi->m_stateout=pDoc->m_daowai;
				pDoc->m_scenechange=true;
				m_save=1;
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
				pDoc->DrawSceneInDC(&pDoc->CurDC);
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
			else
			{
				AfxMessageBox("还没有选择区域属性！请选择！");
				return;
			}
		}
	}
}

void CMapEditView::AddThing(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_addstate==0 && pDoc->m_newwupic)
	{
		//记录物体图片区域
		pDoc->m_tempthing.m_picarea.left=pt.x;
		pDoc->m_tempthing.m_picarea.bottom=pt.y;
		pDoc->m_tempthing.m_picarea.right=pt.x+pDoc->SampleBm.bmWidth;
		pDoc->m_tempthing.m_picarea.top=pt.y-pDoc->SampleBm.bmHeight;
		pDoc->m_addstate++;
		pDoc->m_newwupic=false;
		pDoc->CurDC.BitBlt(pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->BakDC,pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,SRCCOPY);
		pDoc->TransDraw(&pDoc->CurDC,pt.x,pt.y-pDoc->SampleBm.bmHeight,(byte*)pDoc->SampleBm.bmBits,pDoc->SampleBm.bmWidth,pDoc->SampleBm.bmHeight,pDoc->transcolor);
		InvalidateRect(rc,true);
	}
	else if(pDoc->m_addstate>0)
	{
		//记录物体遮挡区域
		pDoc->m_tempthing.m_cover.Add(pt);
		if(pDoc->m_addstate==1)
		{
			pDoc->m_oldpoint=pDoc->m_firstpoint=pt;
			DrawLine(pDoc->m_oldpoint,pDoc->m_oldpoint,PS_SOLID);
		}
		else
		{
			DrawLine(pDoc->m_oldpoint,pt,PS_SOLID);
			pDoc->m_oldpoint=pt;
		}
			pDoc->m_addstate++;
	}
}

void CMapEditView::DelThing(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);

	if(pDoc->m_myscene.m_thinglist.m_head!=NULL)
	{
		pDoc->m_myscene.m_thinglist.m_curposi=pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_head;
		while(pDoc->m_myscene.m_thinglist.m_curposi!=NULL && !pDoc->m_myscene.m_thinglist.m_curposi->m_cover.FindPoint(pt,5))
		{
			pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_curposi;
			pDoc->m_myscene.m_thinglist.Next();
		}
		if(pDoc->m_myscene.m_thinglist.m_curposi==NULL)
		{
			AfxMessageBox("没有选择要删除物体遮盖区域点链上一点！请选择要删除物体遮盖区域点链上的一点！否则右击鼠标取消操作！");
			return;
		}
		else
		{
			MarkPoint(pDoc->m_myscene.m_thinglist.m_curposi->m_cover.m_curposi->mypt,3,RGB(255,255,0));
			if(MessageBox("你确定要删除选中的物品?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
			{
			//	rc=pDoc->m_myscene.m_thinglist.m_curposi->m_picarea;
				pDoc->m_myscene.m_thinglist.Delcur();
				pDoc->m_scenechange=true;
				m_save=1;
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
				pDoc->DrawSceneInDC(&pDoc->CurDC);
				InvalidateRect(rc,true);
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
			}
			else
			{
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
		}
	}
	else
	{
		AfxMessageBox("场景信息中没有物体信息存在！不能进行这项操作！");
		pDoc->m_mstate=0;
	}
}

void CMapEditView::AddNpc(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);

	CNpcStateDlg dlg;
	if(pDoc->m_addstate==0)
	{
		pDoc->CurDC.BitBlt(pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->BakDC,pDoc->m_oldpoint.x,pDoc->m_oldpoint.y-pDoc->m_samSize.cy,SRCCOPY);
		pDoc->CurDC.BitBlt(pt.x,pt.y-pDoc->m_samSize.cy,pDoc->m_samSize.cx,pDoc->m_samSize.cy,&pDoc->MaskDC,0,0,SRCINVERT);
		InvalidateRect(rc,true);
		pDoc->m_tempnpc.m_facehigh=pDoc->m_samSize.cy;
		pDoc->m_tempnpc.m_facewidth=pDoc->m_samSize.cx;
		pDoc->m_oldpoint.x=pt.x;
		pDoc->m_oldpoint.y=pt.y;
		pDoc->m_addstate++;
		pDoc->m_newwupic=false;
		return;
	}
	if(pDoc->m_addstate==1)
	{
		pDoc->m_tempnpc.m_center.x=pt.x;
		pDoc->m_tempnpc.m_center.y=pt.y;
		pDoc->m_tempnpc.m_conposi.x=pt.x-pDoc->m_oldpoint.x;
		pDoc->m_tempnpc.m_conposi.y=pDoc->m_samSize.cy+pt.y-pDoc->m_oldpoint.y;
		m_x=pt.x;
		m_y=pt.y;
		if(dlg.DoModal()==IDOK)
		{
			pDoc->m_tempnpc.m_autoact[0].m_state=npcstate;
			pDoc->m_tempnpc.m_autoact[0].m_wait=npcstoptime;
			pDoc->m_tempnpc.m_autoact[0].m_pt.x=m_x;
			pDoc->m_tempnpc.m_autoact[0].m_pt.y=m_y;
			pDoc->m_addstate++;
			pDoc->m_scenechange=true;
			m_save=1;
			pDoc->m_oldpoint=pDoc->m_firstpoint=pt;
	
			pDoc->m_linecr=RGB(128,128,255);
			DrawLine(pt,pt,PS_DASH);
			return;
		}
		else
		{
			pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
			InvalidateRect(rc,true);
			pDoc->m_scenechange=pDoc->m_scenechange | false;
			m_save=0;
			pDoc->m_mstate=0;
			return;
		}
	}
	if(pDoc->m_addstate > 1)
	{
		if(pDoc->m_addstate > 9)
		{
			AfxMessageBox("只能加九个点！");
	//		pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_state=npcstate;
	//		pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_wait=npcstoptime;
	//		pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.x=m_x;
	//		pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.y=m_y;

			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_state=-1;
			pDoc->m_myscene.m_npclist.Add(pDoc->m_tempnpc);
			pDoc->m_mstate=0;
			pDoc->m_addstate=0;
		//	DrawLine(pDoc->m_oldpoint,pt,PS_DASH);
			DrawLine(pDoc->m_oldpoint,pDoc->m_firstpoint,PS_DASH);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
			return;
		}
		
		m_x=pt.x;
		m_y=pt.y;
		if(dlg.DoModal()==IDOK)
		{
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_state=npcstate;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_wait=npcstoptime;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.x=m_x;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.y=m_y;
			pDoc->m_addstate++;
			DrawLine(pDoc->m_oldpoint,pt,PS_DASH);
			pDoc->m_oldpoint=pt;
			return;
		}
		else
		{
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_state=npcstate;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_wait=npcstoptime;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.x=m_x;
			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate-1].m_pt.y=m_y;

			pDoc->m_tempnpc.m_autoact[pDoc->m_addstate].m_state=-1;
			pDoc->m_myscene.m_npclist.Add(pDoc->m_tempnpc);
			pDoc->m_mstate=0;
			pDoc->m_addstate=0;
			DrawLine(pDoc->m_oldpoint,pt,PS_DASH);
			DrawLine(pt,pDoc->m_firstpoint,PS_DASH);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
		}
	}
}

void CMapEditView::DelNpc(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);

	
	pDoc->m_myscene.m_npclist.m_curposi=pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_head;
	
	while(pDoc->m_myscene.m_npclist.m_curposi!=NULL)
	{
		int i=0;
		while(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state!=-1)
		{
			if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
			{
				MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
				if(MessageBox("你确定要删除选中的人物?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
				{
					pDoc->m_myscene.m_npclist.Delcur();
					pDoc->m_scenechange=true;
					m_save=1;
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
					pDoc->DrawSceneInDC(&pDoc->CurDC);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY); //问题
					InvalidateRect(rc,true);
					return;
				}
				else
				{
					MessageBox("0");
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}

			}
			else
				i++;
		}
		if(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state==-1)
		{
			if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
			{
				MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
				if(MessageBox("你确定要删除选中的人物?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
				{
					pDoc->m_myscene.m_npclist.Delcur();
					pDoc->m_scenechange=true;
					m_save=1;
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
					pDoc->DrawSceneInDC(&pDoc->CurDC);
					pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}
				else
				{
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}
			}
		}
		pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_curposi;
		pDoc->m_myscene.m_npclist.Next();
	}
	AfxMessageBox("没有选择人物自动行走路线点链上的一点，请选择，否则右击鼠标取消操作！");
}

void CMapEditView::MoveThingPoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	
	if(pDoc->m_myscene.m_thinglist.m_head!=NULL)
	{
		if(!pDoc->m_firsthit)
		{
			pDoc->m_myscene.m_thinglist.m_curposi=pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_head;
			while(pDoc->m_myscene.m_thinglist.m_curposi!=NULL && !pDoc->m_myscene.m_thinglist.m_curposi->m_cover.FindPoint(pt,5))
			{
				pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_curposi;
				pDoc->m_myscene.m_thinglist.Next();
			}
			if(pDoc->m_myscene.m_thinglist.m_curposi==NULL)
			{
				AfxMessageBox("没有选择遮盖区域点链上一点！请选择遮盖区域点链上的一点！\n\t否则右击鼠标取消操作！");
				return;
			}
			else
			{
				CPoint temp;
				temp=pDoc->m_myscene.m_thinglist.m_curposi->m_cover.m_curposi->mypt;
				MarkPoint(temp,3,RGB(255,255,0));			
				pDoc->m_firsthit=true;
			}
		}
		else
		{
					
			pDoc->m_myscene.m_thinglist.m_curposi->m_cover.Changecur(pt);
			pDoc->m_firsthit=false;
			pDoc->m_scenechange=true;
			m_save=1;
			pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
			pDoc->DrawSceneInDC(&pDoc->CurDC);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
			InvalidateRect(rc,true);

		}
	}
}

void CMapEditView::DelThingPoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	if(pDoc->m_myscene.m_thinglist.m_head!=NULL)
	{
		pDoc->m_myscene.m_thinglist.m_curposi=pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_head;
		while(pDoc->m_myscene.m_thinglist.m_curposi!=NULL && !pDoc->m_myscene.m_thinglist.m_curposi->m_cover.FindPoint(pt,5))
		{
			pDoc->m_myscene.m_thinglist.m_preposi=pDoc->m_myscene.m_thinglist.m_curposi;
			pDoc->m_myscene.m_thinglist.Next();
		}
		if(pDoc->m_myscene.m_thinglist.m_curposi==NULL)
		{
			AfxMessageBox("没有选择遮盖区域点链上一点！请选择遮盖区域点链上的一点！\n\t否则右击鼠标取消操作！");
			return;
		}
		else
		{
			MarkPoint(pDoc->m_myscene.m_thinglist.m_curposi->m_cover.m_curposi->mypt,3,RGB(255,255,0));
			if(MessageBox("你确定要删除选中的点?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
			{
				pDoc->m_myscene.m_thinglist.m_curposi->m_cover.Delcur();
				pDoc->m_scenechange=true;
				m_save=1;
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
				pDoc->DrawSceneInDC(&pDoc->CurDC);
				pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);				
			}
			else
			{
				pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
				InvalidateRect(rc,true);
			}
		}
	}
}

void CMapEditView::MoveNpcPoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);
	
	if(pDoc->m_myscene.m_npclist.m_head!=NULL)
	{
		if(!pDoc->m_firsthit)
		{
			pDoc->m_myscene.m_npclist.m_curposi=pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_head;
	
			while(pDoc->m_myscene.m_npclist.m_curposi!=NULL)
			{
				int i=0;
				while(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state!=-1)
				{
					if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
					{
						MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
						pDoc->m_firsthit=true;
						pDoc->m_npautopos=i;
						return;
					}
					else
						i++;
				}
				if(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state==-1)
				{
					if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
						(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
					{
						MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
						pDoc->m_firsthit=true;
						pDoc->m_npautopos=i;
						return;
					}
					
				}
				pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_curposi;
				pDoc->m_myscene.m_npclist.Next();
			}
			AfxMessageBox("没有选择人物自动行走路线点链上的一点，请选择，否则右击鼠标取消操作！");
			return;
		}
		else
		{
			if(pDoc->m_npautopos==0)
			{
				pDoc->m_myscene.m_npclist.m_curposi->m_center=pt;
				pDoc->m_myscene.m_npclist.m_curposi->m_autoact[pDoc->m_npautopos].m_pt=pt;
			}
			else
			{
				pDoc->m_myscene.m_npclist.m_curposi->m_autoact[pDoc->m_npautopos].m_pt=pt;
			}
			pDoc->m_firsthit=false;
			pDoc->m_scenechange=true;
			m_save=1;
			pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
			pDoc->DrawSceneInDC(&pDoc->CurDC);
			pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
			InvalidateRect(rc,true);
		}
	}
}

void CMapEditView::DelNpcPoint(CPoint pt)
{
	CMapEditDoc* pDoc = GetDocument();
	CRect rc;
	GetClientRect(&rc);

	pDoc->m_myscene.m_npclist.m_curposi=pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_head;
	
	while(pDoc->m_myscene.m_npclist.m_curposi!=NULL)
	{
		int i=0;
		while(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state!=-1)
		{
			if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
			{
				MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
				if(MessageBox("你确定要删除选中的点?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
				{
					if(i==0)
					{
						pDoc->m_myscene.m_npclist.m_curposi->m_center=pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_pt;
					}
					while(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state!=-1)
					{
						pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i]=pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1];
						i++;
					}
					
					pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_state=-1;
					pDoc->m_scenechange=true;
					m_save=1;
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
					pDoc->DrawSceneInDC(&pDoc->CurDC);
					pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}
				else
				{
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}

			}
			else
				i++;
		}
		if(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i+1].m_state==-1)
		{
			if((pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x<pt.x+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.x>pt.x-5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y<pt.y+5) &&
				(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt.y>pt.y-5))
			{
				MarkPoint(pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_pt,3,RGB(255,255,0));
				if(MessageBox("你确定要删除选中的点?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON1)==IDYES)
				{
					pDoc->m_myscene.m_npclist.m_curposi->m_autoact[i].m_state=-1;
					pDoc->m_scenechange=true;
					m_save=1;
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->memDC,0,0,SRCCOPY);
					pDoc->DrawSceneInDC(&pDoc->CurDC);
					pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}
				else
				{
					pDoc->CurDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->BakDC,0,0,SRCCOPY);
					InvalidateRect(rc,true);
					return;
				}
			}
		}
		
		pDoc->m_myscene.m_npclist.m_preposi=pDoc->m_myscene.m_npclist.m_curposi;
		pDoc->m_myscene.m_npclist.Next();
	}
	AfxMessageBox("没有选择人物自动行走路线点链上的一点，请选择，否则右击鼠标取消操作！");
}


