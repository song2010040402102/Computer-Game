// ConFiveView.cpp : implementation of the CConFiveView class
//

#include "stdafx.h"
#include "ConFive.h"

#include "ConFiveDoc.h"
#include "ConFiveView.h"
#include "Set.h"
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define BOARD_MARGI 10
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConFiveView
int id;
int BoardSize=15;
extern CSet set;
CSearch search;
CProgressCtrl progress;
IMPLEMENT_DYNCREATE(CConFiveView, CView)

BEGIN_MESSAGE_MAP(CConFiveView, CView)
	//{{AFX_MSG_MAP(CConFiveView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_OUTPUTALLLINEINFO, OnOutputalllineinfo)
	ON_COMMAND(ID_READCM, OnReadcm)
	ON_COMMAND(ID_SAVECM, OnSavecm)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SEARCHRECORD, OnSearchrecord)
	ON_UPDATE_COMMAND_UI(ID_SEARCHRECORD, OnUpdateSearchrecord)
	ON_COMMAND(ID_START, OnStart)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConFiveView construction/destruction
void UniquePointHistory(vector<point> &MoveList)
{
	vector<point>::iterator iterp1,iterp2;
	for(iterp1=MoveList.begin();iterp1!=MoveList.end();iterp1++)
	{
		for(iterp2=iterp1+1;iterp2!=MoveList.end();iterp2++)
		{
			if(iterp1->x==iterp2->x &&iterp1->y==iterp2->y)
			{
				MoveList.erase(iterp1);
				break;
			}
		}
	}
}
void OutputPointHistory()
{
	char ch;
	vector<point>::iterator iterp;	
	FILE *F1=fopen("d:\\PointHistory.txt","w");	
	for(iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
	{
		ch=(iterp->side==0)?'B':'W';
		fprintf(F1,"%c,%d,%d\n",ch,iterp->x,iterp->y);
	}	
	fclose(F1);
}
void UpdatePointHistory()
{	
	vector<point>::iterator iterp;	
	for(iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
	{
		if(search.board[iterp->x][iterp->y]==EMPTY)
		{
			search.PointHistory.erase(iterp);	
		}			
	}	
	UniquePointHistory(search.PointHistory);
	id=search.PointHistory.size();
}
UINT ComToCom(LPVOID pParam)
{
	if(search.EndGame==true)return 0;
	int x,y;
	while(1)
	{
		if(search.player==BLACK)
		{
			search.CurPoint=search.ComputerMove(BLACK);
			search.CurPoint.side=BLACK;
			x=search.CurPoint.x;
			y=search.CurPoint.y;
			search.board[x][y]=BLACK;
		}			
		else if(search.player==WHITE)
		{
			search.CurPoint=search.ComputerMove(WHITE);
			search.CurPoint.side=WHITE;
			x=search.CurPoint.x;
			y=search.CurPoint.y;
			search.board[x][y]=WHITE;
		}
		else
			continue;
		search.PointHistory.push_back(search.CurPoint);
		search.UpdateLine(BLACK,search.CurPoint);
		search.UpdateLine(WHITE,search.CurPoint);
		search.player=NEXT(search.player);
		((CFrameWnd*)AfxGetMainWnd())->Invalidate(FALSE);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_MOVE),NULL,SND_RESOURCE);
		UpdatePointHistory();
		OutputPointHistory();
		if(search.WinLose(BLACK)==true)
		{
			AfxMessageBox("Black Win!");
			search.EndGame=true;
			break;
		}
		else if(search.WinLose(WHITE)==true)
		{
			AfxMessageBox("White Win!");
			search.EndGame=true;
			break;
		}
		else
			continue;
	}
	return 0;
}
UINT ComToPer(LPVOID pParam)
{	
	if(search.EndGame==true)return 0;

	int x,y;
	if(set.blc_com==true)  //电脑执黑
	{
		search.CurPoint=search.ComputerMove(BLACK);
		search.CurPoint.side=BLACK;
		x=search.CurPoint.x;
		y=search.CurPoint.y;
		search.board[x][y]=BLACK;
	}
	else  //电脑执白
	{
		search.CurPoint=search.ComputerMove(WHITE);
		search.CurPoint.side=WHITE;
		x=search.CurPoint.x;
		y=search.CurPoint.y;
		search.board[x][y]=WHITE;
	}
	search.PointHistory.push_back(search.CurPoint);
	search.UpdateLine(BLACK,search.CurPoint);
	search.UpdateLine(WHITE,search.CurPoint); //更新黑白双方的线
	search.player=NEXT(search.player);
	((CFrameWnd*)AfxGetMainWnd())->Invalidate(FALSE);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_MOVE),NULL,SND_RESOURCE);
	UpdatePointHistory();
	OutputPointHistory();
	if(search.WinLose(BLACK)==true)
	{
		AfxMessageBox("Black Win!");
		search.EndGame=true;
	}
	else if(search.WinLose(WHITE)==true)
	{
		AfxMessageBox("White Win!");	
		search.EndGame=true;
	}
	return 0;
}

