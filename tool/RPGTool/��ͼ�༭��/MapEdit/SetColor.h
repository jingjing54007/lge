#if !defined(AFX_SETCOLOR_H__BEDAB833_ED36_4242_AEE3_8934AB4E90F5__INCLUDED_)
#define AFX_SETCOLOR_H__BEDAB833_ED36_4242_AEE3_8934AB4E90F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetColor.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CSetColor dialog


class CSetColor : public CDialog
{
// Construction
public:
	CSetColor(CWnd* pParent = NULL);   // standard constructor
	COLORREF color;
	


// Dialog Data
	//{{AFX_DATA(CSetColor)
	enum { IDD = IDD_DIALOG_COLOR };
	CButton	m_add;
	CString	m_areaatrib;
	int		m_rgbb;
	int		m_rgbg;
	int		m_rgbr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetColor)
	afx_msg void OnRadioAreacolor();
	afx_msg void OnButtonAdd();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCOLOR_H__BEDAB833_ED36_4242_AEE3_8934AB4E90F5__INCLUDED_)
