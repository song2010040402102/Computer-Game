// GetLineID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	int  d ,x, y;			
	while(1)
	{
		printf("�����ߵķ���\n");
		scanf("%d",&d);	
		switch(d)
		{
		case 0:
			printf("��������������\n");
			scanf("%d",&y);
			printf("�ߵ��±�Ϊ��%d\n",y);
			break;
		case 1:
			printf("������������x,y\n");
			scanf("%d,%d",&x,&y);
			printf("�ߵ��±�Ϊ��%d\n",15*2+x+y-4);
			break;
		case 2:
			printf("�������ĺ�����\n");
			scanf("%d",&x);
			printf("�ߵ��±�Ϊ��%d\n",15+x);
			break;
		case 3:
			printf("������������x,y\n");
			scanf("%d,%d",&x,&y);
			printf("�ߵ��±�Ϊ��%d\n",15*2+(15-4)*2-1+y-x+10);
			break;
		}	
	}
	return 0;
}

