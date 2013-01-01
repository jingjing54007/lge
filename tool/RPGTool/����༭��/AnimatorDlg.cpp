// AnimatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoleEdior.h"
#include "AnimatorDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TimerID 1
#define TimerRate 10

extern CAnimatorDlg* g_pCAnimatorDlg;
/////////////////////////////////////////////////////////////////////////////
// CAnimatorDlg dialog


CAnimatorDlg::CAnimatorDlg(LPCTSTR lpszFileName, CWnd* pParent, int framenum, int framefrom, int frameto, int framespeed)
	: CDialog(CAnimatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(Create(CAnimatorDlg::IDD, pParent))
	{
		if(lstrlen(lpszFileName)!=0 )
		{
			CFile file;
			file.Open(lpszFileName , CFile::modeRead);
			m_DIB.Read(file);
			file.Close();
			m_Framenum   = framenum;
			m_FrameFrom  = framefrom;
			m_FrameTo    = frameto;
			m_FrameSpeed = framespeed;
			
			m_CurrFrame  = m_FrameFrom;
			m_FrameSpeed = m_FrameSpeed;
			m_Height = m_DIB.Height() / 8;
			m_Width  = m_DIB.Width() / m_Framenum;
			bPaint = true;
		}
		else
		{
			m_Height = 100;
			m_Width  = 100;
			bPaint = false;
		}
		bPlay = true;
		IsMoved = false;
		SetAnimatorWindowPlacement();
		ShowWindow(SW_SHOW);
	}
	else OnClose();
}


void CAnimatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimatorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimatorDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimatorDlg)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimatorDlg message handlers

void CAnimatorDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	ReleaseAll();
}

void CAnimatorDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if(bPaint)
	{
		CRect rcClient, rcDIB;
		GetClientRect(&rcClient);

		rcDIB.top    = 0;
		rcDIB.left   = m_CurrFrame * m_Width;
		rcDIB.right  = rcDIB.left + m_Width;
		rcDIB.bottom = m_Height;
		HDC hdc;
		hdc = dc.GetSafeHdc();
		m_DIB.Paint(hdc, &rcClient, &rcDIB);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CAnimatorDlg::SetAnimatorWindowPlacement()
{
	//设置动画窗口大小,紧靠主窗口右上
	//窗口最大为1/4屏幕
	if(IsMoved) return;
	int width, height;

	WINDOWPLACEMENT lpwndpl, lpParentwndpl;
	this->GetParent()->GetWindowPlacement(&lpParentwndpl);
	GetWindowPlacement(&lpwndpl);
	lpwndpl.showCmd = lpParentwndpl.showCmd;
	lpwndpl.rcNormalPosition.top  = lpParentwndpl.rcNormalPosition.top;
	lpwndpl.rcNormalPosition.left = lpParentwndpl.rcNormalPosition.right;
	if(m_Width > GetSystemMetrics(SM_CXSCREEN)/2 || m_Height > GetSystemMetrics(SM_CYSCREEN)*3/4)
	{
		if(m_Width > GetSystemMetrics(SM_CXSCREEN)/2)
		{
			width  = GetSystemMetrics(SM_CXSCREEN)/2;
			height = m_Height * width / m_Width;
			if(height > GetSystemMetrics(SM_CYSCREEN)*3/4)
			{
				 height = GetSystemMetrics(SM_CYSCREEN)*3/4;
				 width  = m_Width * height / m_Height;
			}
		}
		if(m_Height > GetSystemMetrics(SM_CYSCREEN)*3/4)
		{
			 height = GetSystemMetrics(SM_CYSCREEN)*3/4;
			 width  = m_Width * height / m_Height;
			 if(width > GetSystemMetrics(SM_CXSCREEN)/2)
			 {
				width  = GetSystemMetrics(SM_CXSCREEN)/2;
				height = m_Height * width / m_Width;
			 }
		}
		lpwndpl.rcNormalPosition.bottom = lpwndpl.rcNormalPosition.top + height;
		lpwndpl.rcNormalPosition.right  = lpwndpl.rcNormalPosition.left + width;
		
	}
	else
	{
		lpwndpl.rcNormalPosition.bottom = lpwndpl.rcNormalPosition.top + m_Height;
		lpwndpl.rcNormalPosition.right  = lpwndpl.rcNormalPosition.left + m_Width;
	}
	SetWindowPlacement(&lpwndpl);
	this->GetParent()->SetActiveWindow();
	IsMoved = false;
}

void CAnimatorDlg::ReleaseAll()
{
	KillTimer(TimerID);
	delete this;
	g_pCAnimatorDlg = NULL;
}

BOOL CAnimatorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(TimerID, TimerRate, NULL);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
DWORD oldtime = GetTickCount();
void CAnimatorDlg::OnTimer(UINT nIDEvent) 
{
	if(bPlay && bPaint)
	{
		DWORD nowtime = GetTickCount() ;
		if(nowtime > oldtime + (DWORD)(1000/m_Framenum - m_FrameSpeed))
		{
			oldtime = nowtime;
			if(m_CurrFrame < m_FrameTo-1)
			{
				m_CurrFrame++;
			}
			else 
			{
				m_CurrFrame = m_FrameFrom;
			}
			CClientDC clientDC(this);
			CRect rcClient, rcDIB;
			GetClientRect(&rcClient);

			rcDIB.top    = 0;
			rcDIB.left   = m_CurrFrame * m_Width;
			rcDIB.right  = rcDIB.left + m_Width;
			rcDIB.bottom = m_Height;
			HDC hdc;
			hdc = clientDC.GetSafeHdc();
			m_DIB.Paint(hdc, &rcClient, &rcDIB);
		}
	}
	CDialog::OnTimer(nIDEvent);
}



void CAnimatorDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	IsMoved = true;
}
