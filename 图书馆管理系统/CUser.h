#pragma once
#include"CBook.h"
#include<vector>
typedef struct a
{
	tm bTime;//����ʱ��
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
	BorrowedBook bBookList[10];//�û�����
	bool SetPhone(const char* ph);
	int HasPenalty();// ����0���������ɽ𣻷���1�������ɽ����������鼮δ��������2�������ɽ��ҿɲ�ѯ
};
class CAdmin : public CUser
{
public:
	//bool Display;
};



