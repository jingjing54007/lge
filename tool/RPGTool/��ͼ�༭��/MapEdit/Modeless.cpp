// Modeless.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "Modeless.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog


CModeless::CModeless(CWnd* pParent /*=NULL*/)
	: CDialog(CModeless::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModeless)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(Create(CModeless::IDD,pParent))
	{
		ShowWindow(SW_SHOW);
	}
}


void CModeless::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModeless)
	DDX_Control(pDX, IDC_SLIDER, m_LeftMargin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModeless, CDialog)
	//{{AFX_MSG_MAP(CModeless)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeless message handlers

BOOL CModeless::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LeftMargin.SetRangeMin(0);
	m_LeftMargin.SetRangeMax(50);
	m_LeftMargin.SetPos(0);
	pos=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModeless::OnOK() 
{
	ShowWindow(SW_HIDE);	
	CDialog::OnOK();
}