CConFiveView::CConFiveView()
{
	// TODO: add construction code here
	search.InitGame();
	boardcolor=RGB(193,187,97);
	BlcMin=0;
	BlcSec=0;
	WhtMin=0;
	WhtSec=0;
	BlcTime.Format("BLACK:00:00");
	WhtTime.Format("WHITE:00:00");
	start=false;
}

CConFiveView::~CConFiveView()
{
}

BOOL CConFiveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CConFiveView drawing

/*void CConFiveView::OnDraw(CDC* pDC)
{
	CConFiveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetClientRect(&window);
	pDC->FillRect(&window,&CBrush(RGB(112,113,114)));
	
	int side=(window.Width()>window.Height()?window.Height():window.Width())*0.99;
	board.left=(window.Width()-side)/2;
	board.top=(window.Height()-side)/2;
	board.right=board.left+side;
	board.bottom=board.top+side;
	DrawBoard();	//绘制棋盘
	
	int r=board.Height()/(BoardSize+1)*0.5; //棋子半径
	CDC stoneDC;	
	stoneDC.CreateCompatibleDC(pDC);
	CBitmap stoneBMP;
	stoneBMP.CreateCompatibleBitmap(pDC,r*2,r*2);
	stoneDC.SelectObject(&stoneBMP);
	for(int i=0;i<BoardSize;i++)
	{
		for(int j=0;j<BoardSize;j++)
		{
			int fi=board.left+board.Height()*(i+1)/(BoardSize+1)-r;
			int fj=board.top+board.Height()*(j+1)/(BoardSize+1)-r;
			if(search.board[i][j]==BLACK)
			{
				DrawStone(stoneDC,BLACK,r);				
				pDC->BitBlt(fi,fj,r*2,r*2,&stoneDC,0,0,SRCCOPY);
			}
			else if(search.board[i][j]==WHITE)
			{
				DrawStone(stoneDC,WHITE,r);				
				pDC->BitBlt(fi,fj,r*2,r*2,&stoneDC,0,0,SRCCOPY);
			}			
		}
	}
	stoneBMP.DeleteObject();
	stoneDC.DeleteDC();
}*/
void CConFiveView::DrawTime()
{
	CDC *pDC=GetDC();

	BlcTimer.left=board.left/2;
	BlcTimer.top=board.top;
	BlcTimer.right=board.left;
	BlcTimer.bottom=BlcTimer.Width()/4;

	WhtTimer.left=board.right;
	WhtTimer.top=board.top;
	WhtTimer.right=board.right+BlcTimer.Width();
	WhtTimer.bottom=WhtTimer.Width()/4;

	pDC->FillRect(&BlcTimer,&CBrush(RGB(0,0,0)));
	pDC->FillRect(&WhtTimer,&CBrush(RGB(0,0,0)));

	int h=BlcTimer.Height();
	int w=BlcTimer.Width()/BlcTime.GetLength();
	CFont font;
	font.CreateFont(h,w,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL);
	pDC->SelectObject(&font);
	pDC->SetBkColor(0x00000000);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->TextOut(BlcTimer.left,BlcTimer.top,BlcTime);
	pDC->TextOut(WhtTimer.left,WhtTimer.top,WhtTime);
}
void CConFiveView::OnDraw(CDC* pDC)
{
	CConFiveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetClientRect(&window);

	boardwidth=(window.Width()>window.Height()?window.Height():window.Width());
	boardwidth-=BOARD_MARGI*2;
	if(boardwidth<0) return;

	board.top=(window.Height()-boardwidth)/2;
	board.bottom=board.top+boardwidth;
	board.left=(window.Width()-boardwidth)/2;
	board.right=board.left+boardwidth;	

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC,window.Width(),window.Height());
	CBitmap* pOldBitmap=memDC.SelectObject(&memBitmap);

	// start to draw board
	memDC.FillRect(&window,&CBrush(RGB(0,0,0)));
	memDC.FillRect(&board,&CBrush(boardcolor));

	d=boardwidth/(BoardSize+1);	// stone width

	memDC.SetBkMode(TRANSPARENT);//使输出的字符背景透明。
	CFont font;
	CSize size;
	CString str;
	char num[10],*np=num;
	font.CreateFont(d*2/3,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
	CFont* pOldFont=(CFont*)memDC.SelectObject(&font); 

	int i,x,y;
	if(d>0) 
	{
		//画横竖线
		for(x=0;x<BoardSize;x++) {
			i=board.left+(x+1)*boardwidth/(BoardSize+1);
			memDC.MoveTo(i,board.top+d);
			memDC.LineTo(i,board.bottom-d);
			
			str=('A'+x);//画顶端文字。
			size=memDC.GetTextExtent(str);
			memDC.TextOut(i-size.cx/2,board.top+d-size.cy,str);

			str=CString(_itoa(x,np,10));//画底端文字。
			size=memDC.GetTextExtent(str);
			memDC.TextOut(i-size.cx/2,board.bottom-d,str);
			
		}
		for(y=0;y<BoardSize;y++) {
			i=board.top+(y+1)*boardwidth/(BoardSize+1);
			memDC.MoveTo(board.left+d,i);
			memDC.LineTo(board.right-d,i);

			str=('A'+y);//画左端文字。
			size=memDC.GetTextExtent(str);
			memDC.TextOut(board.left+d-size.cx,i-size.cy/2,str);

			str=CString(_itoa(y,np,10));//画右端文字。
			size=memDC.GetTextExtent(str);
			memDC.TextOut(board.right-d+size.cx/3,i-size.cy/2,str);

		}

		CDC WhiteStoneDC,BlackStoneDC;
		BlackStoneDC.CreateCompatibleDC(pDC);
		WhiteStoneDC.CreateCompatibleDC(pDC);

		CBitmap BlackStoneBmp,WhiteStoneBmp;
		BlackStoneBmp.CreateCompatibleBitmap(pDC,d,d);
		WhiteStoneBmp.CreateCompatibleBitmap(pDC,d,d);

		CBitmap* pOldBlackBmp=BlackStoneDC.SelectObject(&BlackStoneBmp);
		CBitmap* pOldWhiteBmp=WhiteStoneDC.SelectObject(&WhiteStoneBmp);

		DrawStone(d,&WhiteStoneDC,&BlackStoneDC);

		//画棋子。
		int x1,y1;
		unsigned char stone;
		/*for(x=0;x<BoardSize;x++)
			for(y=0;y<BoardSize;y++) */
		for(vector<point>::iterator iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
		{
			x=iterp->x;y=iterp->y;
			x1=board.left+(x+1)*boardwidth/(BoardSize+1);
			y1=board.top+(y+1)*boardwidth/(BoardSize+1);
			stone=search.board[x][y];
			
			if(stone==BLACK)
				memDC.BitBlt(x1-d/2,y1-d/2,d,d,&BlackStoneDC,0,0,SRCCOPY);
			else if(stone==WHITE)
				memDC.BitBlt(x1-d/2,y1-d/2,d,d,&WhiteStoneDC,0,0,SRCCOPY);
		}

		//当前走步显示红十字。
		CPen pen(PS_SOLID,1,RGB(255,0,0));
		CPen *pOldPen=memDC.SelectObject(&pen);	
		x=search.CurPoint.x;
		y=search.CurPoint.y;
		
		if(x>=0 && x<BoardSize && y>=0 && y<BoardSize)//如果是有效的点。
		{
			x1=board.left+(x+0)*boardwidth/(BoardSize+1);
			y1=board.top+(y+0)*boardwidth/(BoardSize+1);
			memDC.MoveTo(x1+d,y1+d*3/4);memDC.LineTo(x1+d,y1+d*5/4);
			memDC.MoveTo(x1+d*3/4,y1+d);memDC.LineTo(x1+d*5/4,y1+d);
		}	
		memDC.SelectObject(pOldPen);				
			
		WhiteStoneDC.SelectObject(pOldWhiteBmp);
		BlackStoneDC.SelectObject(pOldBlackBmp);		
	}
	memDC.SelectObject(pOldFont); 
	pDC->BitBlt(0,0,window.Width(),window.Height(),&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	DrawTime();		

	if(start==false)
	{
		SetTimer(0,1000,NULL);
		if(set.blc_com==true &&set.wht_com==true) //电脑与电脑下
			AfxBeginThread(ComToCom,this);
		else if(set.blc_com==true &&set.wht_hum==true) //电脑落第一子
			AfxBeginThread(ComToPer,this);
		start=true;
	}
}
void CConFiveView::DrawStone(int d, CDC *pWhiteStoneDC, CDC *pBlackStoneDC)
{
	double pixel=0.8,shadow=0.7;
	BOOL Alias=true;

	int red=255-GetRValue(boardcolor);
	int green=255-GetGValue(boardcolor);
	int blue=255-GetBValue(boardcolor);

	COLORREF pb,pw;
	double di,dj,d2=(double)d/2.0-5e-1,r=d2-2e-1,f=sqrt(3.0);
	double x,y,z,xr,xg,hh;
	int g;

	for (int i=0; i<d; i++)
	{
		for (int j=0; j<d; j++)
		{	
			di=i-d2; dj=j-d2;
			hh=r-sqrt(di*di+dj*dj);
			if (hh>=0)
			{	z=r*r-di*di-dj*dj;
			    if (z>0) z=sqrt(z)*f;
			    else z=0;
				x=di; y=dj;
				xr=sqrt(6*(x*x+y*y+z*z));
				xr=(2*z-x+y)/xr;
				if (xr>0.9) xg=(xr-0.9)*10;
				else xg=0;
				if (hh>pixel || !Alias)
				{
					g=(int)(10+10*xr+xg*140);
					pb=(g<<16)|(g<<8)|g;
					g=(int)(200+10*xr+xg*45);
					pw=(g<<16)|(g<<8)|g;
				}
				else
				{	hh=(pixel-hh)/pixel;
					g=(int)(10+10*xr+xg*140);
					double shade;
					if (di-dj<r/3) shade=1;
					else shade=shadow;

					pb=(//(255<<24)|
					    (((int)((1-hh)*g+hh*shade*red))<<16)
						|(((int)((1-hh)*g+hh*shade*green))<<8)
						|((int)((1-hh)*g+hh*shade*blue)));

					g=(int)(200+10*xr+xg*45);

					pw=(//(255<<24)|
					    (((int)((1-hh)*g+hh*shade*red))<<16)
						|(((int)((1-hh)*g+hh*shade*green))<<8)
						|((int)((1-hh)*g+hh*shade*blue)));
				}
			}
			else pb=pw=boardcolor;
			
			pBlackStoneDC->SetPixel(j,i,pb);
			pWhiteStoneDC->SetPixel(j,i,pw);
		}
	}
}
/*void CConFiveView::DrawBoard()
{
	CDC *pDC=GetDC();
	
	pDC->FillRect(&board,&CBrush(RGB(255,255,0)));

	int gap=board.Height()/(BoardSize+1);
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(0,0,0));
	pDC->SelectObject(&pen);
	for(int i=1;i<=BoardSize;i++)  //绘制棋盘横线
	{
		pDC->MoveTo(board.left+gap,board.top+board.Height()*i/(BoardSize+1));
		pDC->LineTo(board.right-gap,board.top+board.Height()*i/(BoardSize+1));
	}	
	for(i=1;i<=BoardSize;i++)  //绘制棋盘竖线
	{
		pDC->MoveTo(board.left+board.Height()*i/(BoardSize+1),board.top+gap);
		pDC->LineTo(board.left+board.Height()*i/(BoardSize+1),board.bottom-gap);
	}  
	pen.DeleteObject();


	CFont font;
	font.CreateFont(gap/2,gap/4,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL);
	pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	CString str;
	for(i=1;i<=BoardSize;i++)  //绘制坐标
	{
		str.Format("%2d",i);
		pDC->TextOut(board.left+board.Height()*i/(BoardSize+1)-gap/4,board.top+gap/4,str); //画顶端数字
		pDC->TextOut(board.left+board.Height()*i/(BoardSize+1)-gap/4,board.bottom-gap*3/4,str); //画底端数字

		pDC->TextOut(board.left+gap/4,board.top+board.Height()*i/(BoardSize+1)-gap/4,str);  //画左端数字
		pDC->TextOut(board.right-gap*3/4,board.top+board.Height()*i/(BoardSize+1)-gap/4,str);  //画右端数字
	}	
	font.DeleteObject();
}

void CConFiveView::DrawStone(CDC &stoneDC,BYTE side,int r)
{
	COLORREF color=(side==BLACK)?0x00000000:0x00ffffff;
	for(int i=0;i<2*r;i++)
	{
		for(int j=0;j<2*r;j++)
		{
			if((i-r)*(i-r)+(j-r)*(j-r)<r*r)
				stoneDC.SetPixel(i,j,color);
			else
				stoneDC.SetPixel(i,j,0x0000ffff);
		}
	}
}*/
/////////////////////////////////////////////////////////////////////////////
// CConFiveView diagnostics

#ifdef _DEBUG
void CConFiveView::AssertValid() const
{
	CView::AssertValid();
}

void CConFiveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CConFiveDoc* CConFiveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConFiveDoc)));
	return (CConFiveDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConFiveView message handlers

void CConFiveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==27)
	{				
		exit(0);
		OnDestroy();
	}
	else
	{		
		if(nChar==38)
		{
			MoveBack(id);
		}
		else if(nChar==40)
		{
			MoveNext(id);
		}
	}	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CConFiveView::MoveBack(int &id)
{
	id--;
	if(id<0)id=0;
	vector<point>::iterator iterp;
	for(iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
	{
		if(iterp-search.PointHistory.begin()<id)
		{
			search.board[iterp->x][iterp->y]=iterp->side;
			search.CurPoint=*iterp;
		}
		else
		{
			search.board[iterp->x][iterp->y]=EMPTY;						
		}				
		search.UpdateLine(BLACK,*iterp);
		search.UpdateLine(WHITE,*iterp);
	}
	Invalidate(FALSE);
}
void CConFiveView::MoveNext(int &id)
{
	id++;
	if(id>search.PointHistory.size())id=search.PointHistory.size();
	vector<point>::iterator iterp;
	for(iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
	{
		if(iterp-search.PointHistory.begin()<id)
		{
			search.board[iterp->x][iterp->y]=iterp->side;			
			search.CurPoint=*iterp;
		}
		else
		{
			search.board[iterp->x][iterp->y]=EMPTY;			
		}
		search.UpdateLine(BLACK,*iterp);
		search.UpdateLine(WHITE,*iterp);
	}
	Invalidate(FALSE);
}
void CConFiveView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default		
	if(search.EndGame==true)return; //游戏结束
	if(search.ComThinking==true)return;  //电脑正在思考
	int x,y;
	int gap=board.Width()/(BoardSize+1);	
	x=(point.x+gap/2-board.left)/gap-1;
	y=(point.y+gap/2-board.top)/gap-1;
				
	if(set.blc_hum==true &&set.wht_hum==true)  //人与人下
		PerToPer(x,y);	
	else if(!(set.blc_com==true &&set.wht_com==true))  //电脑与人下
	{
		HumanMove(x,y);
		AfxBeginThread(ComToPer,this);
	}			
	CView::OnLButtonDown(nFlags, point);
}

void CConFiveView::HumanMove(int x,int y)
{
	if(search.EndGame==true)return;
	
	if(search.player==BLACK)
		search.board[x][y]=BLACK;
	else if(search.player==WHITE)
		search.board[x][y]=WHITE;
	else 
		return;
	search.CurPoint.x=x;
	search.CurPoint.y=y;
	search.CurPoint.side=search.player;
	search.PointHistory.push_back(search.CurPoint);

	search.UpdateLine(BLACK,search.CurPoint);
	search.UpdateLine(WHITE,search.CurPoint);
	search.player=NEXT(search.player);
	Invalidate(FALSE);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_MOVE),NULL,SND_RESOURCE);
	UpdatePointHistory();
	OutputPointHistory();
	if(search.WinLose(BLACK)==true)
	{
		AfxMessageBox("Black Win!");
		search.EndGame=true;
	}
	else if(search.WinLose(WHITE)==true)
	{
		AfxMessageBox("White Win!");	
		search.EndGame=true;
	}
}
void CConFiveView::PerToPer(int x,int y)
{
	if(search.EndGame==true)return;

	if(search.player==BLACK)
	{
		search.board[x][y]=BLACK;		
	}
	else if(search.player==WHITE)
	{
		search.board[x][y]=WHITE;		
	}
	search.CurPoint.x=x;
	search.CurPoint.y=y;
	search.CurPoint.side=search.player;
	search.PointHistory.push_back(search.CurPoint);
	search.UpdateLine(BLACK,search.CurPoint);
	search.UpdateLine(WHITE,search.CurPoint);

	search.player=NEXT(search.player);
	Invalidate(FALSE);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_MOVE),NULL,SND_RESOURCE);
	UpdatePointHistory();
	OutputPointHistory();
	if(search.WinLose(BLACK)==true)
	{
		AfxMessageBox("Black Win!");
		search.EndGame=true;
	}
	else if(search.WinLose(WHITE)==true)
	{
		AfxMessageBox("White Win!");	
		search.EndGame=true;
	}
}
void CConFiveView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==0)
	{
		if(search.player==BLACK)
		{
			BlcSec++;
			if(BlcSec>=60)
			{
				BlcSec=0;
				BlcMin++;
			}			
		}
		if(search.player==WHITE)
		{
			WhtSec++;
			if(WhtSec>=60)
			{
				WhtSec=0;
				WhtMin++;
			}
		}
		BlcTime.Format("BLACK:%2d:%2d",BlcMin,BlcSec);
		WhtTime.Format("WHITE:%2d:%2d",WhtMin,WhtSec);
		InvalidateRect(BlcTimer,FALSE);
		InvalidateRect(WhtTimer,FALSE);		
	}
	CView::OnTimer(nIDEvent);
}

