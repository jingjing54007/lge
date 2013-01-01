#if !defined(AFX_EDITDLG_H__04D84BC0_C95A_11D3_AFB7_E4EF5948B152__INCLUDED_)
#define AFX_EDITDLG_H__04D84BC0_C95A_11D3_AFB7_E4EF5948B152__INCLUDED_

//#include "scene.h"	// Added by ClassView
//#include "scene.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	int m_nConSelect;
	int m_nNum;
	int m_nConItem;
	void MyPaint();
	int FillCombo();
	int m_nItem;
	char m_name[20];
	int m_nSelFace;
	char m_WorkingPath[256];
	CEditDlg(CWnd* pParent = NULL);   // standard constructor
/*
	CBitmap bmp;
	CBitmap *oldBmp;
	CDC dcMemory;
	HBITMAP hBitmap;
*/
// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_DIALOG_DLG };
	CListCtrl	m_ListDlg;
	CListBox	m_FaceList;
	CListBox	m_StationCtrl;
	CButton	m_CtrlSpeaker;
	CButton	m_SpeakerCtrl;
	CString	m_strDlg;
	int		m_nNpcDlg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonStation();
	afx_msg void OnButtonStadelete();
	afx_msg void OnSelchangeListStation();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonStaedit();
	afx_msg void OnSelchangeListFace();
	afx_msg void OnRadioNpc();
	afx_msg void OnRadioMain();
	afx_msg void OnSelchangeListShow();
	afx_msg void OnClickListDlg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__04D84BC0_C95A_11D3_AFB7_E4EF5948B152__INCLUDED_)
