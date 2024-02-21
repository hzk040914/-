#include <stdio.h>
#include <graphics.h> //easyX
#include "resource.h"
//mciSendString��Ҫ
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#define SPACE 10 //���ӿ��10����
#define COLS 80 //���������
#define ROWS 80 //���������
int isContinue = 1;//ѭ��
int map[ROWS][COLS] = { 0 };//��������״̬
//��һ�������θ��ӣ�xyΪ�������Ͻǵ����꣬flagΪ״̬
void drawRect(int x, int y, int flag);

//����������
void drawMap();

//���������������ö�ά����
void getAndSet();

//���º���
void update();

//�Զ���ʼ��ģʽ
void startup();

int main()
{
	//1. ����������
	initgraph(COLS*SPACE, ROWS*SPACE);

	//2. ��������ַ�����ʾ��
	char tips[3][200] = {
		"����1 �� ���ϸ����Χ��3������ϸ�� ���\n",
		"����2 �� ���ϸ����Χ��2������ϸ����ά�ֲ���\n",
		"����3 �� ������� �����\n"
	};

//#if 0
	settextcolor(RED);
	for (int i = 0;i<3;i++)
	{
		outtextxy(150, 333, tips[i]);
		Sleep(2000);
		cleardevice();
	}
//#endif
	//3. ��������ͼ
	//drawMap();
#if 0
	//�Զ���ʼ��
	startup();
	drawMap();
#endif
	//4. ��������� һ����ʾ һ��������루���̣߳��첽io,io��·���ã�����̣�
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)getAndSet,NULL,NULL,NULL);
	while (isContinue)
	{
		drawMap();
	}

	//5. ���ֲ���
	mciSendString("open 1.mp3 alias mybgm", NULL, 0, NULL);
	mciSendString("play mybgm repeat", NULL, 0, NULL);

	//6. ���ݶ��ƵĹ����㷨�����ݱ�
	while (1)
	{
		update();
		drawMap();
	}
}

void drawRect(int x, int y, int flag)
{
	//�߿����ɫ
	setcolor(RGB(167, 167, 167));
	if (1==flag)
	{
		setfillcolor(WHITE);
	} 
	else
	{
		setfillcolor(BLACK);
	}
	fillrectangle(x, y, x + SPACE, y + SPACE);
}

void drawMap()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//Sleep(1);//��ʾ��������
			drawRect(j * SPACE, i * SPACE, map[i][j]);
		}
	}
}

void getAndSet()
{
	MOUSEMSG msg;
	int x, y;
	while (isContinue)
	{
		msg = GetMouseMsg();
		//������Կ�ߵ����±�
		x = msg.x / SPACE;
		y = msg.y / SPACE;

		if (msg.mkLButton) {//���������
			map[y][x] = 1;
			if (y == (ROWS - 1) && x == (COLS - 1))
			{
				isContinue = 0;
			}
		}
		else
		{
			map[y][x] = 0;
		}
	}
}

void update()
{
	int NewCells[ROWS][COLS] = { 0 };//��һ֡��ϸ�����

	//Ϊ�˷��㴦�����Ա߽紦��
	for (int i = 0; i < ROWS - 1; i++)
	{
		for (int j = 0; j < COLS - 1; j++)
		{
			int NeibourNumber;//ͳ���ھӵĸ���
			NeibourNumber = map[i - 1][j - 1] + map[i - 1][j] + map[i - 1][j + 1] + map[i][j - 1] + map[i][j + 1] + map[i + 1][j - 1] + map[i + 1][j] + map[i + 1][j + 1];
			if (NeibourNumber == 3)//����Χ��3��ϸ������ǰλ��ϸ��Ϊ��
			{
				NewCells[i][j] = 1;
			}
			else if (NeibourNumber == 2)//��Χ��2��ϸ������ǰλ��ϸ������
			{
				NewCells[i][j] = map[i][j];
			}
			else
			{
				NewCells[i][j] = 0;
			}
		}
	}
	if (map[ROWS][COLS] == NewCells[ROWS][COLS])//��������ݱ�ͽ����ˣ���ֹ������Դ
	{

	}
	//�������ֵ��map
	for (int i = 0; i < ROWS-1; i++)
	{
		for (int j = 0; j < COLS-1; j++)
		{
			map[i][j] = NewCells[i][j];
		}
	}

}

void startup()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			map[i][j] = rand() % 2;//ϸ�����״̬
		}
	}
}
