#if !defined(AFX_SYSDLG_H__69AF31DA_08CF_42FB_939F_B81CEEB95CB9__INCLUDED_)
#define AFX_SYSDLG_H__69AF31DA_08CF_42FB_939F_B81CEEB95CB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000
// SYSDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSYSDLG dialog
#include "MyArray.h"

class CSYSDLG : public CDialog
{
// Construction
public:
	void ColorLook();
	BOOL m_create;
	BOOL m_change;
	char m_name[20];
	Item  myitem;
	void GetExFilePath(char* filepath);
	CItemList  m_attrlist;
	CSYSDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSYSDLG)
	enum { IDD = IDD_DIALOG_SYS };
	CButton	m_Change;
	CButton	m_Add;
	CSpinButtonCtrl	m_SpinCode;
	CSpinButtonCtrl	m_SpinR;
	CSpinButtonCtrl	m_SpinG;
	CSpinButtonCtrl	m_SpinB;
	CComboBox	m_ComboCtrl;
	int		m_BValue;
	int		m_GValue;
	int		m_RValue;
	int		m_AttribCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSYSDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSYSDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeColorR();
	afx_msg void OnSetfocusColorR();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditchangeComboAttribName();
	afx_msg void OnSetfocusComboAttribName();
	afx_msg void OnChangeColorG();
	afx_msg void OnChangeColorB();
	afx_msg void OnPaint();
	afx_msg void OnKillfocusComboAttribName();
	afx_msg void OnKillfocusEditAttribCode();
	afx_msg void OnKillfocusColorR();
	afx_msg void OnKillfocusColorG();
	afx_msg void OnKillfocusColorB();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonSave();
	afx_msg void OnSelchangeComboAttribName();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSDLG_H__69AF31DA_08CF_42FB_939F_B81CEEB95CB9__INCLUDED_)
