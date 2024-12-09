#pragma once
extern "C" {
#include "execute_query.h"
}

#include<vector>
using namespace std;

struct MembersDto findByMemberId(char id[]);

