#pragma once
#include "execute_query.h"
#include <vector>

using namespace std;

class UserCheckMenu
{
public:
	void printSrc();
	void displayPurchaseHistory(const vector<OrdersDto>& orderHistory);
};

