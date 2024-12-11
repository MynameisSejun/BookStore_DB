#pragma once

struct MembersDto {
	char member_id[20];
	char pw[20];
	char name[20];
	char role[10];
};

struct OrdersDto {
	int order_id;             // �ֹ� ID
	char member_id[20];       // ȸ�� ID
	char book_ISBN[50];       // å ISBN
	char title[100];          // å ����
	char author[100];         // å �۰�
	char genre[50];           // å �帣
	char date[20];            // ���� ��¥
	int count;                // ���� ����
	int pay_amount;           // �� ���� �ݾ�
};


struct BooksDto {
	char isbn[30];
	char title[30];
	char author[20];
	char genre[20];
	int book_price;
	int quantity;
};

struct MembersDto select_MemberId(char id[]);
void execute_update(char query[]);
void execute_insert(char query[]);
struct BooksDto* selectBooks_C(const char* isbn, const char* title, const char* author, const char* genre, int* rowCount);
void execute_delete(char query[]);
void updateBookQuantity(const char* isbn, int newQuantity);
void savePurchaseHistory(const char* userId, const char* isbn, int quantity, int totalAmount);
struct OrdersDto* selectPurchaseHistory_C(const char* user_id, int* rowCount);