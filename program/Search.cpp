// Search.cpp: implementation of the CSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConFive.h"
#include "Search.h"
#include <direct.h>
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern int BoardSize;
extern CProgressCtrl progress;
int LineValue[7]={10000,1000,100,90,60,30,0};
increase increasement[4]={1,0,1,-1,0,1,1,1};
inline bool EqualPoint(const point &p1,const point &p2)
{
	if(p1.x==p2.x &&p1.y==p2.y)return true;
	else return false;
}
inline bool ComparePoint(const point &p1,const point &p2)
{
	if(p1.x>p2.x)return true;
	else if(p1.x==p2.x)
	{
		if(p1.y>p2.y)return true;
		else return false;
	}
	else return false;	
}
inline bool ComPointVal0(const point &p1,const point &p2)
{
	return p1.value[0]>p2.value[0];
}
inline bool ComPointVal1(const point &p1,const point &p2)
{
	return p1.value[1]>p2.value[1];
}
void DecreaseXY(int &x,int &y,BYTE dir)
{
	switch(dir)
	{
	case ANGLE0:
		x--;break;
	case ANGLE45:
		x--;y++;break;
	case ANGLE90:
		y--;break;
	case ANGLE135:
		x--;y--;break;
	default:
		break;
	}
}
void IncreaseXY(int &x,int &y,BYTE dir)
{
	switch(dir)
	{
	case ANGLE0:
		x++;break;
	case ANGLE45:
		x++;y--;break;
	case ANGLE90:
		y++;break;
	case ANGLE135:
		x++;y++;break;
	default:
		break;
	}
}
void UniquePoint(vector<point> &MoveList)
{
	int size;
	vector<point>::iterator iterp,lab;	
	sort(MoveList.begin(),MoveList.end(),ComparePoint);
	lab=unique(MoveList.begin(),MoveList.end(),EqualPoint);
	for(iterp=MoveList.begin(),size=0;iterp!=lab;iterp++,size++);	
	MoveList.resize(size);
}
int GetLineID(point pt,BYTE dir)
{
	int x,y,LineID;
	x=pt.x;y=pt.y;
	switch(dir)
	{
	case ANGLE0:
		LineID=y;break;
	case ANGLE45:
		LineID=BoardSize*2+x+y-4;break;
	case ANGLE90:
		LineID=BoardSize+x;break;
	case ANGLE135:
		LineID=BoardSize*2+(BoardSize-4)*2-1+y-x+BoardSize-5;break;
	default:
		LineID=0;break;
	}
	return LineID;
}
point GetStartPoint(point pt,BYTE dir)
{
	int x,y;
	x=pt.x;y=pt.y;
	point start;
	switch(dir)
	{
	case ANGLE0:
		start.x=0;start.y=y;break;
	case ANGLE45:
		if(x+y<BoardSize){start.x=0;start.y=x+y;}
		else{start.x=x-(BoardSize-1-y);start.y=BoardSize-1;}
		break;
	case ANGLE90:
		start.x=x;start.y=0;break;
	case ANGLE135:
		if(x<y){start.x=0;start.y=y-x;}
		else{start.x=x-y;start.y=0;}
		break;
	default:
		start.x=0;start.y=0;break;
	}
	return start;
}
CSearch::CSearch()
{
	InitGame();
}