void CConFiveView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);	
	// TODO: Add your message handler code here					
}

void CConFiveView::OnOutputalllineinfo() 
{
	// TODO: Add your command handler code here
	search.OutputAllLineInfo();
}

void CConFiveView::OnReadcm() 
{
	// TODO: Add your command handler code here
	search.InitGame();
	char ch;
	int x,y;
	CString FileName;
	FILE *F1;
	CFileDialog OpenDlg(TRUE,".txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		FileName=OpenDlg.GetFileName();
		F1=fopen(FileName,"r");
		while(!feof(F1))
		{
			fscanf(F1,"%c,%d,%d\n",&ch,&x,&y);
			if(ch=='B')
			{
				search.board[x][y]=BLACK;
				search.CurPoint.side=BLACK;				
			}
			else if(ch=='W')
			{
				search.board[x][y]=WHITE;
				search.CurPoint.side=WHITE;				
			}
			else
				break;
			search.CurPoint.x=x;
			search.CurPoint.y=y;
			search.PointHistory.push_back(search.CurPoint);
			search.UpdateLine(BLACK,search.CurPoint);
			search.UpdateLine(WHITE,search.CurPoint);
		}
		search.player=NEXT(search.CurPoint.side);
		fclose(F1);	
		Invalidate(FALSE);
	}
}

