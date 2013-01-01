// SYSDLG.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "SYSDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSYSDLG dialog


CSYSDLG::CSYSDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSYSDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSYSDLG)
	m_BValue = 0;
	m_GValue = 0;
	m_RValue = 0;
	m_AttribCode = 0;
	m_create=false;
	m_change=false;
	//}}AFX_DATA_INIT
}


void CSYSDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSYSDLG)
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_Change);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_Add);
	DDX_Control(pDX, IDC_SPINCODE, m_SpinCode);
	DDX_Control(pDX, IDC_SPIN_R, m_SpinR);
	DDX_Control(pDX, IDC_SPIN_G, m_SpinG);
	DDX_Control(pDX, IDC_SPIN_B, m_SpinB);
	DDX_Control(pDX, IDC_COMBO_ATTRIB_NAME, m_ComboCtrl);
	DDX_Text(pDX, IDC_COLOR_B, m_BValue);
	DDV_MinMaxInt(pDX, m_BValue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_G, m_GValue);
	DDV_MinMaxInt(pDX, m_GValue, 0, 255);
	DDX_Text(pDX, IDC_COLOR_R, m_RValue);
	DDV_MinMaxInt(pDX, m_RValue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_ATTRIB_CODE, m_AttribCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSYSDLG, CDialog)
	//{{AFX_MSG_MAP(CSYSDLG)
	ON_EN_CHANGE(IDC_COLOR_R, OnChangeColorR)
	ON_EN_SETFOCUS(IDC_COLOR_R, OnSetfocusColorR)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_COMBO_ATTRIB_NAME, OnEditchangeComboAttribName)
	ON_CBN_SETFOCUS(IDC_COMBO_ATTRIB_NAME, OnSetfocusComboAttribName)
	ON_EN_CHANGE(IDC_COLOR_G, OnChangeColorG)
	ON_EN_CHANGE(IDC_COLOR_B, OnChangeColorB)
	ON_WM_PAINT()
	ON_CBN_KILLFOCUS(IDC_COMBO_ATTRIB_NAME, OnKillfocusComboAttribName)
	ON_EN_KILLFOCUS(IDC_EDIT_ATTRIB_CODE, OnKillfocusEditAttribCode)
	ON_EN_KILLFOCUS(IDC_COLOR_R, OnKillfocusColorR)
	ON_EN_KILLFOCUS(IDC_COLOR_G, OnKillfocusColorG)
	ON_EN_KILLFOCUS(IDC_COLOR_B, OnKillfocusColorB)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO_ATTRIB_NAME, OnSelchangeComboAttribName)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSYSDLG message handlers

BOOL CSYSDLG::OnInitDialog() 
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
		m_change=true;
		//m_Add.EnableWindow(false);
	}
	else
	{
		::SetWindowText(GetSafeHwnd(),"创建配置文件");
		m_create=true;
		//m_Change.EnableWindow(false);
	}

	m_SpinR.SetRange(0,255);
	m_SpinG.SetRange(0,255);
	m_SpinB.SetRange(0,255);
	m_SpinCode.SetRange(0,9999);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSYSDLG::GetExFilePath(char *filepath)
{
    CString ExePath;
	int num;
	GetModuleFileName(GetModuleHandle("mapedit.exe"), filepath, 255);
	ExePath.Format("%s",filepath);// 此时filename中为应用程序的路径+文件名称

	num=ExePath.ReverseFind('\\');
	ExePath=ExePath.Left(num);// 此时ExePath中为应用程序的路径

	strcpy(filepath, ExePath);
}

void CSYSDLG::OnChangeColorR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_create || m_change)
		ColorLook();
}

void CSYSDLG::OnSetfocusColorR() 
{
	
}

void CSYSDLG::ColorLook()
{
	CRect rect,rc;
 	GetClientRect(&rect);
 	rc=rect;
 	rc.left=rect.right/2-15;
 	rc.top=rect.bottom/3+55;
 	rc.right=rect.right-125;
 	rc.bottom=rect.bottom-45;
 	CBrush brush;
	
	CClientDC dlgDC(this);
 	UpdateData(true);
 	brush.CreateSolidBrush(RGB(m_RValue,m_GValue,m_BValue));
 	dlgDC.FillRect(&rc, &brush);
 	brush.DeleteObject();
}

void CSYSDLG::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CSYSDLG::OnEditchangeComboAttribName() 
{
	
}

void CSYSDLG::OnSetfocusComboAttribName() 
{
	ColorLook();

}

void CSYSDLG::OnChangeColorG() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_create || m_change)
		ColorLook();
	
}

