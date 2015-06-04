// Set.cpp : implementation file
//

#include "stdafx.h"
#include "ConFive.h"
#include "Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet dialog

CSet::CSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet)
	//}}AFX_DATA_INIT
	blc_com=false;
	blc_hum=true;	
	wht_com=true;
	wht_hum=false;
	full_screen=false;	
}


void CSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet)
	//}}AFX_DATA_MAP
}
BOOL CSet::OnInitDialog()
{		
	/*GetDlgItem(IDC_RADIO_COM_BLACK)->SetCheck(true);
	GetDlgItem(IDC_RADIO_COM_WHITE)->SetCheck(false);
	GetDlgItem(IDC_RADIO_HUM_BLACK)->SetCheck(false);
	GetDlgItem(IDC_RADIO_HUM_WHITE)->SetCheck(true);*/
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSet, CDialog)
	//{{AFX_MSG_MAP(CSet)		
	ON_BN_CLICKED(IDC_RADIO_BLC_COM, OnRadioComBlack)
	ON_BN_CLICKED(IDC_RADIO_BLC_HUM, OnRadioHumBlack)
	ON_BN_CLICKED(IDC_RADIO_WHT_HUM, OnRadioHumWhite)	
	ON_BN_CLICKED(IDC_RADIO_WHT_COM, OnRadioComWhite)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHECK_FULLSCREEN, OnCheckFullscreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet message handlers

void CSet::OnRadioComBlack() 
{
	// TODO: Add your control notification handler code here
	blc_com=true;
	blc_hum=false;
}

void CSet::OnRadioHumBlack() 
{
	// TODO: Add your control notification handler code here
	blc_com=false;
	blc_hum=true;
}

void CSet::OnRadioComWhite() 
{
	// TODO: Add your control notification handler code here
	wht_com=true;
	wht_hum=false;
}

void CSet::OnRadioHumWhite() 
{
	// TODO: Add your control notification handler code here
	wht_com=false;
	wht_hum=true;
}

int CSet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here	
	return 0;
}

void CSet::OnCheckFullscreen() 
{
	// TODO: Add your control notification handler code here
	full_screen^=1;
}
