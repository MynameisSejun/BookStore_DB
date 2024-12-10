#define _CRT_SECURE_NO_WARNINGS

#include "DeleteBook.h"
#include <stdio.h>
#include "Dao.h"
#include <iostream>
#include "screenControl.h"

void DeleteBook::printScr() {
	clrscr();

	print_screen("./screen/DeleteBook.txt");

	char inputIsbn[30];

	gotoxy(21, 5);
	gets_s(inputIsbn);

	int y = cursorControl(13, 9, 11, 2);

	switch (y) {
		// 뒤로가기 버튼 생성 필요 요망
	case COMPLETE:
		deleteBook(inputIsbn);
		break;
	case BACK:
		break;
	}
}