void CSYSDLG::OnChangeColorB() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_create || m_change)
		ColorLook();
	
}

void CSYSDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	ColorLook();
	//将区域名称载入选择框
	if(m_change)
	{
		m_ComboCtrl.ResetContent();
		if(m_attrlist.m_head!=NULL)
		{
			m_attrlist.m_curposi=m_attrlist.m_head;
			for(int i=0;i<m_attrlist.m_count;i++)
			{
				m_ComboCtrl.InsertString(i,m_attrlist.m_curposi->myitem.AttribName);
				m_attrlist.Next();
			}
		}

	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CSYSDLG::OnKillfocusComboAttribName() 
{
	CString ss;
//	UpdateData(true);
	if(GetDlgItemText(IDC_COMBO_ATTRIB_NAME,ss))
	{
	
		for(int i=0;i<ss.GetLength();i++)
		{
			m_name[i]=ss.GetAt(i);
		}
		m_name[i]='\0';
		
		strcpy(myitem.AttribName,m_name);
	//	if(m_attrlist.CheckItem(myitem))
	//	{
	//		AfxMessageBox("现在添加的属性名称已经存在！");
	//		m_ComboCtrl.SetFocus();
	//		return;
	//	}
	//	else
	
	}

}

void CSYSDLG::OnKillfocusEditAttribCode() 
{
	UpdateData(true);
	myitem.AttribCode=m_AttribCode;
//	if(m_attrlist.CheckItem(myitem))
//		AfxMessageBox("现在添加的属性代码已经存在！");
}

void CSYSDLG::OnKillfocusColorR() 
{
	UpdateData(true);
	myitem.Rvalue=m_RValue;
	
}

void CSYSDLG::OnKillfocusColorG() 
{
	UpdateData(true);
	myitem.Gvalue=m_GValue;
}

void CSYSDLG::OnKillfocusColorB() 
{
	UpdateData(true);
	myitem.Bvalue=m_BValue;
//	if(m_attrlist.CheckItem(myitem))
//		AfxMessageBox("现在添加的属性颜色已经存在！");
}

void CSYSDLG::OnButtonAdd() 
{
	UpdateData(true);
	strcpy(myitem.AttribName,m_name);
	myitem.AttribCode=m_AttribCode;
	myitem.Bvalue=m_BValue;
	myitem.Rvalue=m_RValue;
	myitem.Gvalue=m_GValue;
	if(!m_attrlist.CheckItem(myitem,4))
	{
		m_attrlist.Add(myitem);
		m_ComboCtrl.InsertString(-1,m_name);
		m_ComboCtrl.SetFocus();
	}
	else
	{
		AfxMessageBox("已经存在！");
		return;
	}
}

void CSYSDLG::OnButtonSave() 
{
	ofstream out;
	char path[256];
	CFile file;
	GetExFilePath(path);
	strcat(path,"\\system.dat");
	out.open(path,ios::out|ios::binary);
	if(out)
	{
		m_attrlist.write(out);
		out.close();
	}
	else
	{
		AfxMessageBox("存盘失败！");
		out.close();
	}
	OnOK();
}

void CSYSDLG::OnSelchangeComboAttribName() 
{
	m_attrlist.m_curposi=m_attrlist.m_head;
	for(int i=0;i<m_ComboCtrl.GetCurSel();i++)
	{
		m_attrlist.Next();
	}
	m_AttribCode=m_attrlist.m_curposi->myitem.AttribCode;
	m_RValue=m_attrlist.m_curposi->myitem.Rvalue;
	m_GValue=m_attrlist.m_curposi->myitem.Gvalue;
	m_BValue=m_attrlist.m_curposi->myitem.Bvalue;
	UpdateData(false);
	ColorLook();
}

void CSYSDLG::OnButtonExit() 
{
	OnCancel();	
}

void CSYSDLG::OnButtonCancel() 
{
    if(m_attrlist.CheckItem(myitem,4))
		return;
	if(m_attrlist.CheckItem(myitem,1) || m_attrlist.CheckItem(myitem,2) || m_attrlist.CheckItem(myitem,3))
	{
		UpdateData(true);
		strcpy(m_attrlist.m_curposi->myitem.AttribName,m_name);
		m_attrlist.m_curposi->myitem.AttribCode=m_AttribCode;
		m_attrlist.m_curposi->myitem.Bvalue=m_BValue;
		m_attrlist.m_curposi->myitem.Gvalue=m_GValue;
		m_attrlist.m_curposi->myitem.Rvalue=m_RValue;
		ColorLook();
	}
	else
	{
		AfxMessageBox("这是一个全新的属性，请添加！");
	}
}
