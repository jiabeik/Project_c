#include"game.h"

typedef struct Coord
{
	char name[20];
	int count;
}coo;
void menu()//打印菜单
{
	coo c = { "扫雷",COUNT };
	printf("%s\n", c.name);
	printf("****************************\n");
	printf("********    play    ********\n");
	printf("********    exit    ********\n");
	printf("****************************\n");
	printf("共有%d个雷\n", c.count);
}
void game()
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
	DispBoard(mine, ROW, COL);//答案
	//扫雷
	FindMine(mine, show, ROW, COL);


}

//int chose()
//{
//	for (int i = 0; i < '\0'; i++)
//	{
//		if (input == '1')
//		{
//			return 1;
//		}
//		else if (input == '0')
//		{
//			return 0;
//		}
//		else
//		{
//			return 2;
//		}
//	}
//
//}

int get_input()
{
	char str[100];
	scanf("%s" ,str, sizeof(str));
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return -1;
		}
	}
	return atoi(str);
}

void test()
{
	char input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择：");
		input = get_input();
		//随机数生成				
		/*	chose(input);*/
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("重新选择:\n");
		}
	} while (input);
}
	//char input = 0;
	//menu();
	//printf("请选择：");
	//scanf("%c", &input);
	//srand((unsigned int)time(NULL));//随机数生成
	//while (input)
	//{
	///*	chose(input);*/
	//	switch (input)
	//	{
	//	case '1':
	//		game();
	//		break;
	//	case '0':
	//		printf("退出游戏\n");
	//		break;
	//	default:
	//		printf("重新选择:\n");
	//		menu();
	//		printf("请选择：");
	//		scanf("%c", &input);
	//	}
	//} 
//}
int main()
{
	test();
	return 0;
}