// MyEditor.h : main header file for the MYEDITOR application
//

#if !defined(AFX_MYEDITOR_H__FDFE23B1_CA22_4EB8_8D76_9320931CAE5B__INCLUDED_)
#define AFX_MYEDITOR_H__FDFE23B1_CA22_4EB8_8D76_9320931CAE5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyEditorApp:
// See MyEditor.cpp for the implementation of this class
//

class CMyEditorApp : public CWinApp
{
public:
	CMyEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyEditorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDITOR_H__FDFE23B1_CA22_4EB8_8D76_9320931CAE5B__INCLUDED_)
