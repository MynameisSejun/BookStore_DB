#pragma once

struct MembersDto {
	char member_id[20];
	char pw[20];
	char name[20];
	char role[10];
};

struct OrdersDto {
	int order_id;
	char member_id[20];
	char book_ISBN[50];
	char date[20];
	int count;
	int pay_amount;
};

struct BooksDto {
	char isbn[30];
	char title[30];
	char author[20];
	char genre[20];
	int book_price;
};

struct MembersDto select_MemberId(char id[]);
void execute_update(char query[]);
void execute_insert(char query[]);
struct BooksDto* selectBooks_C(const char* isbn, const char* title, const char* author, const char* genre, int* rowCount);