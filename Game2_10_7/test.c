#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<time.h>

#define SIZE 10
#define BOMBS 10

void initializeBoard(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
            hiddenBoard[i][j] = '-';
        }
    }
}

void placeBombs(char board[SIZE][SIZE]) {
    int bombsPlaced = 0;

    while (bombsPlaced < BOMBS) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (board[row][col] != '*') {
            board[row][col] = '*';
            bombsPlaced++;
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int countAdjacentBombs(char board[SIZE][SIZE], int row, int col) {
    int count = 0;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && board[i][j] == '*') {
                count++;
            }
        }
    }

    return count;
}

void revealCell(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE], int row, int col) {
    if (hiddenBoard[row][col] != '-') {
        return;
    }

    hiddenBoard[row][col] = '0' + countAdjacentBombs(board, row, col);

    if (hiddenBoard[row][col] == '0') {
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                    revealCell(board, hiddenBoard, i, j);
                }
            }
        }
    }
}

int main() {
    char board[SIZE][SIZE];
    char hiddenBoard[SIZE][SIZE];
    int row, col;

    srand(time(0));

    initializeBoard(board, hiddenBoard);
    placeBombs(board);

    while (1) {
        printBoard(hiddenBoard);

        printf("Enter row and column: ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid input! Try again.\n");
            continue;
        }

        if (board[row][col] == '*') {
            printf("Game over! You hit a bomb.\n");
            break;
        }

        revealCell(board, hiddenBoard, row, col);

        int cellsLeft = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (hiddenBoard[i][j] == '-') {
                    cellsLeft++;
                }
            }
        }

        if (cellsLeft == BOMBS) {
            printf("Congratulations! You won the game.\n");
            break;
        }
    }

    return 0;
}