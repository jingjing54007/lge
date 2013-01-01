#if !defined(AFX_MODELESS_H__55D4D1B7_4844_4E69_9B69_E1378406874F__INCLUDED_)
#define AFX_MODELESS_H__55D4D1B7_4844_4E69_9B69_E1378406874F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modeless.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog

class CModeless : public CDialog
{
// Construction
public:
	CModeless(CWnd* pParent = NULL);   // standard constructor
	int pos;
	CView* pointer;
// Dialog Data
	//{{AFX_DATA(CModeless)
	enum { IDD = IDD_MODALESS };
	CSliderCtrl	m_LeftMargin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeless)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModeless)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESS_H__55D4D1B7_4844_4E69_9B69_E1378406874F__INCLUDED_)
