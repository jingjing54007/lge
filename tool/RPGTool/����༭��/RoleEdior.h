// RoleEdior.h : main header file for the ROLEEDIOR application
//

#if !defined(AFX_ROLEEDIOR_H__66C80396_1998_4BDD_80B2_DFFA0D81CE80__INCLUDED_)
#define AFX_ROLEEDIOR_H__66C80396_1998_4BDD_80B2_DFFA0D81CE80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoleEdiorApp:
// See RoleEdior.cpp for the implementation of this class
//

class CRoleEdiorApp : public CWinApp
{
public:
	CRoleEdiorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoleEdiorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRoleEdiorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLEEDIOR_H__66C80396_1998_4BDD_80B2_DFFA0D81CE80__INCLUDED_)
