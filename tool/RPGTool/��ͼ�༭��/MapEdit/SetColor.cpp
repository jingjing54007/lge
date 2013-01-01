// SetColor.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "SetColor.h"

#include "MainFrm.h"
#include "MapEditDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetColor dialog


CSetColor::CSetColor(CWnd* pParent /*=NULL*/)
	: CDialog(CSetColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetColor)
	m_areaatrib = _T("");
	m_rgbb = 0;
	m_rgbg = 0;
	m_rgbr = 0;
	//}}AFX_DATA_INIT
	
}


void CSetColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetColor)
	DDX_Control(pDX, IDC_BUTTON_ADD, m_add);
	DDX_Text(pDX, IDC_EDIT_AREALEIXING, m_areaatrib);
	DDV_MaxChars(pDX, m_areaatrib, 20);
	DDX_Text(pDX, IDC_EDIT_B, m_rgbb);
	DDV_MinMaxInt(pDX, m_rgbb, 0, 255);
	DDX_Text(pDX, IDC_EDIT_G, m_rgbg);
	DDV_MinMaxInt(pDX, m_rgbg, 0, 255);
	DDX_Text(pDX, IDC_EDIT_R, m_rgbr);
	DDV_MinMaxInt(pDX, m_rgbr, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetColor, CDialog)
	//{{AFX_MSG_MAP(CSetColor)
	ON_BN_CLICKED(IDC_RADIO_AREACOLOR, OnRadioAreacolor)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetColor message handlers



void CSetColor::OnRadioAreacolor() 
{
	CDC *dc;
	dc=GetDC();
	
	CRect rc,rect;
	GetClientRect(&rc);
	rect=rc;
	CColorDialog mycolordlg;
	mycolordlg.DoModal();
	color=mycolordlg.GetColor();
	
	rect.left=rc.left+120;
	rect.right=rc.right-100;
	rect.top=rc.top+90;
	rect.bottom=rc.bottom-20;
	CBrush brush;
	brush.CreateSolidBrush(color);
	dc->FillRect(&rect, &brush);
	brush.DeleteObject();
	ReleaseDC(dc);
}

void CSetColor::OnButtonAdd() 
{

   // UpdateData(true);
	m_rgbr=234;
	UpdateData(false);
/*	CFile file;
	char path[256];
	strcpy(path, pDoc->m_WorkingPath);
	strcat(path,"\\system.ini");
	
	if(!file.Open(path,CFile::modeReadWrite,NULL))
		AfxMessageBox("打开文件失败！");
*/	
}

void CSetColor::OnClose() 
{
	ExitProcess(0);

	CDialog::OnClose();
}