void CConFiveView::OnSavecm() 
{
	// TODO: Add your command handler code here
	char ch;	
	CString FileName;
	vector<point>::iterator iterp;
	FILE *F1;
	CFileDialog OpenDlg(FALSE,".txt","棋谱",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||",NULL);
	if(OpenDlg.DoModal()==IDOK)
	{
		FileName=OpenDlg.GetFileName();
		F1=fopen(FileName,"w");
		for(iterp=search.PointHistory.begin();iterp!=search.PointHistory.end();iterp++)
		{
			ch=(iterp->side==0)?'B':'W';
			fprintf(F1,"%c,%d,%d\n",ch,iterp->x,iterp->y);
		}
		fclose(F1);			
	}
}

int CConFiveView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;	
	// TODO: Add your specialized creation code here	
	progress.Create(PBS_SMOOTH|WS_VISIBLE,CRect(window.left,window.bottom-100,window.right,window.bottom),this,1);	
	return 0;
}

void CConFiveView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GetClientRect(&window);	
	progress.MoveWindow(CRect(window.left,window.bottom-20,window.right,window.bottom),FALSE);
}

void CConFiveView::OnSearchrecord() 
{
	// TODO: Add your command handler code here
	search.SearchRecord^=1;
}

void CConFiveView::OnUpdateSearchrecord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(search.SearchRecord==true?1:0);
}

void CConFiveView::OnStart() 
{
	// TODO: Add your command handler code here	
}

void CConFiveView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	AfxEndThread(0);
}
