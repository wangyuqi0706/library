#pragma once
#include"CBook.h"
typedef struct a
{
	tm bTime;//����ʱ��
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
	BorrowedBook bBookList[10];//�û�������Ϣ
	bool borrow(const char* bookname);
};
class CAdmin : public CUser
{
public:
	//bool Display;
};
