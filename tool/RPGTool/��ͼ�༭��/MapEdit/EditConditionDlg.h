#if !defined(AFX_EDITCONDITIONDLG_H__8BD321B4_0A5F_4E92_888D_5C65812CE24F__INCLUDED_)
#define AFX_EDITCONDITIONDLG_H__8BD321B4_0A5F_4E92_888D_5C65812CE24F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConditionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConditionDlg dialog

class CEditConditionDlg : public CDialog
{
// Construction
public:
	int m_nOld;
	CEditConditionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConditionDlg)
	enum { IDD = IDD_DIALOG_CONEDIT };
	CString	m_strConDescribe;
	int		m_nConID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConditionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditConditionDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONDITIONDLG_H__8BD321B4_0A5F_4E92_888D_5C65812CE24F__INCLUDED_)
