#if !defined(AFX_SMALLDLG_H__37569000_C9C0_11D3_AFB7_F04D6B10AE52__INCLUDED_)
#define AFX_SMALLDLG_H__37569000_C9C0_11D3_AFB7_F04D6B10AE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmallDlg dialog

class CSmallDlg : public CDialog
{
// Construction
public:
	CSmallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmallDlg)
	enum { IDD = IDD_DIALOG_EDIT };
	CComboBox	m_Speaker;
	CString	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSmallDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLDLG_H__37569000_C9C0_11D3_AFB7_F04D6B10AE52__INCLUDED_)
