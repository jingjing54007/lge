// RoleEdiorDlg.h : header file
//

#if !defined(AFX_ROLEEDIORDLG_H__9559E07E_8C31_47D5_A9E0_7B9E08944662__INCLUDED_)
#define AFX_ROLEEDIORDLG_H__9559E07E_8C31_47D5_A9E0_7B9E08944662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thing.h"
#include "piclib.h"
#include "AnimatorDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRoleEdiorDlg dialog

class CRoleEdiorDlg : public CDialog
{
// Construction
public:
	void ClearAll();
	void FileClose();
	BOOL AskSave();
	void DataSaved();
	void DataMod();
	bool IsMod;
	void UpdateUI();
	void OnChaSave();
	int GetID();
	CString strCurrFileName;
	CString strCurrPathName;
	CNpc m_Npc;
	int m_PicID[10];
	CNpcList * m_pNpcList;
	CNameLib m_Namelib;
	CRoleEdiorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRoleEdiorDlg)
	enum { IDD = IDD_ROLEEDIOR_DIALOG };
	CButton	m_Ani;
	CComboBox	m_Pic;
	CComboBox	m_Viewport;
	CComboBox	m_Status;
	CSpinButtonCtrl	m_Spin7;
	CSpinButtonCtrl	m_Spin6;
	CSpinButtonCtrl	m_Spin5;
	CSpinButtonCtrl	m_Spin4;
	CSpinButtonCtrl	m_Spin3;
	CSpinButtonCtrl	m_Spin2;
	CSpinButtonCtrl	m_Spin1;
	CListBox	m_ListView;
	int	m_Def;
	int	m_Exp;
	int	m_ID;
	int	m_Level;
	int	m_Life;
	CString	m_Name;
	int	m_Speed;
	int	m_Attack;
	int		m_Function;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoleEdiorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
  bool  m_bDoClose;

	// Generated message map functions
	//{{AFX_MSG(CRoleEdiorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg BOOL OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnChaNew();
	afx_msg void OnSelchangeListview();
	afx_msg void OnChangeEditName();
	afx_msg void OnSelchangeComboPic();
	afx_msg void OnSelchangeComboStatusViewport();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnCheckAni();
	afx_msg void OnChaDel();
	afx_msg void OnChangeData();
	afx_msg void OnButtonFollow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnFileclose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLEEDIORDLG_H__9559E07E_8C31_47D5_A9E0_7B9E08944662__INCLUDED_)
