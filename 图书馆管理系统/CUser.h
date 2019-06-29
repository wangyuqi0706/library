#pragma once
#include"CBook.h"
typedef struct a
{
	tm bTime;//借阅时间
	int bBookId;//
}BorrowedBook;
class CUser
{
protected:
	char name[20];
	char phone[15];
	char pwd[20];
public:
	void SetName(const char* n);
	char* GetName();
	void SetPasswd(const char* tpwd);
	char* GetPasswd();
};
class CReader :public CUser
{
public:
	BorrowedBook bBookList[10];//用户借书信息
	bool borrow(const char* bookname);
};
class CAdmin : public CUser
{
public:
	bool AddBookInfo();//添加书籍信息
	bool DisplayOverDueUser();//显示逾期用户
	bool RevertByAdmin();//管理员手动归还
	bool DispalyUser_bBook();//显示某用户所借图书
	bool DisplayAllBooks();//所有馆藏书籍
	//bool Display;
};
