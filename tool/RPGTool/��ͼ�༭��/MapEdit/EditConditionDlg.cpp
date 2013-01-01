// EditConditionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "EditConditionDlg.h"
#include "scene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CConditionList *m_pConditionList;

/////////////////////////////////////////////////////////////////////////////
// CEditConditionDlg dialog


CEditConditionDlg::CEditConditionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConditionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConditionDlg)
	m_strConDescribe = _T("");
	m_nConID = 0;
	//}}AFX_DATA_INIT
}


void CEditConditionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConditionDlg)
	DDX_Text(pDX, IDC_EDIT_CONDISCRIBE, m_strConDescribe);
	DDV_MaxChars(pDX, m_strConDescribe, 50);
	DDX_Text(pDX, IDC_EDIT_CONID, m_nConID);
	DDV_MinMaxInt(pDX, m_nConID, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConditionDlg, CDialog)
	//{{AFX_MSG_MAP(CEditConditionDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConditionDlg message handlers

void CEditConditionDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(strlen(m_strConDescribe)>0)
	{
	int flag=0;
	CCondition *lp=m_pConditionList->m_head;
	for(int i=0;i<m_pConditionList->m_nConditionNum && flag==0;i++,lp=lp->lpNext)
		if(m_nConID==lp->m_nID && m_nConID!=m_nOld)	
			flag=1;
	if(flag)
		AfxMessageBox("输入的ID与现有的重复，请重新输入!");
	else	
	CDialog::OnOK();
	}
}

BOOL CEditConditionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText("条件编辑");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
