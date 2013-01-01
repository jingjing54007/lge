// EditEventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "EditEventDlg.h"
#include "scene.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CEventList *m_pEventList;
extern BOOL GrammarCheck(CString s);
extern BOOL CheckCharacer(CString s);

/////////////////////////////////////////////////////////////////////////////
// CEditEventDlg dialog


CEditEventDlg::CEditEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditEventDlg)
	m_strEventDescribe = _T("");
	m_nEventID = 0;
	m_strExpression = _T("");
	//}}AFX_DATA_INIT
}


void CEditEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditEventDlg)
	DDX_Text(pDX, IDC_EDIT_EVENTDISCRIBE, m_strEventDescribe);
	DDV_MaxChars(pDX, m_strEventDescribe, 50);
	DDX_Text(pDX, IDC_EDIT_EVENTID, m_nEventID);
	DDV_MinMaxInt(pDX, m_nEventID, 0, 99);
	DDX_Text(pDX, IDC_EDIT_EXPRESSION, m_strExpression);
	DDV_MaxChars(pDX, m_strExpression, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditEventDlg, CDialog)
	//{{AFX_MSG_MAP(CEditEventDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEventDlg message handlers

void CEditEventDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
if(strlen(m_strEventDescribe)>0 && strlen(m_strExpression))
{
	if(!CheckCharacer(m_strExpression))
	{
		AfxMessageBox("逻辑表达式中有非法字符!");
		return;
	}
	if(!GrammarCheck(CheckCondition(m_strExpression,0)))
	{
		AfxMessageBox("逻辑表达式中有语法错误或者非法条件ID!");
		return;
	}
	CheckCondition(m_strExpression,1);

	int flag=0;
	CEvent *lp=m_pEventList->m_head;
	for(int i=0;i<m_pEventList->m_nEventNum && flag==0;i++,lp=lp->lpNext)
		if(m_nEventID==lp->m_nID && m_nEventID!=m_nOld)	
			flag=1;
	if(flag)
		AfxMessageBox("输入的ID与现有的重复，请重新输入!");
	else	
		CDialog::OnOK();
}
}

BOOL CEditEventDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText("事件编辑");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
