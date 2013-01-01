#if !defined(AFX_EDITEVENTDLG_H__8D0DEF36_7F1C_49AE_A287_B914DC034A45__INCLUDED_)
#define AFX_EDITEVENTDLG_H__8D0DEF36_7F1C_49AE_A287_B914DC034A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEventDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditEventDlg dialog

class CEditEventDlg : public CDialog
{
// Construction
public:
	int m_nOld;
	CEditEventDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditEventDlg)
	enum { IDD = IDD_DIALOG_EVENTEDIT };
	CString	m_strEventDescribe;
	int		m_nEventID;
	CString	m_strExpression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditEventDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEVENTDLG_H__8D0DEF36_7F1C_49AE_A287_B914DC034A45__INCLUDED_)
