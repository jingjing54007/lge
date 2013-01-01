#if !defined(AFX_ZOOMDLG_H__12D21AA4_44C3_451E_AEB5_66D0C4DF2CD6__INCLUDED_)
#define AFX_ZOOMDLG_H__12D21AA4_44C3_451E_AEB5_66D0C4DF2CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog
extern float m_zoomout,m_zoomin;
extern BOOL m_modeltest;

class CZoomDlg : public CDialog
{
// Construction
public:
	CZoomDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL m_far,m_near;

// Dialog Data
	//{{AFX_DATA(CZoomDlg)
	enum { IDD = IDD_DIALOG_ZOOM };
	CButton	m_test;
	float	m_minvalue;
	float	m_maxvalue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonCancel();
	afx_msg void OnSetfocusEditZoomin();
	afx_msg void OnSetfocusEditZoomout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDLG_H__12D21AA4_44C3_451E_AEB5_66D0C4DF2CD6__INCLUDED_)
