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
	bool AddBookInfo();//����鼮��Ϣ
	bool DisplayOverDueUser();//��ʾ�����û�
	bool RevertByAdmin();//����Ա�ֶ��黹
	bool DispalyUser_bBook();//��ʾĳ�û�����ͼ��
	bool DisplayAllBooks();//���йݲ��鼮
	void AddBook(CBook NewBook);  //����ͼ��
	void DeleteBook();//ɾ��ͼ��
	bool ReviseBook(char name[15], char author[15]);//�޸�ĳ�������Ϣ
	void PrintBook(CBook a);//���ĳ�����������Ϣ
	void ShowAllBooks(); //���ϵͳ����ͼ��
	list<CBook>::iterator Search_BookPos_WithAB(char thebook[15], char theauthor[15]);

	void SaveData();
};

