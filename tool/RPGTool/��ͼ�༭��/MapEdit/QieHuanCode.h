#if !defined(AFX_QIEHUANCODE_H__B186F130_A40E_4C76_A44E_BDDEA41B51B6__INCLUDED_)
#define AFX_QIEHUANCODE_H__B186F130_A40E_4C76_A44E_BDDEA41B51B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QieHuanCode.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CQieHuanCode dialog
#include <iostream.h>
#include <fstream.h>
extern int m_qiehuancode;
class CQieHuanCode : public CDialog
{
// Construction
public:
	char path[256],m_name[20];
	int m_num;	
	CQieHuanCode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQieHuanCode)
	enum { IDD = IDD_DIALOG_QIEHUAN };
	CComboBox	m_SceneCode;
	int		m_QieHuanCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQieHuanCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQieHuanCode)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboQiehuanselect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QIEHUANCODE_H__B186F130_A40E_4C76_A44E_BDDEA41B51B6__INCLUDED_)
