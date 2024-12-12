#define _CRT_SECURE_NO_WARNINGS

#include < windows.h >
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

void gotoxy(int x, int y);
void getxy(int* x, int* y);
void clrscr(void);
void print_screen(const char fname[]);

#define DOWN_KEY 80
#define UP_KEY 72
#define ENTER_KEY 13

#define getch() _getch()

int cursorControl(int x, int startPoint, int endPoint, int gap) {
	int current = startPoint;
	int inputKey;
	gotoxy(x, current);
	while (1) {
		if (_getch() == 13)
			inputKey = 13;
		else inputKey = _getch();
		switch (inputKey) {
		case ENTER_KEY:
			return current;
		case DOWN_KEY: //아래 방향키 입력 시
			if (current + gap <= endPoint) {
				current += gap;
			}
			break;
		case UP_KEY: //윗 방향키 입력 시
			if (current - gap >= startPoint) {
				current -= gap;
			}
			break;
		}
		gotoxy(x, current);
	}
}

/*---------------  화면 커서 제어 함수 --------------------*/
#define STD_HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

void gotoxy(int x, int y)
{
	COORD Cur = { (SHORT)x, (SHORT)y };

	SetConsoleCursorPosition(STD_HANDLE, Cur);
}

void getxy(int* x, int* y)
{
	CONSOLE_SCREEN_BUFFER_INFO Buf;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Buf);
	*x = (int)Buf.dwCursorPosition.X;
	*y = (int)Buf.dwCursorPosition.Y;

}

void clrscr(void)
{
	COORD Cur = { 0, 0 };
	unsigned long dwLen;

	FillConsoleOutputCharacter(STD_HANDLE, ' ', 85 * 85, Cur, &dwLen);
}

/*---------------------------------------------------------*/

void print_screen(const char fname[])
{
	extern int errno;
	FILE* fp;
	char line[100];
	clrscr();
	gotoxy(0, 1);

	if ((fp = fopen(fname, "r")) == NULL) {
		printf("file open error : %d\n", errno);
		getch();
		exit(-1);
	}
	while (1)
	{
		if (fgets(line, 99, fp) == NULL) {
			break;
		}
		printf("%s", line);
	}

	fclose(fp);
}