// Search.h: interface for the CSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCH_H__31E0AB80_F32C_47EA_BC64_DF48B9017362__INCLUDED_)
#define AFX_SEARCH_H__31E0AB80_F32C_47EA_BC64_DF48B9017362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
#include <vector>
using namespace std;

#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define BORDER 65536
#define WIN 10000
#define LOSE -10000
#define THREAT (WIN-1)
#define ANGLE0 0
#define ANGLE45 1
#define ANGLE90 2
#define ANGLE135 3
#define MaxDepth 5
#define NEXT(player) (player^1)
typedef unsigned char BYTE;
struct point
{
	BYTE side;
	int x;
	int y;
	int value[2]; //分别存储招法值与线型值	
};
struct line
{
	BYTE side;
	int value;
	int ThreatNum[2];  //分别表示连四和连三威胁数
	vector<point> ThreatPoint;  //威胁点，此点可让本方或对方赢
};
struct increase
{
	int ix;
	int iy;
};
struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
};
class CSearch  
{
public:
	BYTE **board;
	line *LineInfo[2];
	BYTE player;
	BYTE ComColor;
	BYTE LineType[BORDER-32];
	point CurPoint;
	bool EndGame;
	bool del;
	bool ComThinking;
	bool SearchRecord;
	int LineNum;
	vector<point> PointHistory;
public:
	CSearch();
	virtual ~CSearch();
	void InitGame();
	void CreateArrays();
	void DelArrays();
	void InitBoard();
	void ReadLineType();
	bool WinLose(BYTE side);
	point ComputerMove(BYTE side);	
	line GetAllLine(BYTE side,int which=0);
	line ValuateType(point CurP,BYTE dir,int style,int len,int which=0);
	void InitLine();
	void BackupLine(BYTE side,point pt,int which=0);
	void UpdateLine(BYTE side,point pt,int which=0);
	void UpdateSingleLine(BYTE side,point pt,BYTE dir,line *LineInfo,int which=0);	
	vector<point> ConstructStepForThreat(line SiCom,line SiPer);
	vector<point> ConstructStepForNoThreat(line SiCom,line SiPer);
	void MakeMove(BYTE side,point pt);
	void BackMove(BYTE side,point pt);
	int MaxSearch(int alpha,int beta,int depth,char *path);
	int MinSearch(int alpha,int beta,int depth,char *path);
	Rect GetSearchRange();
	void OutputAllLineInfo();
	point GetCM(BYTE side);	
};

#endif // !defined(AFX_SEARCH_H__31E0AB80_F32C_47EA_BC64_DF48B9017362__INCLUDED_)
