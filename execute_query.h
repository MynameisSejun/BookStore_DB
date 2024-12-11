#pragma once

struct MembersDto {
	char member_id[20];
	char pw[20];
	char name[20];
	char role[10];
};

struct OrdersDto {
	int order_id;             // 주문 ID
	char member_id[20];       // 회원 ID
	char book_ISBN[50];       // 책 ISBN
	char title[100];          // 책 제목
	char author[100];         // 책 작가
	char genre[50];           // 책 장르
	char date[20];            // 구매 날짜
	int count;                // 구매 수량
	int pay_amount;           // 총 결제 금액
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