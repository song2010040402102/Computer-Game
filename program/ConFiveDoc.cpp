// ConFiveDoc.cpp : implementation of the CConFiveDoc class
//

#include "stdafx.h"
#include "ConFive.h"

#include "ConFiveDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConFiveDoc

IMPLEMENT_DYNCREATE(CConFiveDoc, CDocument)

BEGIN_MESSAGE_MAP(CConFiveDoc, CDocument)
	//{{AFX_MSG_MAP(CConFiveDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConFiveDoc construction/destruction

CConFiveDoc::CConFiveDoc()
{
	// TODO: add one-time construction code here

}

CConFiveDoc::~CConFiveDoc()
{
}

BOOL CConFiveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CConFiveDoc serialization

void CConFiveDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CConFiveDoc diagnostics

#ifdef _DEBUG
void CConFiveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CConFiveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConFiveDoc commands
