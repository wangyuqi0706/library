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
	void ReviseReader();//�޸Ķ�����Ϣ���������ɽ��֧�����㣩
	char* GetAdminName();
	void ShowMain();
	void ReturnBook(CReader& a);
	void LostReturnBook(); //��ʧ�黹�����ɽ����

	bool logon();
	bool login();
	bool isFindUser(const char* name);
	bool isPwdRight(const char* pwd);
	void inputPassword(char* passwd);
	bool DisplayAllOverDueUser();
	int DisplayFirstPage();
	bool LoadData();
	void BorrowBook(CReader &a);
	void RevertByAdmin(CReader a);//����Ա�ֶ��黹
	list<CReader>::iterator FindUser(const char* n);
	char* GetCurUserName();
	int DisplayAdminMenu();
	int DisplayReaderMenu();
	void Search_BookPos_WithKind(char Kind[15]);//������ͼ�������ͬ�����鼮
	void AdminReturnBook();//����


	bool AddBookInfo();//����鼮��Ϣ
	bool ChangeBookInfo();//����Ա�ֶ��黹
	bool DisplayUser_bBook();//��ʾĳ�û�����ͼ��
	bool DisplayUser_bBook(const char * toSrchName);
	bool DisplayAllBooks();//���йݲ��鼮
	list<CBook>::iterator FindBook(int bookid);
	list<CBook>::iterator Search_BookPos_WithAB(char thebook[50], char theauthor[50]);
	void DeleteBook();
	bool SaveData();
	void printfbook(std::list<CBook>::iterator);
	void PrintTitle();
};

