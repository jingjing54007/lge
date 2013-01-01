#if !defined(AFX_ANIMATORDLG_H__856C16FE_D0A5_46F7_9069_ED5AA60A6F58__INCLUDED_)
#define AFX_ANIMATORDLG_H__856C16FE_D0A5_46F7_9069_ED5AA60A6F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimatorDlg.h : header file
//
#include "Dib.h"
/////////////////////////////////////////////////////////////////////////////
// CAnimatorDlg dialog

class CAnimatorDlg : public CDialog
{
// Construction
public:
	BOOL IsMoved;
	bool bPlay;
	bool bPaint;
	int m_FrameSpeed;
	UINT_PTR ptr;
	int m_Width;
	int m_Height;
	int m_Framenum;
	int m_FrameFrom;
	int m_FrameTo;
	int m_CurrFrame;
	void ReleaseAll();
	void SetAnimatorWindowPlacement();
	CDib m_DIB;
	CAnimatorDlg(LPCTSTR lpszFileName, CWnd* pParent = NULL, int framenum = 10, int framefrom = 0, int frameto = 10, int framespeed = 10);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimatorDlg)
	enum { IDD = IDD_ANIMATOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnimatorDlg)
	afx_msg void OnClose();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATORDLG_H__856C16FE_D0A5_46F7_9069_ED5AA60A6F58__INCLUDED_)
