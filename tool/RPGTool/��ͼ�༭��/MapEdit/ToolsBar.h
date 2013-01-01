#if !defined(AFX_TOOLSBAR_H__2007281F_B4D2_47A1_AD8B_6357F954B8A4__INCLUDED_)
#define AFX_TOOLSBAR_H__2007281F_B4D2_47A1_AD8B_6357F954B8A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolsBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolsBar form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "ZoomDlg.h"
extern float m_zoomin,m_zoomout;
extern int m_qiehuancode;
#include "QieHuanCode.h"
class CToolsBar : public CFormView
{
protected:
	CToolsBar();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CToolsBar)

// Form Data
public:
	//{{AFX_DATA(CToolsBar)
	enum { IDD = IDD_FORMVIEW };
	CComboBox	m_ChooseCtrl;
	CStatic	m_displaypos;
	CStatic	m_displayzoom;
	CComboBox	m_AddRenCtrl;
	CComboBox	m_AddWuCtrl;
	CComboBox	m_DaoWaiCtrl;
	CComboBox	m_DaoNeiCtrl;
	COLORREF transcr;
	float	m_zoom;
	int m_pos;
	CString	m_strChoose;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CToolsBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CToolsBar)
	afx_msg void OnRadioKezou();
	afx_msg void OnRadioDao();
	afx_msg void OnRadioQiehuan();
	afx_msg void OnRadioMove();
	afx_msg void OnRadioDelpoint();
	afx_msg void OnRadioDelarea();
	afx_msg void OnRadioAddwu();
	afx_msg void OnRadioDelwu();
	afx_msg void OnRadioAddren();
	afx_msg void OnRadioDelren();
	afx_msg void OnRadioChange();
	afx_msg void OnSelchangeComboWu();
	afx_msg void OnSelchangeComboDaonei();
	afx_msg void OnSelchangeComboDaowai();
	afx_msg void OnSelchangeComboRen();
	afx_msg void OnButtonOrgpos();
	afx_msg void OnButtonZoom();
	afx_msg void OnRadioDelrenpoint();
	afx_msg void OnRadioDelwupoint();
	afx_msg void OnRadioMoverenpoint();
	afx_msg void OnRadioMovewupoint();
	afx_msg void OnButtonDlg();
	afx_msg void OnRadioDlg();
	afx_msg void OnButtonCondition();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLSBAR_H__2007281F_B4D2_47A1_AD8B_6357F954B8A4__INCLUDED_)
