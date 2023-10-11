#include"game.h"
//��ʼ������
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
//��ӡ����
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
//������
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
//����ܱ��׵�����
int Get_mine_count(char mine[ROWS][COLS], int x, int y)//ASC����ֵ����
{
	int temp = mine[x - 1][y] + mine[x - 1][y - 1] +
		mine[x][y - 1] + mine[x + 1][y - 1] +
		mine[x + 1][y] + mine[x + 1][y + 1] +
		mine[x][y + 1] + mine[x - 1][y + 1];
	temp = temp - 8 * '0';
	return temp;
}
//�����������ڲ����׵�����
void Search(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y)//�ݹ�
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
//�ж��Ƿ�ʤ��
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

//�ж�����ĵ��ַ��Ƿ����Ҫ��
int Get_input()
{
	char str[30];
	scanf("%s", str);
	rewind(stdin);//ɾ������������vs֧��
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return -1;
		}
	}
	return atoi(str);
}

//��ӡ�˵�
void MENU()
{
	coo c = { "ɨ��",COUNT };
	printf("****************************\n");
	printf("*****    1.continue    *****\n");
	printf("*******    0.exit    *******\n");
	printf("****************************\n");
	printf("����%d����\n", c.count);
}

//��������Ϸ
void Game()
{
	//�洢�׵���Ϣ
//�Ѿ����úõ���Ϣ
	char mine[ROWS][COLS] = { 0 };
	//�Ų���׵ĸ�����Ϣ
	char show[ROWS][COLS] = { 0 };
	//��ʼ��
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//��ӡ����
	DispBoard(show, ROW, COL);
	//������
	SetMine(mine, ROW, COL);
	/*DispBoard(mine, ROW, COL);*///��
	//ɨ��
	FindMine(mine, show, ROW, COL);
}

//ѭ��������Ϸ
void Again()
{
	int h = 0;
	do
	{
		MENU();
		printf("��ѡ��");
		h = Get_input();
		switch (h)
		{
		case 1:
			Game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("����������\n");
			continue;
		}
		break;
	} while (h);
}

//����ɨ��
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int z = 0;
	while (1)//��һ�β�������
	{
		printf("���������꣺");
		x = Get_input();
		if (x == -1)
		{
			printf("���������������\n");
			continue;
		}
		y = Get_input();
		if (y == -1)
		{
			printf("���������������\n");
			continue;
		}
		//�ж�����Ϸ���
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
				z = 1;//ʹ��һ�β�����ѭ������
			}
			if (show[x][y] != '*')
			{
				printf("�����룬��������\n");
				continue;
			}
			if (mine[x][y] == '1' && z != 0)
			{
				printf("BOOM!!! ��ը��\n");
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
					printf("Ӯ��\n");
					Again();
					break;
				}
			}

		}
		else
		{
			printf("���곬����Χ����������������\n");
		}
	}
}
