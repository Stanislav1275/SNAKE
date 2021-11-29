#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <Windows.h>
#include <unistd.h>

int i, j, width = 20, height = 20, gayOver, score = 0, x, y, fruitX, fruitY, flag, speed = 200;
void Render();
void SettingLVL();
void UpdateCursore();
void KeysFlag();
void Move();
int main()
{
	setlocale(0, "rus");
    int m, n;
    SettingLVL();
    
    while (!gayOver) 
	{
        Render();
        KeysFlag();
        Move();
    }
}
void Render()
{
	UpdateCursore();
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(i == height - 1 || i == 0)
			printf("*");
			else if((j == width - 1 || j == 0) && (i != 5 || j != 19))
			printf("|");
			else
			{
				if (i == x && j == y)
                    printf("0");
                else if (i == fruitX && j == fruitY)
                    printf("*");
				else printf(" ");
			}
		}
		printf("\n");
	}
    	printf("ВЫ НАБРАЛИ %d\n%d", score,y);
    	printf("НАЖМИТЕ X ЧТОБЫ ЗАВЕРШИТЬ ИГРУ");	
}
void SettingLVL()
{
	x = rand() % 15;
    y = rand() % 15;
label1:
    fruitX = rand() % 15;
    if (fruitX == 0)
        goto label1;
label2:
    fruitY = rand() % 15;
    if (fruitY == 0)
        goto label2;
    score = 0;
}
void KeysFlag()
{
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gayOver = 1;//завершить игру
            break;
        }
    }
}
void Move()
{
	Sleep(speed);
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
  
    // игра заверишлась
    if (x < 0 || y < 0 || y == width - 1 || x == 0 || x == width - 1 || y == 0)
    {
        gayOver = 1;
        printf("\n\nты проиграл");
 	}
    else
    {
    	if (x == fruitX && y == fruitY) //жеска заглатываем и спавним новые фрукты
		{
    	label3:
		    fruitX = rand() % 15;
		    if (fruitX == 0)
		        goto label3;
		
		// если съел - генерировать новый фрукт
		label4:
		    fruitY = rand() % 15;
		    if (fruitY == 0)
		        goto label4;
		    score += 10;
		    if(score % 50 == 0) speed /= 2;// обновление очков и скорости
		}
	}
}
void UpdateCursore()
{
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cd;
    cd.X = 0;
    cd.Y = 0;
    SetConsoleCursorPosition(hd, cd);
}
