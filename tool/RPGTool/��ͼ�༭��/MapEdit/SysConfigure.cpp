// SysConfigure.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "SysConfigure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysConfigure dialog


CSysConfigure::CSysConfigure(CWnd* pParent /*=NULL*/)
	: CDialog(CSysConfigure::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysConfigure)
	m_AttribCode = 0;
	m_BValue = 0;
	m_GValue = 0;
	m_RValue = 0;
	m_Bvalue = 0;
	m_Gvalue = 0;
	m_Rvalue = 0;
	//}}AFX_DATA_INIT
}


void CSysConfigure::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysConfigure)
	DDX_Control(pDX, IDC_SPIN_R, m_spinR);
	DDX_Control(pDX, IDC_SPIN_G, m_spinG);
	DDX_Control(pDX, IDC_SPIN_B, m_spinB);
	DDX_Control(pDX, IDC_COMBO_AREAATTIB, m_ComboCtrl);
	DDX_Text(pDX, IDC_EDIT_ATTRIBCODE, m_AttribCode);
	DDX_Text(pDX, IDC_COLOR_B, m_Bvalue);
	DDV_MinMaxInt(pDX, m_Bvalue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_G, m_Gvalue);
	DDV_MinMaxInt(pDX, m_Gvalue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_R, m_Rvalue);
	DDV_MinMaxInt(pDX, m_Rvalue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysConfigure, CDialog)
	//{{AFX_MSG_MAP(CSysConfigure)
	ON_CBN_SETFOCUS(IDC_COMBO_AREAATTIB, OnSetfocusComboAreaattib)
	ON_EN_CHANGE(IDC_COLOR_R, OnChangeColorR)
	ON_EN_CHANGE(IDC_COLOR_G, OnChangeColorG)
	ON_EN_CHANGE(IDC_COLOR_B, OnChangeColorB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysConfigure message handlers

BOOL CSysConfigure::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char path[256];
	CFile file;
	GetExFilePath(path);
	strcat(path,"\\system.ini");
	
	ifstream in;
	in.open(path,ios::nocreate|ios::in|ios::binary);
	if(in)
	{
		m_attlist.read(in);
		in.close();
		::SetWindowText(GetSafeHwnd(),"修改配置文件");
	}
	else
	{
		::SetWindowText(GetSafeHwnd(),"创建配置文件");
	}
	m_spinR.SetRange(0,255);
	m_spinG.SetRange(0,255);
	m_spinB.SetRange(0,255);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSysConfigure::GetExFilePath(char *filepath)
{
    CString ExePath;
	int num;
	GetModuleFileName(GetModuleHandle("mapedit.exe"), filepath, 255);
	ExePath.Format("%s",filepath);// 此时filename中为应用程序的路径+文件名称

	num=ExePath.ReverseFind('\\');
	ExePath=ExePath.Left(num);// 此时ExePath中为应用程序的路径

	strcpy(filepath, ExePath);
}



void CSysConfigure::OnSetfocusComboAreaattib() 
{
/*	CRect rect,rc;
	GetClientRect(&rect);
	rc=rect;
	rc.left=rect.right/2-10;
	rc.top=rect.bottom/3+20;
	rc.right=rect.right-112;
	rc.bottom=rect.bottom-74;
	CBrush brush;
	
	CClientDC dlgDC(this);

	brush.CreateSolidBrush(RGB(0,0,0));
	dlgDC.FillRect(&rc, &brush);
	brush.DeleteObject();	
	m_RValue=0;
	m_GValue=0;
	m_BValue=0;
	UpdateData(false); */
}




void CSysConfigure::OnChangeColorR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CRect rect,rc;
 	GetClientRect(&rect);
 	rc=rect;
 	rc.left=rect.right/2-10;
 	rc.top=rect.bottom/3+20;
 	rc.right=rect.right-112;
 	rc.bottom=rect.bottom-74;
 	CBrush brush;
	
	CClientDC dlgDC(this);
 	UpdateData(true);
 	brush.CreateSolidBrush(RGB(m_Rvalue,m_Gvalue,m_Bvalue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
	
}

void CSysConfigure::OnChangeColorG() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CRect rect,rc;
 	GetClientRect(&rect);
 	rc=rect;
 	rc.left=rect.right/2-10;
 	rc.top=rect.bottom/3+20;
 	rc.right=rect.right-112;
 	rc.bottom=rect.bottom-74;
 	CBrush brush;
	
	CClientDC dlgDC(this);
 	UpdateData(true);
 	brush.CreateSolidBrush(RGB(m_Rvalue,m_Gvalue,m_Bvalue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
	
}

void CSysConfigure::OnChangeColorB() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CRect rect,rc;
 	GetClientRect(&rect);
 	rc=rect;
 	rc.left=rect.right/2-10;
 	rc.top=rect.bottom/3+20;
 	rc.right=rect.right-112;
 	rc.bottom=rect.bottom-74;
 	CBrush brush;
	
	CClientDC dlgDC(this);
 	UpdateData(true);
 	brush.CreateSolidBrush(RGB(m_Rvalue,m_Gvalue,m_Bvalue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
	
}
