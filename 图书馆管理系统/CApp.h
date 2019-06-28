#pragma once
#include"CBook.h"
#include"CUser.h"
#include<list>
using namespace std;
class CApp
{
private:
	char currentUserName[20];
	list<CBook> bookList;
	list<CUser> userList;
public:
	void ShowMain();
	bool logon();
	bool login();
	bool isFindUser(const char* name);
	bool isPwdRight(const char* pwd);
	void inputPassword(char* passwd);
	bool DisplayFirstPage();
	bool LoadData();
	list<CUser>::iterator FindUser(const char* n);
};

