#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

#define ROW 10
#define COL 10

#define ROWS ROW+2
#define COLS COL+2

#define COUNT 10

typedef struct Coord
{
	char name[20];
	int count;
}coo;

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);
void DispBoard(char show[ROWS][COLS], int row, int col);
void SetMine(char mine[ROWS][COLS], int row, int col);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
void Search(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y);
bool Win(char show[ROWS][COLS], char mine[ROWS][COLS], int row, int col);

