#if !defined(AFX_SYSCONFIGURE_H__CCDDDD79_8DE9_466F_8A13_40DABD193EAC__INCLUDED_)
#define AFX_SYSCONFIGURE_H__CCDDDD79_8DE9_466F_8A13_40DABD193EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysConfigure.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysConfigure dialog
#include "MyArray.h"
class CSysConfigure : public CDialog
{
// Construction
public:


	void GetExFilePath(char *filepath);
	CSysConfigure(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysConfigure)
	enum { IDD = IDD_DIALOG_CONFIGURE };
	CSpinButtonCtrl	m_spinR;
	CSpinButtonCtrl	m_spinG;
	CSpinButtonCtrl	m_spinB;
	CSpinButtonCtrl	m_SpinR;
	CSpinButtonCtrl	m_SpinG;
	CSpinButtonCtrl	m_SpinB;
	CComboBox	m_ComboCtrl;
	int		m_AttribCode;
	int		m_BValue;
	int		m_GValue;
	int		m_RValue;
	int		m_Bvalue;
	int		m_Gvalue;
	int		m_Rvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysConfigure)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CItemList  m_attlist;
	// Generated message map functions
	//{{AFX_MSG(CSysConfigure)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusComboAreaattib();
	afx_msg void OnChangeColorR();
	afx_msg void OnChangeColorG();
	afx_msg void OnChangeColorB();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSCONFIGURE_H__CCDDDD79_8DE9_466F_8A13_40DABD193EAC__INCLUDED_)
