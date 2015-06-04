// ConFive.h : main header file for the CONFIVE application
//

#if !defined(AFX_CONFIVE_H__C5712372_61F2_4256_AC9B_B96A9224AD2A__INCLUDED_)
#define AFX_CONFIVE_H__C5712372_61F2_4256_AC9B_B96A9224AD2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CConFiveApp:
// See ConFive.cpp for the implementation of this class
//

class CConFiveApp : public CWinApp
{
public:
	CConFiveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConFiveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CConFiveApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIVE_H__C5712372_61F2_4256_AC9B_B96A9224AD2A__INCLUDED_)
