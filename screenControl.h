#pragma once
void gotoxy(int x, int y);
void getxy(int* x, int* y);
void clrscr(void);
int cursorControl(int x, int startPoint, int endPoint, int gap);
void print_screen(const char fname[]);