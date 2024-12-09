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
	char book_ISBN[50];
	char title[20];
	char writer[20];
	char genre[20];
	int price;
};

struct MembersDto select_MemberId(char id[]);
void execute_update(char query[]);
