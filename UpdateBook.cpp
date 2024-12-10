#define _CRT_SECURE_NO_WARNINGS

#include "UpdateBook.h"
#include <stdio.h>
#include "Dao.h"
#include <iostream>
#include "screenControl.h"

void UpdateBook::printScr()
{
	clrscr();

	print_screen("./screen/UpdateBook.txt");

	char inputIsbn[30];
	char inputTitle[30];
	char inputAuthor[20];
	char inputGenre[20];
	int inputBookPrice;
	char findIsbn[30];

	gotoxy(21, 5);
	gets_s(findIsbn);

	gotoxy(17, 8);
	gets_s(inputIsbn);

	gotoxy(17, 10);
	gets_s(inputTitle);

	gotoxy(17, 12);
	gets_s(inputAuthor);

	gotoxy(17, 14);
	gets_s(inputGenre);

	gotoxy(17, 16);
	cin >> (inputBookPrice);
	cin.ignore();

	int y = cursorControl(13, 18, 20, 2);

	BooksDto book;
	strcpy(book.isbn, inputIsbn);
	strcpy(book.title, inputTitle);
	strcpy(book.author, inputAuthor);
	strcpy(book.genre, inputGenre);
	book.book_price = inputBookPrice;

	switch (y) {
		// 뒤로가기 버튼 생성 필요 요망
	case COMPLETE:
		updateBook(book, findIsbn);
		break;
	case BACK:
		break;
	}
}
