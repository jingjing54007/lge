// QieHuanCode.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "QieHuanCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQieHuanCode dialog


CQieHuanCode::CQieHuanCode(CWnd* pParent /*=NULL*/)
	: CDialog(CQieHuanCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQieHuanCode)
	m_QieHuanCode = 0;
	//}}AFX_DATA_INIT
}


void CQieHuanCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQieHuanCode)
	DDX_Control(pDX, IDC_COMBO_QIEHUANSELECT, m_SceneCode);
	DDX_Text(pDX, IDC_EDIT_QIEHUANCODE, m_QieHuanCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQieHuanCode, CDialog)
	//{{AFX_MSG_MAP(CQieHuanCode)
	ON_CBN_SELCHANGE(IDC_COMBO_QIEHUANSELECT, OnSelchangeComboQiehuanselect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQieHuanCode message handlers

BOOL CQieHuanCode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	strcat(path,"\\maps\\scenelib.txt");
	ifstream in(path);
	if(in)
	{			
		while(!in.eof())
		{
			in.getline(m_name,20);
			m_SceneCode.AddString(m_name);
		}
	}
	in.close();
	m_num=-1;
	m_qiehuancode=m_QieHuanCode;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQieHuanCode::OnOK() 
{
	UpdateData(true);
	if(m_num==-1)
	{
		AfxMessageBox("没有选择切换到那个场景!");
		return;
	}
	else
	{
		m_qiehuancode=m_QieHuanCode;
	}
	CDialog::OnOK();
}

void CQieHuanCode::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CQieHuanCode::OnSelchangeComboQiehuanselect() 
{
	m_num=m_SceneCode.GetCurSel();
	m_QieHuanCode=m_qiehuancode+m_num;
	UpdateData(false);
}
