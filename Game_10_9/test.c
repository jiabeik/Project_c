#include"game.h"

typedef struct Coord
{
	char name[20];
	int count;
}coo;
void menu()//��ӡ�˵�
{
	coo c = { "ɨ��",COUNT };
	printf("%s\n", c.name);
	printf("****************************\n");
	printf("********    play    ********\n");
	printf("********    exit    ********\n");
	printf("****************************\n");
	printf("����%d����\n", c.count);
}
void game()
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
	DispBoard(mine, ROW, COL);//��
	//ɨ��
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
		printf("��ѡ��");
		input = get_input();
		//���������				
		/*	chose(input);*/
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("����ѡ��:\n");
		}
	} while (input);
}
	//char input = 0;
	//menu();
	//printf("��ѡ��");
	//scanf("%c", &input);
	//srand((unsigned int)time(NULL));//���������
	//while (input)
	//{
	///*	chose(input);*/
	//	switch (input)
	//	{
	//	case '1':
	//		game();
	//		break;
	//	case '0':
	//		printf("�˳���Ϸ\n");
	//		break;
	//	default:
	//		printf("����ѡ��:\n");
	//		menu();
	//		printf("��ѡ��");
	//		scanf("%c", &input);
	//	}
	//} 
//}
int main()
{
	test();
	return 0;
}