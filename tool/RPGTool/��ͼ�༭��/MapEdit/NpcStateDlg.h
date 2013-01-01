#if !defined(AFX_NPCSTATEDLG_H__F80CB7EC_CBE5_4E53_801F_00118ACDE69A__INCLUDED_)
#define AFX_NPCSTATEDLG_H__F80CB7EC_CBE5_4E53_801F_00118ACDE69A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpcStateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpcStateDlg dialog
extern int m_x,m_y,npcstate,npcstoptime;
class CNpcStateDlg : public CDialog
{
// Construction
public:
	CNpcStateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNpcStateDlg)
	enum { IDD = IDD_DIALOG_NPC };
	CComboBox	m_ComboState;
	CStatic	m_position;
	int		m_standTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpcStateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNpcStateDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NPCSTATEDLG_H__F80CB7EC_CBE5_4E53_801F_00118ACDE69A__INCLUDED_)
