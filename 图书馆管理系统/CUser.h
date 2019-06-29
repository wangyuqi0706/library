#pragma once
#include"CBook.h"
typedef struct a
{
	tm bTime;
	//std::vector<char[20]> bBookList;
}BorrowedBook;
class CUser
{
protected:
	char name[20];
	char phone[15];
	char pwd[15];
	BorrowedBook bBookList;
public:
	void SetName(const char* n);
	char* GetName();
	void SetPasswd(const char* tpwd);
	char* GetPasswd();
};
class CReader :public CUser
{
	bool borrow(const char* bookname);
};
class CAdmin : public CUser
{
public:
	bool AddBookInfo();
	bool DisplayOverDueUser();
	bool RevertByAdmin();
	//bool Display;
};
