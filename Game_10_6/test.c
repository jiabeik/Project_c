
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
	printf("********   1.play   ********\n");
	printf("********   0.exit   ********\n");
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
	DispBoard(show,ROW,COL);
	//布置雷
	SetMine(mine, ROW, COL);
	DispBoard(mine, ROW, COL);//答案
	//扫雷
	FindMine(mine, show, ROW, COL);


}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));//随机数生成
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
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
int main()
{
	test();
	return 0;
}