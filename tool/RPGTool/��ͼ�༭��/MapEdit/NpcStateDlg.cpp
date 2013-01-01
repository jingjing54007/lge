// NpcStateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "NpcStateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpcStateDlg dialog


CNpcStateDlg::CNpcStateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNpcStateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNpcStateDlg)
	m_standTime = 0;
	//}}AFX_DATA_INIT
}


void CNpcStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNpcStateDlg)
	DDX_Control(pDX, IDC_COMBO_STATE, m_ComboState);
	DDX_Control(pDX, IDC_POINT, m_position);
	DDX_Text(pDX, IDC_EDIT_TIME, m_standTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNpcStateDlg, CDialog)
	//{{AFX_MSG_MAP(CNpcStateDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_STATE, OnSelchangeComboState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNpcStateDlg message handlers

BOOL CNpcStateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString ss;
	ss.Format("当前点场景坐标：x=%d ,y=%d",m_x,m_y);
	m_position.SetWindowText(ss);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNpcStateDlg::OnOK() 
{
	UpdateData(true);
	npcstoptime=m_standTime;
	CDialog::OnOK();
}

void CNpcStateDlg::OnCancel() 
{
	UpdateData(true);
	npcstoptime=m_standTime;
	CDialog::OnCancel();
}

void CNpcStateDlg::OnSelchangeComboState() 
{
	npcstate=m_ComboState.GetCurSel();
	
}
