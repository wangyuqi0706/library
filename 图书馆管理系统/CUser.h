#pragma once
#include"CBook.h"
#include<vector>
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
	CReader();
	std::vector<BorrowedBook> bBookList;//�û�����
	bool borrow(const char* bookname);
	bool SetPhone(const char* ph);
};
class CAdmin : public CUser
{
public:
	//bool Display;
};