CSearch::~CSearch()
{

}
void CSearch::InitGame()
{
	DelArrays();
	ComThinking=false;
	SearchRecord=false;	
	player=BLACK;
	LineNum=BoardSize*2+((BoardSize-4)*2-1)*2;
	EndGame=false;
	CreateArrays();
	InitBoard();
	InitLine();
	ReadLineType();
}
bool CSearch::WinLose(BYTE side)
{
	int i,j;
	for(i=0;i<BoardSize;i++) //扫描竖线有没有连五
	  for(j=0;j<BoardSize-4;j++)
	  {
		  if(board[i][j]==side &&board[i][j+1]==side &&board[i][j+2]==side &&board[i][j+3]==side &&board[i][j+4]==side)
			  return true;
	  }
	for(i=0;i<BoardSize;i++) //扫描横线有没有连五
	  for(j=0;j<BoardSize-4;j++)
	  {
		  if(board[j][i]==side &&board[j+1][i]==side &&board[j+2][i]==side &&board[j+3][i]==side &&board[j+4][i]==side)
			  return true;          
	  }
	for(i=0;i<BoardSize-4;i++) //扫描45度斜线
	   for(j=4;j<BoardSize;j++)
	   {
		   if(board[i][j]==side &&board[i+1][j-1]==side &&board[i+2][j-2]==side &&board[i+3][j-3]==side &&board[i+4][j-4]==side)
			  return true;           
	   }
	for(i=0;i<BoardSize-4;i++) //扫描135度斜线
	   for(j=0;j<BoardSize-4;j++)
	   {
		   if(board[i][j]==side &&board[i+1][j+1]==side &&board[i+2][j+2]==side &&board[i+3][j+3]==side &&board[i+4][j+4]==side)
			  return true;          
	   }
	return false;
}
void CSearch::CreateArrays()
{
	int i;
	del=true;
	board=new BYTE *[BoardSize];
	for(i=0;i<BoardSize;i++)	
		board[i]=new BYTE[BoardSize];	

	LineInfo[0]=new line[LineNum];
	LineInfo[1]=new line[LineNum];
}
void CSearch::DelArrays()
{
	int i;
	if(del==true)
	{
		for(i=0;i<BoardSize;i++)
			delete[]board[i];
		delete[]board;

		delete[]LineInfo[0];
		delete[]LineInfo[1];
	}
	PointHistory.clear();
}
void CSearch::InitBoard()
{
	for(int i=0;i<BoardSize;i++)
		for(int j=0;j<BoardSize;j++)
		{
			board[i][j]=EMPTY;
		}
}
void CSearch::MakeMove(BYTE side,point pt)
{		
	board[pt.x][pt.y]=side;
	UpdateLine(BLACK,pt);
	UpdateLine(WHITE,pt);
}
void CSearch::BackMove(BYTE side,point pt)
{
	board[pt.x][pt.y]=EMPTY;
	UpdateLine(BLACK,pt);
	UpdateLine(WHITE,pt);
}
point CSearch::GetCM(BYTE side)
{
	int i,j,x,y,StepID;
	point pt;	
	StepID=0;
	pt.side=EMPTY;
	for(i=0;i<BoardSize;i++)
		for(j=0;j<BoardSize;j++)
		{
			if(board[i][j]!=EMPTY)
			{
				StepID++;
				x=i;
				y=j;
			}				
		}
	if(StepID==0 &&side==BLACK)
	{
		pt.x=BoardSize/2;
		pt.y=BoardSize/2;		
		pt.side=BLACK;		
	}
	else if(StepID==1 &&side==WHITE)
	{
		if(x<BoardSize/2 &&y<BoardSize/2){x++;y++;}
		else if(x<BoardSize/2 &&y>BoardSize/2){x++;y--;}
		else if(x>BoardSize/2 &&y<BoardSize/2){x--;y++;}
		else if(x>BoardSize/2 &&y>BoardSize/2){x--;y--;}
		else if(x<BoardSize/2 &&y==BoardSize/2)x++;
		else if(x>BoardSize/2 &&y==BoardSize/2)x--;
		else if(x==BoardSize/2 &&y<BoardSize/2)y++;
		else if(x==BoardSize/2 &&y>BoardSize/2)y--;
		else if(x==BoardSize/2 &&y==BoardSize/2){x--;y--;}
		pt.x=x;
		pt.y=y;
		pt.side=WHITE;		
	}
	return pt;
}
point CSearch::ComputerMove(BYTE side)
{		
	int i,alpha,beta,value,depth;
	char path[300];
	CString filename;		
	CString StrCurStep;	
	line SiCom,SiPer;
	point pt;
	vector<point> MoveList;
	vector<point>::iterator iterp;
	ComColor=side;
	alpha=-THREAT;beta=THREAT;
	depth=0;
	pt=GetCM(side);
	if(pt.side!=EMPTY)return pt;
	ComThinking=true;	
	SiCom=GetAllLine(side);
	SiPer=GetAllLine(NEXT(side));
	if(SiCom.ThreatNum[0]!=0 ||SiCom.ThreatNum[1]!=0 ||SiPer.ThreatNum[0]!=0 ||SiPer.ThreatNum[1]!=0)
	{
		MoveList=ConstructStepForThreat(SiCom,SiPer);
	}
	else
	{
		MoveList=ConstructStepForNoThreat(SiCom,SiPer);
	}
	strcpy(path,"d:\\SearchRecord");
	_mkdir(path);
	progress.SetRange(0,MoveList.size());
	progress.SetStep(1);
	for(iterp=MoveList.begin(),i=0;iterp!=MoveList.end();iterp++,i++)
	{			
		if(SearchRecord==true)
		{
			filename.Format("/%2d,%2d",iterp->x,iterp->y);
			strcpy(path,"d:\\SearchRecord");strcat(path,filename);_mkdir(path);
		}
		MakeMove(side,*iterp);
		value=MaxSearch(alpha,beta,depth+1,path);
		iterp->value[1]=value;
		if(value>alpha)
			alpha=value;
		BackMove(side,*iterp);			
		progress.StepIt();
	}
	progress.SetPos(0);
	sort(MoveList.begin(),MoveList.end(),ComPointVal1);
	ComThinking=false;

	FILE *F1=fopen("d:\\SearchRecord/Movelist.txt","w");
	for( iterp=MoveList.begin(),i=0;iterp!=MoveList.end();iterp++,i++)
	fprintf(F1,"第1层第%2d节点: %2d,%2d,%5d,%5d\n",i+1,iterp->x,iterp->y,iterp->value[0],iterp->value[1]);
	fclose(F1);
	return MoveList[0];
}
int CSearch::MaxSearch(int alpha,int beta,int depth,char *path)
{
	int i,BestValue,value;
	char MaxPath[300];
	CString StrCurStep;
	CString StrSumStep;	
	CString filename;
	line SiCom,SiPer;
	vector<point> MoveList;
	vector<point>::iterator iterp;
	BestValue=THREAT;	
	SiCom=GetAllLine(ComColor);
	SiPer=GetAllLine(NEXT(ComColor));	
	if(SiCom.value>=WIN)return WIN-depth;	
	if(SiPer.ThreatNum[0]>=1)return -(THREAT-depth);
	if(SiCom.ThreatNum[0]>=2)return THREAT-depth;	

	if(depth>=MaxDepth)
	{
		return SiCom.value-SiPer.value;
	}	

	if(SiCom.ThreatNum[0]!=0 ||SiCom.ThreatNum[1]!=0 ||SiPer.ThreatNum[0]!=0 ||SiPer.ThreatNum[1]!=0)
	{
		MoveList=ConstructStepForThreat(SiPer,SiCom);
	}
	else
	{
		MoveList=ConstructStepForNoThreat(SiPer,SiCom);
	}

	for(iterp=MoveList.begin(),i=0;iterp!=MoveList.end();iterp++,i++)
	{		
		if(SearchRecord==true)
		{
			filename.Format("/%2d,%2d",iterp->x,iterp->y);
			strcpy(MaxPath,path);strcat(MaxPath,filename);_mkdir(MaxPath);
		}
		MakeMove(NEXT(ComColor),*iterp);
		if(depth==1 &&iterp->x==8 &&iterp->y==8)
		{
			int a;
			a=1;
		}
		if(depth==3 &&iterp->x==2 &&iterp->y==5)
		{
			int a;
			a=1;
		}
		if(depth==5 &&iterp->x==8 &&iterp->y==6)
		{
			int a;
			a=1;
		}
		if(depth==7 &&iterp->x==8 &&iterp->y==7)
		{
			int a;
			a=1;
		}
		value=MinSearch(alpha,beta,depth+1,MaxPath);
		iterp->value[1]=value;
		if(value<BestValue)
			BestValue=value;
		if(value<beta)
			beta=value;

		BackMove(NEXT(ComColor),*iterp);
		StrCurStep.Format("第%2d层第%2d个节点: %2d,%2d 步的值为:%5d 线形值为:%5d\r\n\r\n",depth+1,i+1,iterp->x,iterp->y,iterp->value[0],iterp->value[1]);
		if(value<alpha)
		{
			StrCurStep.Format("第%2d层第%2d个节点: %2d,%2d 步的值为:%5d 线形值为:%5d 被α剪枝\r\n\r\n",depth+1,i+1,iterp->x,iterp->y,iterp->value[0],iterp->value[1]);
			StrSumStep+=StrCurStep;
			break;		
		}			
		StrSumStep+=StrCurStep;
	}	
	if(SearchRecord==true)
	{
		strcat(path,"/MaxMovelist.txt");
		FILE *F1=fopen(path,"w");	
		fprintf(F1,"%s",StrSumStep);
		fclose(F1);	
	}
	return BestValue;
}
int CSearch::MinSearch(int alpha,int beta,int depth,char *path)
{
	int i,BestValue,value;
	char MinPath[300];
	CString StrCurStep;
	CString StrSumStep;	
	CString filename;
	line SiCom,SiPer;
	vector<point> MoveList;
	vector<point>::iterator iterp;
	BestValue=-THREAT;	
	SiCom=GetAllLine(ComColor);
	SiPer=GetAllLine(NEXT(ComColor));	
	if(SiPer.value>=WIN)return -(WIN-depth);
	if(SiCom.ThreatNum[0]>=1)return THREAT-depth;
	if(SiPer.ThreatNum[0]>=2)return -(THREAT-depth);

	if(depth>=MaxDepth)
	{
		return SiCom.value-SiPer.value;
	}

	if(SiCom.ThreatNum[0]!=0 ||SiCom.ThreatNum[1]!=0 ||SiPer.ThreatNum[0]!=0 ||SiPer.ThreatNum[1]!=0)
	{
		MoveList=ConstructStepForThreat(SiCom,SiPer);
	}
	else
	{
		MoveList=ConstructStepForNoThreat(SiCom,SiPer);
	}

	for(iterp=MoveList.begin(),i=0;iterp!=MoveList.end();iterp++,i++)
	{		
		if(SearchRecord==true)
		{
			filename.Format("/%2d,%2d",iterp->x,iterp->y);
			strcpy(MinPath,path);strcat(MinPath,filename);_mkdir(MinPath);
		}
		MakeMove(ComColor,*iterp);
		if(depth==2 &&iterp->x==3 &&iterp->y==6)
		{
			int a;
			a=1;
		}
		if(depth==4 &&iterp->x==3 &&iterp->y==8)
		{
			int a;
			a=1;
		}
		if(depth==6 &&iterp->x==3 &&iterp->y==7)
		{
			int a;
			a=1;
		}
		value=MaxSearch(alpha,beta,depth+1,MinPath);
		iterp->value[1]=value;
		if(value>BestValue)
			BestValue=value;
		if(value>alpha)
			alpha=value;

		BackMove(ComColor,*iterp);
		StrCurStep.Format("第%2d层第%2d个节点: %2d,%2d 步的值为:%5d 线形值为:%5d\r\n\r\n",depth+1,i+1,iterp->x,iterp->y,iterp->value[0],iterp->value[1]);
		if(value>beta)
		{
			StrCurStep.Format("第%2d层第%2d个节点: %2d,%2d 步的值为:%5d 线形值为:%5d 被β剪枝\r\n\r\n",depth+1,i+1,iterp->x,iterp->y,iterp->value[0],iterp->value[1]);
			StrSumStep+=StrCurStep;
			break;		
		}			
		StrSumStep+=StrCurStep;		
	}	
	if(SearchRecord==true)
	{
		strcat(path,"/MinMovelist.txt");
		FILE *F1=fopen(path,"w");	
		fprintf(F1,"%s",StrSumStep);
		fclose(F1);	
	}
	return BestValue;
}
vector<point> CSearch::ConstructStepForThreat(line SiCom,line SiPer)
{
	int ComValue,PerValue;
	vector<point> MoveList;
	vector<point>::iterator iterp;
	if(SiCom.ThreatPoint.size()!=0)
	{
		for(iterp=SiCom.ThreatPoint.begin();iterp!=SiCom.ThreatPoint.end();iterp++)
		{
			MoveList.push_back(*iterp);
		}
	}
	if(SiPer.ThreatPoint.size()!=0)
	{
		for(iterp=SiPer.ThreatPoint.begin();iterp!=SiPer.ThreatPoint.end();iterp++)
		{
			MoveList.push_back(*iterp);
		}
	}
	UniquePoint(MoveList);
	for(iterp=MoveList.begin();iterp!=MoveList.end();iterp++)
	{
		board[iterp->x][iterp->y]=SiCom.side;
		UpdateLine(SiCom.side,*iterp,1);
		UpdateLine(SiPer.side,*iterp,1);

		ComValue=GetAllLine(SiCom.side,1).value;
		PerValue=GetAllLine(SiPer.side,1).value;
		iterp->value[0]=ComValue-PerValue;

		board[iterp->x][iterp->y]=EMPTY;
		UpdateLine(SiCom.side,*iterp,1);
		UpdateLine(SiPer.side,*iterp,1);
	}
	sort(MoveList.begin(),MoveList.end(),ComPointVal0);	
	if(MoveList.size()>10)MoveList.resize(10);
	return MoveList;
}
vector<point> CSearch::ConstructStepForNoThreat(line SiCom,line SiPer)
{
	int x,y,ComValue,PerValue;
	Rect area;
	point pt;
	vector<point> MoveList;
	vector<point>::iterator iterp;
	area=GetSearchRange();
	for(x=area.left;x<=area.right;x++)
		for(y=area.top;y<=area.bottom;y++)
		{
			if(board[x][y]==EMPTY)
			{
				pt.x=x;pt.y=y;
				MoveList.push_back(pt);
			}
		}
	for(iterp=MoveList.begin();iterp!=MoveList.end();iterp++)
	{
		board[iterp->x][iterp->y]=SiCom.side;
		UpdateLine(SiCom.side,*iterp,1);
		UpdateLine(SiPer.side,*iterp,1);

		ComValue=GetAllLine(SiCom.side,1).value;
		PerValue=GetAllLine(SiPer.side,1).value;
		iterp->value[0]=ComValue-PerValue;

		board[iterp->x][iterp->y]=EMPTY;
		UpdateLine(SiCom.side,*iterp,1);
		UpdateLine(SiPer.side,*iterp,1);
	}
	sort(MoveList.begin(),MoveList.end(),ComPointVal0);	
	if(MoveList.size()>10)MoveList.resize(10);
	return MoveList;
}
Rect CSearch::GetSearchRange()
{
	bool left,right,top,bottom;
	left=false;right=false;top=false;bottom=false;
	int i,j,m;	
	Rect area;
	m=BoardSize;
	area.left=m/2;
	area.top=m/2;
	area.right=m/2;
	area.bottom=m/2;	

	for(i=0;i<BoardSize;i++)
	{
		for(j=0;j<BoardSize;j++)
		{
			if(board[i][j]!=EMPTY &&left==false)
			{
				area.left=i;
				left=true;
			}
			if(board[m-i-1][j]!=EMPTY &&right==false)
			{
				area.right=m-i-1;
				right=true;
			}
			if(board[j][i]!=EMPTY &&top==false)
			{
				area.top=i;
				top=true;
			}
			if(board[j][m-i-1]!=EMPTY &&bottom==false)
			{
				area.bottom=m-i-1;
				bottom=true;
			}
		}
	}		
	area.left-=1;
	area.top-=1;
	area.right+=1;
	area.bottom+=1;
	if(area.left<0)area.left=0;
	if(area.top<0)area.top=0;
	if(area.right>m-1)area.right=m-1;
	if(area.bottom>m-1)area.bottom=m-1;
	return area;
}
void CSearch::ReadLineType()
{
	FILE*F1;
	F1=fopen("ConFive","r");
	fread(LineType,sizeof(BYTE),BORDER-32,F1);
	fclose(F1);
}
void CSearch::InitLine()
{
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<LineNum;j++)
		{
			LineInfo[i][j].value=0;	
			LineInfo[i][j].ThreatNum[0]=0;
			LineInfo[i][j].ThreatNum[1]=0;
		}
}
void CSearch::UpdateLine(BYTE side,point pt,int which)
{
	int k;
	for(k=0;k<4;k++)
	{		
		UpdateSingleLine(side,pt,k,LineInfo[side],which);
	}
}
void CSearch::BackupLine(BYTE side,point pt,int which)
{
	
}
void CSearch::UpdateSingleLine(BYTE side,point pt,BYTE dir,line *LineInfo,int which)
{
	bool OppSide=false;
	int LineID,x,y,len,style;
	point start,CurP;
	vector<point>::iterator iterp;
	line LinePart;
	LineID=GetLineID(pt,dir);		
	start=GetStartPoint(pt,dir);
	x=start.x;y=start.y;
	CurP=start;
	len=0;style=0;
	LineInfo[LineID].value=0;  //对要更新的线初始化
	LineInfo[LineID].ThreatNum[0]=0;
	LineInfo[LineID].ThreatNum[1]=0;
	if(which==0)
	{
		LineInfo[LineID].ThreatPoint.clear();
	}	
	while(x!=-1 &&x!=BoardSize &&y!=-1 &&y!=BoardSize)
	{
		if(OppSide==true){CurP.x=x;CurP.y=y;OppSide=false;}
		if(board[x][y]==EMPTY)
		{
			len++;
		}
		else if(board[x][y]==side)
		{
			style+=(1<<len);
			len++;
		}
		else
		{
			if(len>4)
			{
				style+=(1<<len);
				LinePart=ValuateType(CurP,dir,style,len,which);
				LineInfo[LineID].value+=LinePart.value;
				LineInfo[LineID].ThreatNum[0]+=LinePart.ThreatNum[0];
				LineInfo[LineID].ThreatNum[1]+=LinePart.ThreatNum[1];
				if(LinePart.ThreatPoint.size()!=0 &&which==0)
				{
					for(iterp=LinePart.ThreatPoint.begin();iterp!=LinePart.ThreatPoint.end();iterp++)
					{
						LineInfo[LineID].ThreatPoint.push_back(*iterp);
					}		
				}				
			}
			OppSide=true;
			len=0;
			style=0;
		}
		IncreaseXY(x,y,dir);
	}
	if(len>4)
	{
		style+=(1<<len);
		LinePart=ValuateType(CurP,dir,style,len,which);
		LineInfo[LineID].value+=LinePart.value;
		LineInfo[LineID].ThreatNum[0]+=LinePart.ThreatNum[0];
		LineInfo[LineID].ThreatNum[1]+=LinePart.ThreatNum[1];
		if(LinePart.ThreatPoint.size()!=0 &&which==0)
		{
			for(iterp=LinePart.ThreatPoint.begin();iterp!=LinePart.ThreatPoint.end();iterp++)
			{
				LineInfo[LineID].ThreatPoint.push_back(*iterp);
			}		
		}			
	}
}
line CSearch::ValuateType(point CurP,BYTE dir,int style,int len,int which)
{
	int i,j,t,num,LineTypeID,first;
	point pt;
	line LinePart;
	LineTypeID=LineType[style-32];
	LinePart.value=LineValue[LineTypeID];	
	if(LineTypeID==1){LinePart.ThreatNum[0]=2;LinePart.ThreatNum[1]=2;}
	else if(LineTypeID==2){LinePart.ThreatNum[0]=1;LinePart.ThreatNum[1]=0;}
	else if(LineTypeID==3){LinePart.ThreatNum[0]=0;LinePart.ThreatNum[1]=1;}
	else{LinePart.ThreatNum[0]=0;LinePart.ThreatNum[1]=0;}
	if(which!=0)return LinePart;
	if(LineTypeID<=2)
	{
		for(i=0;i<len-4;i++)
		{
			num=0;
			t=(style>>i)&31;
			for(j=0;j<5;j++)
			{					
				if(((t>>j)&1)!=0)
                {
					num++;					
				}
			}
			if(num==4)
			{
				for(j=0;j<5;j++)
				{				
					if(((t>>j)&1)==0)
					{						
						pt.x=CurP.x+increasement[dir].ix*(i+j);
						pt.y=CurP.y+increasement[dir].iy*(i+j);						
						LinePart.ThreatPoint.push_back(pt);
						break;
					}
				}
			}			
		}
	}
	else if(LineTypeID==3)
	{
		for(i=0;i<len;i++)
		{
			if((style>>i)&1!=0)continue;
			first=(1<<i);
			if(LineType[style-32+first]==1)
			{
				pt.x=CurP.x+increasement[dir].ix*i;
				pt.y=CurP.y+increasement[dir].iy*i;						
				LinePart.ThreatPoint.push_back(pt);
			}
		}
	}
	else if(LineTypeID==4)
	{
		for(i=0;i<len;i++)
		{
			if((style>>i)&1!=0)continue;
			first=(1<<i);
			if(LineType[style-32+first]==2)
			{
				pt.x=CurP.x+increasement[dir].ix*i;
				pt.y=CurP.y+increasement[dir].iy*i;						
				LinePart.ThreatPoint.push_back(pt);
			}
		}
	}
	return LinePart;
}
line CSearch::GetAllLine(BYTE side,int which)
{
	int i;
	vector<point>::iterator iterp;
	line ln;
	ln.side=side;
	ln.value=0;
	ln.ThreatNum[0]=0;
	ln.ThreatNum[1]=0;
	for(i=0;i<LineNum;i++)
	{
		ln.value+=LineInfo[side][i].value;
		ln.ThreatNum[0]+=LineInfo[side][i].ThreatNum[0];
		ln.ThreatNum[1]+=LineInfo[side][i].ThreatNum[1];
		if(LineInfo[side][i].ThreatPoint.size()!=0 &&which==0)
		{
			for(iterp=LineInfo[side][i].ThreatPoint.begin();iterp!=LineInfo[side][i].ThreatPoint.end();iterp++)
			{
				ln.ThreatPoint.push_back(*iterp);
			}
		}
	}
	return ln;
}
void CSearch::OutputAllLineInfo()
{
	int i,k,sum;
	vector<point>::iterator iterp;
	FILE *F1=fopen("d:\\AllLineInfo.txt","w");
	for(k=0;k<2;k++)
	{
		sum=0;
		for(i=0;i<LineNum;i++)
		{
			sum+=LineInfo[k][i].value;			
			fprintf(F1,"%d:第%d条线的值为:%d\n",k,i,LineInfo[k][i].value);
			if(LineInfo[k][i].ThreatPoint.size()!=0)
			{
				for(iterp=LineInfo[k][i].ThreatPoint.begin();iterp!=LineInfo[k][i].ThreatPoint.end();iterp++)
				{					
					fprintf(F1,"%d:第%d条线的威胁点为:%d,%d\n",k,i,iterp->x,iterp->y);
				}
			}
		}
		fprintf(F1,"%d:总线型值:%d\n",k,sum);
	}
	fclose(F1);
}
