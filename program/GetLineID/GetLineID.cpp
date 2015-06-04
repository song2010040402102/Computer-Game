// GetLineID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int  d ,x, y;			
	while(1)
	{
		printf("输入线的方向\n");
		scanf("%d",&d);	
		switch(d)
		{
		case 0:
			printf("请输入点的纵坐标\n");
			scanf("%d",&y);
			printf("线的下标为：%d\n",y);
			break;
		case 1:
			printf("请输入点的坐标x,y\n");
			scanf("%d,%d",&x,&y);
			printf("线的下标为：%d\n",15*2+x+y-4);
			break;
		case 2:
			printf("请输入点的横坐标\n");
			scanf("%d",&x);
			printf("线的下标为：%d\n",15+x);
			break;
		case 3:
			printf("请输入点的坐标x,y\n");
			scanf("%d,%d",&x,&y);
			printf("线的下标为：%d\n",15*2+(15-4)*2-1+y-x+10);
			break;
		}	
	}
	return 0;
}

