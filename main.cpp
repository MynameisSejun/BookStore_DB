#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <vector>

#include "MainMenu.h"
#include "Dao.h"

#define getch() _getch()

using namespace std;

int main()
{
	_putenv("NLS_LANG=American_America.KO16KSC5601"); //한글사용

	MainMenu mainMenu;
	mainMenu.printSrc();

	//UpdateBook updateBook;
	//updateBook.printScr();
	getch();
}