#include "AdminBookMenu.h"

#include "screenControl.h"
#include <stdlib.h>
#include "AddBook.h"
#include "AdminMainMenu.h"
#include "UpdateBook.h"
#include "DeleteBook.h"

void AdminBookMenu::printSrc()
{
	clrscr();

	print_screen("./screen/AdminBookMenu.txt");

	int y = cursorControl(17, 5, 11, 2);

	switch (y) {
	case ADD:
		AddBook addMenu;
		addMenu.printScr();
		break;

	case UPDATE:
		UpdateBook updateMenu;
		updateMenu.printSrc();
		break;

	case DELETE:
		DeleteBook deleteMenu;
		deleteMenu.printScr();
		break;

	case EXIT:
		AdminMainMenu back;
		back.printSrc();
		break;
	}
}
