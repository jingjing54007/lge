// System.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "System.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystem dialog


CSystem::CSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystem)
	m_AttribCode = 0;
	m_BValue = 0;
	m_GValue = 0;
	m_RValue = 0;
	//}}AFX_DATA_INIT
}


void CSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystem)
	DDX_Control(pDX, IDC_SPIN_R, m_SpinR);
	DDX_Control(pDX, IDC_SPIN_G, m_SpinG);
	DDX_Control(pDX, IDC_SPIN_B, m_SpinB);
	DDX_Control(pDX, IDC_SPIN_ATTRIBCODE, m_SpinCode);
	DDX_Text(pDX, IDC_ATTRIBCODE, m_AttribCode);
	DDX_Text(pDX, IDC_COLOR_B, m_BValue);
	DDV_MinMaxInt(pDX, m_BValue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_G, m_GValue);
	DDV_MinMaxInt(pDX, m_GValue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_R, m_RValue);
	DDV_MinMaxInt(pDX, m_RValue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystem, CDialog)
	//{{AFX_MSG_MAP(CSystem)
	ON_EN_CHANGE(IDC_COLOR_B, OnChangeColorB)
	ON_EN_CHANGE(IDC_COLOR_G, OnChangeColorG)
	ON_EN_CHANGE(IDC_COLOR_R, OnChangeColorR)
	ON_CBN_EDITCHANGE(IDC_COMBO_ATTRIBNAME, OnEditchangeComboAttribname)
	ON_CBN_SELCHANGE(IDC_COMBO_ATTRIBNAME, OnSelchangeComboAttribname)
	ON_EN_CHANGE(IDC_ATTRIBCODE, OnChangeAttribcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystem message handlers

void CSystem::GetExFilePath(char *filepath)
{
	CString ExePath;
	int num;
	GetModuleFileName(GetModuleHandle("mapedit.exe"), filepath, 255);
	ExePath.Format("%s",filepath);// 此时filename中为应用程序的路径+文件名称

	num=ExePath.ReverseFind('\\');
	ExePath=ExePath.Left(num);// 此时ExePath中为应用程序的路径

	strcpy(filepath, ExePath);
}

BOOL CSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char path[256];
	CFile file;
	GetExFilePath(path);
	strcat(path,"\\system.dat");
	
	ifstream in;
	in.open(path,ios::nocreate|ios::in|ios::binary);
	if(in)
	{
		m_attrlist.read(in);
		in.close();
		::SetWindowText(GetSafeHwnd(),"修改配置文件");
	}
	else
	{
		::SetWindowText(GetSafeHwnd(),"创建配置文件");
	}
	m_SpinR.SetRange(0,255);
	m_SpinG.SetRange(0,255);
	m_SpinB.SetRange(0,255);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystem::OnChangeColorB() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CSystem::OnChangeColorG() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CSystem::OnChangeColorR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
//	ColorDisplay();

/*	CRect rect,rc;
 	GetClientRect(&rect);

// 	rc=rect;

 	rc.left=rect.right/2-10;
 	rc.top=rect.bottom/3+20;
 	rc.right=rect.right-112;
 	rc.bottom=rect.bottom-74;
 	CBrush brush;
	
	CClientDC dlgDC(this);

 	UpdateData(true);

 	brush.CreateSolidBrush(RGB(m_RValue,m_GValue,m_BValue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
	*/
	
}

void CSystem::OnEditchangeComboAttribname() 
{
	// TODO: Add your control notification handler code here
	
}

void CSystem::OnSelchangeComboAttribname() 
{
	// TODO: Add your control notification handler code here
	
}

void CSystem::OnChangeAttribcode() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CSystem::ColorDisplay()
{
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
 	brush.CreateSolidBrush(RGB(m_RValue,m_GValue,m_BValue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
}
