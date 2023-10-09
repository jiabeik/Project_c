#include <stdio.h>
#include <time.h>


// 定义蛇的最大长度
#define MAX_LENGTH 100

// 定义蛇的方向
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// 定义蛇的结构体
struct Snake {
    int x;
    int y;
};

// 定义食物的结构体
struct Food {
    int x;
    int y;
};

// 定义全局变量
int width = 20;   // 游戏界面的宽度
int height = 20;  // 游戏界面的高度
int score = 0;    // 得分
int gameOver = 0; // 游戏是否结束
enum Direction dir;
struct Snake snake[MAX_LENGTH];
struct Food food;

// 初始化游戏
void init() {
    // 初始化蛇的初始位置和长度
    snake[0].x = width / 2;
    snake[0].y = height / 2;
    snake[1].x = width / 2 - 1;
    snake[1].y = height / 2;
    snake[2].x = width / 2 - 2;
    snake[2].y = height / 2;

    // 初始化蛇的初始方向
    dir = RIGHT;

    // 初始化食物的位置
    food.x = rand() % width;
    food.y = rand() % height;
}

// 绘制游戏界面
void draw() {
    system("cls"); // 清屏

    // 绘制上边界
    for (int i = 0; i < width + 2; i++) {
        printf("#");
    }
    printf("\n");

    // 绘制游戏界面
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                printf("#"); // 绘制左边界
            }

            // 绘制蛇的身体
            int isSnakeBody = 0;
            for (int k = 0; k < score + 1; k++) {
                if (snake[k].x == j && snake[k].y == i) {
                    printf("O");
                    isSnakeBody = 1;
                    break;
                }
            }

            // 绘制食物
            if (!isSnakeBody && food.x == j && food.y == i) {
                printf("@");
            }
            else if (!isSnakeBody) {
                printf(" ");
            }

            if (j == width - 1) {
                printf("#"); // 绘制右边界
            }
        }
        printf("\n");
    }

    // 绘制下边界
    for (int i = 0; i < width + 2; i++) {
        printf("#");
    }
    printf("\n");

    // 绘制得分
    printf("Score: %d\n", score);
}

// 处理键盘输入
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

// 更新游戏状态
void update() {
    // 更新蛇的位置
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

    // 检查是否吃到食物
    if (snake[0].x == food.x && snake[0].y == food.y) {
        score++;
        food.x = rand() % width;
        food.y = rand() % height;
    }

    // 检查是否碰到边界或自身
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
    // 初始化游戏
    init();

    // 游戏循环
    while (!gameOver) {
        // 绘制游戏界面
        draw();

        // 处理键盘输入
        input();

        // 更新游戏状态
        update();

        // 控制游戏速度
        Sleep(100);
    }

    // 游戏结束
    printf("Game Over!\n");

    return 0;
}