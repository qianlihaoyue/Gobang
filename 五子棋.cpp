#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<easyx.h>     //vs2019之前好像不用这个头文件

void map_init();     
bool judge();
void success();
void mouse();

int i, j, x, y , flag = 0,piece[15][15] = { 0 };
IMAGE chess;

void main()
{
	map_init();
	while (1)
	{
		mouse();
		Sleep(10);					// 延时，降低 CPU 占用率
		success();
	}
	closegraph();
}

void map_init()				 //初始化游戏背景
{
	int w, h;
	loadimage(&chess, _T("res\\chess.png"));
	w = chess.getwidth();
	h = chess.getheight();
	initgraph(w, h * 4 / 5);
	setaspectratio(1.5, 1.5);
	loadimage(0, _T("res\\bk.jpg"));
	setaspectratio(0.8, 0.8);
	loadimage(0, _T("res\\chess.png"));
	setaspectratio(1, 1);

	setlinecolor(RGB(0, 0, 0));
	settextstyle(80, 0, _T("华文行楷"));
	setbkmode(TRANSPARENT);
}

void mouse()             
{
	MOUSEMSG msg;
	if (flag) setfillcolor(RGB(255, 255, 255));
	else	  setfillcolor(RGB(0, 0, 0));
	fillcircle(900, 500, 20);

	while (MouseHit())			// 当有鼠标消息的时候执行
	{
		msg = GetMouseMsg();	// 获取鼠标消息
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			x = msg.x / 53; y = msg.y / 51;
			if (!piece[x][y] && x < 15)
			{
				fillcircle(x * 53 + 27, y * 51 + 20, 20);
				piece[x][y] = flag + 1;
				flag = !flag;
			}
		}
	}
}

bool judge()   
{
	int b,temp=piece[x][y];      //b->储存相同的数量   temp储存刚刚落得棋子
	b = 1;
	i = x;   while (piece[i--][y] == temp)   b++;	//横
	i = x;   while (piece[i++][y] == temp)   b++;
	if (b == 7) return true;

	b = 1;
	j = y;    while (piece[x][j--] == temp)  b++;	//竖
	j = y;    while (piece[x][j++] == temp)  b++;
	if (b == 7) return true;

	b = 1;
	i = x; j = y;  while (piece[i--][j++] == temp)  b++;	//撇
	i = x; j = y;  while (piece[i++][j--] == temp)  b++;
	if (b == 7) return true;

	b = 1;
	i = x; j = y;  while (piece[i--][j--] == temp)  b++;  //捺
	i = x; j = y;  while (piece[i++][j++] == temp)  b++;
	if (b == 7) return true;

	return false;
}

void success()
{
	if (judge())
	{
		if (flag == 1) outtextxy(850, 200, _T("黑"));
		else outtextxy(850, 200, _T("白"));
		outtextxy(850, 280, _T("棋"));
		outtextxy(820, 350, _T("胜出"));
		system("pause");

		memset(piece, 0, sizeof(piece));  //重置
		flag = 0;
		main();
	}
}


