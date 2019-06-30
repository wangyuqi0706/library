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
	list<CReader> userList;
	CAdmin admin;
public:
	~CApp();
	CApp();
	void ShowMain();
	bool logon();
	bool login();
	bool isFindUser(const char* name);
	bool isPwdRight(const char* pwd);
	void inputPassword(char* passwd);
	bool DisplayFirstPage();
	bool LoadData();
	list<CReader>::iterator FindUser(const char* n);
	char* GetCurUserName();
	bool DisplayAdminMenu();
	bool DisplayReaderMenu();
	bool AddBookInfo();//添加书籍信息
	bool DisplayOverDueUser();//显示逾期用户
	bool RevertByAdmin();//管理员手动归还
	bool DispalyUser_bBook();//显示某用户所借图书
	bool DisplayAllBooks();//所有馆藏书籍
	void AddBook(CBook NewBook);  //增加图书
	void DeleteBook();//删除图书
	bool ReviseBook(char name[15], char author[15]);//修改某本书的信息
	void PrintBook(CBook a);//输出某本书的所有信息
	void ShowAllBooks(); //输出系统所有图书
	list<CBook>::iterator Search_BookPos_WithAB(char thebook[15], char theauthor[15]);

	void SaveData();
};

