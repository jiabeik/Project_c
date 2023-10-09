#include <stdio.h>
#include <time.h>


// �����ߵ���󳤶�
#define MAX_LENGTH 100

// �����ߵķ���
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// �����ߵĽṹ��
struct Snake {
    int x;
    int y;
};

// ����ʳ��Ľṹ��
struct Food {
    int x;
    int y;
};

// ����ȫ�ֱ���
int width = 20;   // ��Ϸ����Ŀ��
int height = 20;  // ��Ϸ����ĸ߶�
int score = 0;    // �÷�
int gameOver = 0; // ��Ϸ�Ƿ����
enum Direction dir;
struct Snake snake[MAX_LENGTH];
struct Food food;

// ��ʼ����Ϸ
void init() {
    // ��ʼ���ߵĳ�ʼλ�úͳ���
    snake[0].x = width / 2;
    snake[0].y = height / 2;
    snake[1].x = width / 2 - 1;
    snake[1].y = height / 2;
    snake[2].x = width / 2 - 2;
    snake[2].y = height / 2;

    // ��ʼ���ߵĳ�ʼ����
    dir = RIGHT;

    // ��ʼ��ʳ���λ��
    food.x = rand() % width;
    food.y = rand() % height;
}

// ������Ϸ����
void draw() {
    system("cls"); // ����

    // �����ϱ߽�
    for (int i = 0; i < width + 2; i++) {
        printf("#");
    }
    printf("\n");

    // ������Ϸ����
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                printf("#"); // ������߽�
            }

            // �����ߵ�����
            int isSnakeBody = 0;
            for (int k = 0; k < score + 1; k++) {
                if (snake[k].x == j && snake[k].y == i) {
                    printf("O");
                    isSnakeBody = 1;
                    break;
                }
            }

            // ����ʳ��
            if (!isSnakeBody && food.x == j && food.y == i) {
                printf("@");
            }
            else if (!isSnakeBody) {
                printf(" ");
            }

            if (j == width - 1) {
                printf("#"); // �����ұ߽�
            }
        }
        printf("\n");
    }

    // �����±߽�
    for (int i = 0; i < width + 2; i++) {
        printf("#");
    }
    printf("\n");

    // ���Ƶ÷�
    printf("Score: %d\n", score);
}

// �����������
void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

// ������Ϸ״̬
void update() {
    // �����ߵ�λ��
    for (int i = score; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    switch (dir) {
    case UP:
        snake[0].y--;
        break;
    case DOWN:
        snake[0].y++;
        break;
    case LEFT:
        snake[0].x--;
        break;
    case RIGHT:
        snake[0].x++;
        break;
    }

    // ����Ƿ�Ե�ʳ��
    if (snake[0].x == food.x && snake[0].y == food.y) {
        score++;
        food.x = rand() % width;
        food.y = rand() % height;
    }

    // ����Ƿ������߽������
    if (snake[0].x < 0 || snake[0].x >= width || snake[0].y < 0 || snake[0].y >= height) {
        gameOver = 1;
    }
    for (int i = 1; i < score + 1; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = 1;
            break;
        }
    }
}

int main() {
    // ��ʼ����Ϸ
    init();

    // ��Ϸѭ��
    while (!gameOver) {
        // ������Ϸ����
        draw();

        // �����������
        input();

        // ������Ϸ״̬
        update();

        // ������Ϸ�ٶ�
        Sleep(100);
    }

    // ��Ϸ����
    printf("Game Over!\n");

    return 0;
}