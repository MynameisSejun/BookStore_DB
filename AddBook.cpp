#define _CRT_SECURE_NO_WARNINGS

#include "screenControl.h"
#include "AddBook.h"
#include <stdio.h>
#include "Dao.h"
#include <iostream>

void AddBook::printScr() {
	clrscr();

	print_screen("./screen/AddBook.txt");

	char inputIsbn[30];
	char inputTitle[30];
	char inputAuthor[20];
	char inputGenre[20];
	int inputBookPrice;

	gotoxy(23, 5);
	gets_s(inputIsbn);

	gotoxy(24, 7);
	gets_s(inputTitle);

	gotoxy(22, 9);
	gets_s(inputAuthor);

	gotoxy(22, 11);
	gets_s(inputGenre);

	gotoxy(22, 13);
	cin >> (inputBookPrice);
	cin.ignore();

	int y = cursorControl(17, 15, 17, 2);

	BooksDto book;
	strcpy(book.isbn, inputIsbn);
	strcpy(book.title, inputTitle);
	strcpy(book.author, inputAuthor);
	strcpy(book.genre, inputGenre);
	book.book_price = inputBookPrice;

	switch (y) {
		// 뒤로가기 버튼 생성 필요 요망
	case COMPLETE:
		addBook(book);
		break;
	case BACK:
		break;
	}
}