#if !defined(AFX_SYSTEM_H__262C505C_D342_47C1_9078_D4FF78A9E1A6__INCLUDED_)
#define AFX_SYSTEM_H__262C505C_D342_47C1_9078_D4FF78A9E1A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// System.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSystem dialog

#include "MyArray.h"

class CSystem : public CDialog
{
// Construction
public:
	void ColorDisplay();
	CItemList m_attrlist;
	void GetExFilePath(char *filepath);
	CSystem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystem)
	enum { IDD = IDD_DIALOG_SYS };
	CSpinButtonCtrl	m_SpinR;
	CSpinButtonCtrl	m_SpinG;
	CSpinButtonCtrl	m_SpinB;
	CSpinButtonCtrl	m_SpinCode;
	int		m_AttribCode;
	int		m_BValue;
	int		m_GValue;
	int		m_RValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystem)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeColorB();
	afx_msg void OnChangeColorG();
	afx_msg void OnChangeColorR();
	afx_msg void OnEditchangeComboAttribname();
	afx_msg void OnSelchangeComboAttribname();
	afx_msg void OnChangeAttribcode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEM_H__262C505C_D342_47C1_9078_D4FF78A9E1A6__INCLUDED_)
