#include"game.h"

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


int Get_mine_count(char mine[ROWS][COLS], int x, int y)//ASCⅡ码值计算
{
	int temp = mine[x - 1][y] + mine[x - 1][y - 1] +
		mine[x][y - 1] + mine[x + 1][y - 1] +
		mine[x + 1][y] + mine[x + 1][y + 1] +
		mine[x][y + 1] + mine[x - 1][y + 1];
	temp = temp - 8 * '0';
	return temp;
}

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

int Get_input()
{
	char str[30];
	scanf("%s", str);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return -1;
		}
	}
	return atoi(str);
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
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
		if (mine[x][y] == '1')
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
		}
		
		if (x >= 1 && x <= row && y >= 1 && y <= col)//判断输入合法性
		{
			if (show[x][y] != '*')
			{
				printf("已输入，重新输入\n");
				continue;
			}
			if (mine[x][y] == '1')
			{
				printf("BOOM!!!\n");
				DispBoard(mine, row, col);
				break;
			}
			else
			{
				Search(mine, show, row, col, x, y);
				DispBoard(show, ROW, COL);
				if (Win(show, mine, row, col))
				{
					printf("赢！\n");
					break;
				}
			}

		}
		else
		{
			printf("请重新输入坐标\n");
		}
	}

}