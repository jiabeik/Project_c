#include"game.h"


void menu()//��ӡ�˵�
{
	coo c = { "ɨ��",COUNT };
	printf("%s\n", c.name);
	printf("****************************\n");
	printf("*******    1.play    *******\n");
	printf("*******    0.exit    *******\n");
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
	/*DispBoard(mine, ROW, COL);*///��
	//ɨ��
	FindMine(mine, show, ROW, COL);
}

void test()
{
	int input = 0;;
	srand((unsigned int)time(NULL));
	//���������
	do
	{
		menu();
		printf("��ѡ��");
		input = Get_input();
		switch (input)
		{
		case 1:
			game();
			input--;
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("����ѡ��:\n");
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}