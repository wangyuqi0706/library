#pragma once
#include"CBook.h"
#include<vector>
typedef struct a
{
	tm bTime;//借阅时间
	int bBookId=0;//
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
	CReader();
	BorrowedBook bBookList[10];//用户借书
	bool SetPhone(const char* ph);
	int HasPenalty();// 返回0，则无滞纳金；返回1，有滞纳金，且有逾期书籍未还；返回2，有滞纳金，且可查询
};
class CAdmin : public CUser
{
public:
	//bool Display;
};



