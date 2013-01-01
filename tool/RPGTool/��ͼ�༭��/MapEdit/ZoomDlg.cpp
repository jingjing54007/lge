// ZoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "ZoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog


CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDlg)
	m_minvalue = 0.0f;
	m_maxvalue = 0.0f;
	//}}AFX_DATA_INIT
}


void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Text(pDX, IDC_EDIT_ZOOMIN, m_minvalue);
	DDX_Text(pDX, IDC_EDIT_ZOOMOUT, m_maxvalue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_EN_SETFOCUS(IDC_EDIT_ZOOMIN, OnSetfocusEditZoomin)
	ON_EN_SETFOCUS(IDC_EDIT_ZOOMOUT, OnSetfocusEditZoomout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers

void CZoomDlg::OnOK() 
{
	UpdateData(true);
	if((m_minvalue > 0.0f && m_minvalue <= m_maxvalue))
		m_zoomin=m_minvalue;
	else
	{
		AfxMessageBox("输入的值不合理！！");
		return;
	}
	
	if((m_minvalue > 0.0f && m_maxvalue >= m_minvalue))
		m_zoomout=m_maxvalue;
	else
	{
		AfxMessageBox("输入的值不合理！！");
		return;
	}

/*	if(!m_far || !m_near)
	{
		AfxMessageBox("请输入远处和近处的缩放比例值！！！");
		return;
	}
*/
	CDialog::OnOK();
}

void CZoomDlg::OnCancel() 
{
//	CDialog::OnCancel();
}



BOOL CZoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_far=false;
	m_near=false;
	
//	if(m_zoomout!=0.0f || m_zoomin!=0.0f)
		
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZoomDlg::OnCancelMode() 
{
//	CDialog::OnCancelMode();
}




void CZoomDlg::OnButtonCancel() 
{
	CDialog::OnCancel();
}

void CZoomDlg::OnSetfocusEditZoomin() 
{
	m_far=true;
	
}

void CZoomDlg::OnSetfocusEditZoomout() 
{
	m_near=true;	
}
