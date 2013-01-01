// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MainFrm.h"

#include "MapEditView.h"
#include "ToolsBar.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MOUSE,OnUpdateMousePos)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_MOUSE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_save=0;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	UINT x,y;
	x=::GetSystemMetrics(SM_CXSCREEN);
	y=::GetSystemMetrics(SM_CYSCREEN);
	
	m_wndSplitter1.CreateStatic(this,1,2);
	m_wndSplitter1.CreateView(0,0,RUNTIME_CLASS(CMapEditView),CSize(x*3/4,0),pContext);
	m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0,1));
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CSampleView), CSize(0, 2*y/5),pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CToolsBar), CSize(0, 0),pContext);
	return true;
	
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    
	//　设置窗口标准大小为最大化

	cs.style = WS_POPUPWINDOW | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
    cs.y = 0;
    cs.x = 0;
	cs.style &= ~FWS_ADDTOTITLE;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnUpdateMousePos(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}


void CMainFrame::SetMousePosText(CString strText)
{
	// ** Find the index position for ID_INDICATOR_MOUSE
	int nIndex=
		m_wndStatusBar.CommandToIndex(ID_INDICATOR_MOUSE);

		//** Set the pane text to the passed value
		m_wndStatusBar.SetPaneText(nIndex,strText);

		// ** Measure the width of the text
		CWindowDC dc(&m_wndStatusBar);
		CSize sizeText = dc.GetTextExtent(strText);
		
		// ** Set the indicator's width to the text width
		m_wndStatusBar.SetPaneInfo(nIndex,
			ID_INDICATOR_MOUSE,	SBPS_NORMAL,sizeText.cx);
}



void CMainFrame::OnClose() 
{
	if(m_save!=0)
	{
		if(MessageBox("你确定要不保存场景信息退出?    ","警告",MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDNO)
			return;
		else
			CFrameWnd::OnClose();
	}
	else
		CFrameWnd::OnClose();
}
