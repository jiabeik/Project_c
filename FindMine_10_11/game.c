#include"game.h"
//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}
//打印棋盘
void DispBoard(char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	for (int i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (int j = 1; j <= col; j++)
		{
			printf("%c ", show[i][j]);
		}
		printf("\n");
	}
}
//设置雷
void SetMine(char mine[ROWS][COLS], int row, int col)
{
	int count = COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}
//获得周边雷的数量
int Get_mine_count(char mine[ROWS][COLS], int x, int y)//ASCⅡ码值计算
{
	int temp = mine[x - 1][y] + mine[x - 1][y - 1] +
		mine[x][y - 1] + mine[x + 1][y - 1] +
		mine[x + 1][y] + mine[x + 1][y + 1] +
		mine[x][y + 1] + mine[x - 1][y + 1];
	temp = temp - 8 * '0';
	return temp;
}
//遍历，打开相邻不是雷的坐标
void Search(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y)//递归
{
	if (x >= 1 && x <= row && y >= 1 && y <= col)
	{
		if (show[x][y] == ' ')
		{
			return;
		}
		else if (Get_mine_count(mine, x, y) != 0)
		{
			show[x][y] = Get_mine_count(mine, x, y) + '0';
			return;
		}
		else
		{
			show[x][y] = ' ';
			Search(mine, show, row, col, x + 1, y);
			Search(mine, show, row, col, x + 1, y - 1);
			Search(mine, show, row, col, x, y - 1);
			Search(mine, show, row, col, x - 1, y - 1);
			Search(mine, show, row, col, x - 1, y);
			Search(mine, show, row, col, x - 1, y + 1);
			Search(mine, show, row, col, x, y + 1);
			Search(mine, show, row, col, x + 1, y + 1);
		}
	}
}
//判断是否胜利
bool Win(char show[ROWS][COLS], char mine[ROWS][COLS], int row, int col)
{
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (mine[i][j] == '1' || show[i][j] != '*' && mine[i][j] == '0')
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//判断输入的的字符是否符合要求
int Get_input()
{
	char str[30];
	scanf("%s", str);
	rewind(stdin);//删除缓冲区——vs支持
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return -1;
		}
	}
	return atoi(str);
}

//打印菜单
void MENU()
{
	coo c = { "扫雷",COUNT };
	printf("****************************\n");
	printf("*****    1.continue    *****\n");
	printf("*******    0.exit    *******\n");
	printf("****************************\n");
	printf("共有%d个雷\n", c.count);
}

//继续的游戏
void Game()
{
	//存储雷的信息
//已经设置好的信息
	char mine[ROWS][COLS] = { 0 };
	//排查出雷的个数信息
	char show[ROWS][COLS] = { 0 };
	//初始化
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//打印函数
	DispBoard(show, ROW, COL);
	//布置雷
	SetMine(mine, ROW, COL);
	/*DispBoard(mine, ROW, COL);*///答案
	//扫雷
	FindMine(mine, show, ROW, COL);
}

//循环进入游戏
void Again()
{
	int h = 0;
	do
	{
		MENU();
		printf("请选择：");
		h = Get_input();
		switch (h)
		{
		case 1:
			Game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("请重新输入\n");
			continue;
		}
		break;
	} while (h);
}

//进行扫雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int z = 0;
	while (1)//第一次不能是雷
	{
		printf("请输入坐标：");
		x = Get_input();
		if (x == -1)
		{
			printf("输入错误，重新输入\n");
			continue;
		}
		y = Get_input();
		if (y == -1)
		{
			printf("输入错误，重新输入\n");
			continue;
		}
		//判断输入合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (z == 0 && mine[x][y] == '1')
			{
				mine[x][y] = '0';
				while (1)
				{
					int x = rand() % row + 1;
					int y = rand() % col + 1;
					if (mine[x][y] == '0')
					{
						mine[x][y] = '1';
						break;
					}
				}
				z = 1;//使下一次不满足循环条件
			}
			if (show[x][y] != '*')
			{
				printf("已输入，重新输入\n");
				continue;
			}
			if (mine[x][y] == '1' && z != 0)
			{
				printf("BOOM!!! 被炸死\n");
				DispBoard(mine, row, col);
				Again();
				break;
			}
			else
			{
				Search(mine, show, row, col, x, y);
				DispBoard(show, ROW, COL);
				z = 1;
				if (Win(show, mine, row, col))
				{
					printf("赢！\n");
					Again();
					break;
				}
			}

		}
		else
		{
			printf("坐标超出范围，请重新输入坐标\n");
		}
	}
}
