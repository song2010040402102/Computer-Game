// ConFiveDoc.h : interface of the CConFiveDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIVEDOC_H__2DEDA8F6_2D65_459C_907F_755625E4AFB2__INCLUDED_)
#define AFX_CONFIVEDOC_H__2DEDA8F6_2D65_459C_907F_755625E4AFB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CConFiveDoc : public CDocument
{
protected: // create from serialization only
	CConFiveDoc();
	DECLARE_DYNCREATE(CConFiveDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConFiveDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConFiveDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConFiveDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIVEDOC_H__2DEDA8F6_2D65_459C_907F_755625E4AFB2__INCLUDED_)
