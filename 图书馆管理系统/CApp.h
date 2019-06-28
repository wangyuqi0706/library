#pragma once
#include"CBook.h"
#include"CUser.h"
#include<list>
using namespace std;
class CApp
{
private:
	CUser* currentUser=0;
	list<CBook> bookList;
	list<CUser> userList;
public:
	void ShowMain();
	bool logon();
	bool login();
	bool FindUser(const char* name);
	bool isPwdRight(const char* pwd);
	void inputPassword(char* passwd);
	bool DisplayFirstPage();
	bool LoadData();
};

