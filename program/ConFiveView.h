// ConFiveView.h : interface of the CConFiveView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIVEVIEW_H__28C2D573_0EE4_4A6F_9BC9_BDBAF691ABC6__INCLUDED_)
#define AFX_CONFIVEVIEW_H__28C2D573_0EE4_4A6F_9BC9_BDBAF691ABC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Search.h"


class CConFiveView : public CView
{
protected: // create from serialization only
	CConFiveView();
	DECLARE_DYNCREATE(CConFiveView)

// Attributes
public:
	CConFiveDoc* GetDocument();

// Operations
public:	
	CRect window,board;
	CRect BlcTimer,WhtTimer;
	CString BlcTime,WhtTime;
	int BlcMin,BlcSec,WhtMin,WhtSec;
	int boardwidth,d;	
	bool start;
	COLORREF boardcolor;
	void DrawBoard();
	//void DrawStone(CDC &stoneDC,BYTE side,int r);
	void DrawStone(int d, CDC *pWhiteStoneDC, CDC *pBlackStoneDC);
	void DrawTime();
	void PerToPer(int x,int y);
	void HumanMove(int x,int y);
	void MoveBack(int &id);
	void MoveNext(int &id);	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConFiveView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConFiveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConFiveView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnOutputalllineinfo();
	afx_msg void OnReadcm();
	afx_msg void OnSavecm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSearchrecord();
	afx_msg void OnUpdateSearchrecord(CCmdUI* pCmdUI);
	afx_msg void OnStart();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ConFiveView.cpp
inline CConFiveDoc* CConFiveView::GetDocument()
   { return (CConFiveDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIVEVIEW_H__28C2D573_0EE4_4A6F_9BC9_BDBAF691ABC6__INCLUDED_)
