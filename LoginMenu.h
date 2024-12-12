#pragma once
class LoginMenu
{
private:
	static const int SIGNIN = 9;
	static const int CANCLE = 11;
public:
	void printSrc();
	void logout();
};

struct UserDto {
	char user_id[20];
	char name[50];
	char role[20];
};

// 전역 변수
extern UserDto currentUser;


