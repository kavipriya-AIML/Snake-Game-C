#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 30
#define HEIGHT 15

int gameOver;
int x, y, fruitX, fruitY;
int score;

int tailX[100], tailY[100];
int tailLength;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void setup()
{
    gameOver = 0;
    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    score = 0;
    tailLength = 0;
}

void draw()
{
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");

            else if (i == fruitY && j == fruitX)
                printf("*");

            else
            {
                int printed = 0;

                for (int k = 0; k < tailLength; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }

                if (!printed)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }

        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\nScore: %d\n", score);
    printf("W A S D = Move | X = Exit\n");
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;

            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;

            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;

            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;

            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void logic()
{
    int previousX = tailX[0];
    int previousY = tailY[0];

    int previous2X;
    int previous2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        previous2X = tailX[i];
        previous2Y = tailY[i];

        tailX[i] = previousX;
        tailY[i] = previousY;

        previousX = previous2X;
        previousY = previous2Y;
    }

    switch (dir)
    {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;

        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;

        tailLength++;
    }
}

int main()
{
    setup();

    while (!gameOver)
    {
        draw();
        input();
        logic();

        Sleep(100);
    }

    printf("\nGAME OVER!\n");
    printf("Final Score: %d\n", score);

    return 0;
}