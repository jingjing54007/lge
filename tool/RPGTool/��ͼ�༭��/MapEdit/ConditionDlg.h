#if !defined(AFX_CONDITIONDLG_H__89ACFF1A_4599_4921_8C56_ECD6CF02C339__INCLUDED_)
#define AFX_CONDITIONDLG_H__89ACFF1A_4599_4921_8C56_ECD6CF02C339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConditionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConditionDlg dialog

class CConditionDlg : public CDialog
{
// Construction
public:
	void clear();
	void Refresh();
	int m_nEventSelect;
	int m_nConSelect;
	int m_nEventItem;
	int m_nConItem;
	CConditionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConditionDlg)
	enum { IDD = IDD_DIALOG_CONDITION };
	CListCtrl	m_ListEvent;
	CListCtrl	m_ListCondition;
	CString	m_ConditionDescribe;
	CString	m_EventDescribe;
	CString	m_Expression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConditionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConditionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonConok();
	afx_msg void OnButtonEventok();
	afx_msg void OnClickListCondition(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonCondel();
	afx_msg void OnClickListEvent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonEventdel();
	afx_msg void OnButtonEventedit();
	afx_msg void OnButtonConedit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDITIONDLG_H__89ACFF1A_4599_4921_8C56_ECD6CF02C339__INCLUDED_)
