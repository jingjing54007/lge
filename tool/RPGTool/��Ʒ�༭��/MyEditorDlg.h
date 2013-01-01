// MyEditorDlg.h : header file

//

#if !defined(AFX_MYEDITORDLG_H__8767AB35_6768_4E5D_9311_EC33D8A76599__INCLUDED_)
#define AFX_MYEDITORDLG_H__8767AB35_6768_4E5D_9311_EC33D8A76599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyEditorDlg dialog

#include <iostream.h>
#include <fstream.h>
#include "Thing.h"
#include "DIB.h"
#include "piclib.h"



class CMyEditorDlg : public CDialog
{
// Construction
public:
	CMyEditorDlg(CWnd* pParent = NULL);	// standard constructor
     DIB m_dib;
	 CThingList m_thingList; 
	 CThing m_thing;
	 CNameLib m_nameLib;
// Dialog Data
	//{{AFX_DATA(CMyEditorDlg)
	enum { IDD = IDD_MYEDITOR_DIALOG };
	CSpinButtonCtrl	m_ctrlFunSpin;
	CButton	m_ctrlVisible;
	CButton	m_ctrlActive;
	CListBox	m_ctrlPicList;
	CListBox	m_ctrlSthList;
	CString	m_strName;
	int		m_intPicID;
	int		m_intSthID;
	int		m_intFunction;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeSthList();
	afx_msg void OnDelButton();
	afx_msg void OnSelchangePicList();
	afx_msg void OnHelpButton();
	afx_msg void OnModifyButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkPicList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDITORDLG_H__8767AB35_6768_4E5D_9311_EC33D8A76599__INCLUDED_)
