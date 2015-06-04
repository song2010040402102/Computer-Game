// LineType.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define BORDER 65536

int len=15;
int EmptyPoint[15];
int epNum=0;
unsigned char LineType[BORDER-32];
void print_binary(int style,int LineID)
{
	int a=style;
	char s[16],filename[20],num[2];
	strcpy(filename,"d:\\");_itoa(LineID,num,10);strcat(filename,num),strcat(filename,".txt");
	FILE *F1=fopen(filename,"a");
	for(int i=0;i<16;i++)
	{
		s[i]=(a%2)+'0';
		a=a/2;		
	}
	fprintf(F1,"%s\n",s);
	fclose(F1);
}
bool construct_win_type(int style)
{		
	int k;	
	for(k=0;k<len-4;k++)
	{
		if(((style>>k)&31)==31)
		{			
			return true;
		}
	}
	return false;
}
bool construct_double_threat(int style)
{
	bool dbThreat;	
	int x,y,first,second;
	if(len<6)return false;
		
	for(x=0;x<=epNum;x++)
	{
		dbThreat=false;
		first=EmptyPoint[x];
		for(y=0;y<=epNum;y++)
		{
			if(x==y)continue;
			second=EmptyPoint[y];						
			if(construct_win_type(style+(1<<second))==true)
			{
				dbThreat=true;
				break;
			}			
		}
		if(dbThreat==false)return false;
	}	
	return true;
}
bool construct_single_threat1(int style)
{	
	int x,first;	
	
	for(x=0;x<=epNum;x++)
	{
		first=EmptyPoint[x];						
		if(construct_win_type(style+(1<<first))==true)
		{				
			return true;
		}		
	}
	return false;
}

bool construct_single_threat2(int style)
{	
	int x,first;
		
	for(x=0;x<=epNum;x++)
	{
		first=EmptyPoint[x];
		if(construct_double_threat(style+(1<<first))==true)return true;
	}
	return false;
}

bool construct_sleep_three(int style)
{	
	int x,y,first,second;
	
	for(x=0;x<=epNum;x++)
	{
		first=EmptyPoint[x];
		for(y=x+1;y<=epNum;y++)
		{
			second=EmptyPoint[y];
			if(construct_win_type(style+(1<<first)+(1<<second))==true)return true;
		}		
	}
	return false;
}

bool construct_live_two(int style)
{
	int x,first;
		
	for(x=0;x<=epNum;x++)
	{
		first=EmptyPoint[x];
		if(construct_single_threat2(style+(1<<first))==true)return true;
	}
	return false;
}

void WriteToLineType()
{
	FILE *F1;
	F1=fopen("d:\\ConFive.lt","w");
	fwrite(LineType,sizeof(unsigned char),BORDER-32,F1);
	fclose(F1);
}
int main(int argc, char* argv[])
{
	int i,k,style;		
	for(style=32;style<BORDER;style++)
	{
		for(k=0;k<31;k++)
		{
			if((style<<k)<0)
			{
				len=32-k-1;
				break;
			}
		}		

		for(i=0,k=0;i<len;i++)
		{								
			if(((style>>i)&1)==0)
			{
				EmptyPoint[k]=i;
				k++;
			}				
		}
		epNum=k-1;

		if(construct_win_type(style)==true)
		{
			print_binary(style,0);
			LineType[style-32]=0;
			continue;  //赢的线型
		}
		if(construct_double_threat(style)==true)
		{
			print_binary(style,1);
			LineType[style-32]=1;
			continue; //打印双威胁
		}
		if(construct_single_threat1(style)==true)
		{
			print_binary(style,2); //落一子即可赢的单威胁
			LineType[style-32]=2;
			continue;
		}
		if(construct_single_threat2(style)==true)
		{
			print_binary(style,3); //落两子即可赢的单威胁
			LineType[style-32]=3;
			continue;
		}
		if(construct_sleep_three(style)==true)
		{
			print_binary(style,4); //落两子即可赢的眠三
			LineType[style-32]=4;
			continue;
		}
		if(construct_live_two(style)==true)
		{
			print_binary(style,5); //落一子即可形成活三（活二）
			LineType[style-32]=5;
			continue;
		}
		print_binary(style,6); //剩下型
		LineType[style-32]=6;
	}
	WriteToLineType();
	return 0;
}
