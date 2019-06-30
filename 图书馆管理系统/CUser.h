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
	CReader();
	vector<BorrowedBook> bBookList;//用户借书信息
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

	void AddBook(CBook NewBook);  //增加图书
	void DeleteBook(char bookname[15], char author[15]);//删除图书
	void ReviseBook(char name[15], char author[15]);//修改某本书的信息
	void PrintBook(CBook a);//输出某本书的所有信息
	void ShowAllBooks(); //输出系统所有图书

};
