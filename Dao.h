#pragma once
#ifndef DAO
#define DAO
extern "C" {
#include "execute_query.h"
}

#include<vector>
using namespace std;

void addMember(MembersDto member);

struct MembersDto findByMemberId(char id[]);

void addBook(BooksDto book);

vector<BooksDto> selectBooks(const BooksDto& criteria);

void deleteBook(char findIsbn[]);

vector<OrdersDto> selectPurchaseHistory(const char* user_id);

void updateBookDetails(BooksDto& book);

#endif DAO