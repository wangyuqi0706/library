#pragma once
#include"CBook.h"
#include"CUser.h"
#include<list>
#include<iomanip>
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
	void DisplayOverDueBook(CReader &a);
	void ReviseReader();//修改读者信息（包括缴纳金的支付清零）
	char* GetAdminName();
	void ShowMain();
	void ReturnBook(CReader& a);
	void LostReturnBook(); //遗失归还含滞纳金计算

	bool logon();
	bool login();
	bool isFindUser(const char* name);
	bool isPwdRight(const char* pwd);
	void inputPassword(char* passwd);
	bool DisplayAllOverDueUser();
	int DisplayFirstPage();
	bool LoadData();
	void BorrowBook(CReader &a);
	void RevertByAdmin(CReader a);//管理员手动归还
	list<CReader>::iterator FindUser(const char* n);
	char* GetCurUserName();
	int DisplayAdminMenu();
	int DisplayReaderMenu();
	void Search_BookPos_WithKind(char Kind[15]);//检索出图书馆所有同类型书籍
	void AdminReturnBook();//还书


	bool AddBookInfo();//添加书籍信息
	bool ChangeBookInfo();//管理员手动归还
	bool DisplayUser_bBook();//显示某用户所借图书
	bool DisplayUser_bBook(const char * toSrchName);
	bool DisplayAllBooks();//所有馆藏书籍
	list<CBook>::iterator FindBook(int bookid);
	list<CBook>::iterator Search_BookPos_WithAB(char thebook[50], char theauthor[50]);
	void DeleteBook();
	bool SaveData();
	void printfbook(std::list<CBook>::iterator);
	void PrintTitle();
};

