#if !defined(AFX_SET_H__06D34820_17C0_42D9_991B_D18FD630B230__INCLUDED_)
#define AFX_SET_H__06D34820_17C0_42D9_991B_D18FD630B230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CSet dialog
class CSet : public CDialog
{
// Construction
public:
	CSet(CWnd* pParent = NULL);   // standard constructor	
	bool blc_com;
	bool blc_hum;	
	bool wht_com;
	bool wht_hum;
	bool full_screen;
// Dialog Data
	//{{AFX_DATA(CSet)
	enum { IDD = IDD_DIALOG_SET };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSet)	
	afx_msg void OnRadioComWhite();
	afx_msg void OnRadioHumBlack();
	afx_msg void OnRadioHumWhite();
	afx_msg void OnRadioComBlack();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCheckFullscreen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_H__06D34820_17C0_42D9_991B_D18FD630B230__INCLUDED_)
