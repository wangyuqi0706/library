#include "CApp.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#define QUIT -1
#define NEXT 1
#define STAY 0
#define LOGOUT 2
using namespace std;
CApp::~CApp()
{
	
	SaveData();
}
CApp::CApp()
{
	admin.SetName("A");
	admin.SetPasswd("0");
	strcpy(currentUserName, "");
	LoadData();
}
char* CApp::GetAdminName()
{
	return admin.GetName();
}
void CApp::ShowMain()
{

	system("cls");
	cout << "****************************************************************************************" << endl;
	cout << "                               1.��¼" << endl;
	cout << "                               2.ע��" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "�������ѡ���ܣ�";
}

bool CApp::logon()
{
	CReader user;
	char tname[30] = { 0 };
	char tpwd[20] = { 0 };
	char phone[12] = { 0 };
	int x = sizeof(tpwd);
	while (1)
	{
		system("cls");
		cout << "***************************************�û�ע��*******************************************" << endl;
		cout << "�û�����";
		cin >> tname;
		if (isFindUser(tname) == true)
		{
			cout << "���û����ѱ�ע�ᣡ" << endl;
			system("pause");
			continue;
		}
		cout << "����绰���룺";
		cin >> phone;
		cout << "�������룺";
		inputPassword(tpwd);
		if (isPwdRight(tpwd) == false)
		{
			system("pause");
			continue;
		}
		cout << "ȷ�����룺";
		char tpwd2[20] = { 0 };
		inputPassword(tpwd2);
		if (strcmp(tpwd, tpwd2) == 0)
		{
			break;
		}
		else
		{
			cout << "������������벻һ��!" << endl;
			system("pause");
			continue;
		}

	}
	cout << "�û� " << tname << " ע��ɹ�" << endl;
	system("pause");
	user.SetName(tname);
	user.SetPasswd(tpwd);
	user.SetPhone(phone);
	userList.push_back(user);
	return true;
}

bool CApp::login()
{
	while (1)
	{
		system("cls");
		cout << "***************************************�û���¼*******************************************" << endl;
		cout << "�û�����";
		char tname[20] = { 0 };
		cin >> tname;
		if (isFindUser(tname) == false && strcmp(tname, admin.GetName()) != 0)
		{
			cout << "���û�������!�Ƿ�ע�᣿y/n" << endl;
			char k1;
			cin >> k1;
			switch (k1)
			{
			case 'y':logon(); break;
			case 'n':return false; 
			default:
				cout << "��������ȷ�����" << endl;
				break;
			}
			continue;
		}
		cout << "����:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
		if (strcmp(tname, admin.GetName()) == 0 && strcmp(tpasswd, admin.GetPasswd()) == 0)
		{
			cout << "����Ա "<<admin.GetName()<<" ��¼�ɹ�" << endl;
			strcpy(currentUserName, tname);
			system("pause");
			return true;
		}
		auto i = FindUser(tname);

		if (strcmp(tpasswd, (*i).GetPasswd()) == 0)
		{
			cout << "��¼�ɹ�" << endl;
			strcpy(currentUserName, tname);
			system("pause");
			return true;
		}
		else
		{
			cout << "�����������" << endl;
			system("pause");
			continue;
		}
	}
	return false;
}


bool CApp::isFindUser(const char* cname)
{
	for (auto i = userList.begin(); i != userList.end(); i++)
	{
		if (strcmp(cname, (*i).GetName()) == 0)
			return true;
	}
	// TODO: �ڴ˴����ʵ�ִ���.
	return false;
}




bool CApp::isPwdRight(const char* pwd)
{
	int len = strlen(pwd);
	if (len <= 7)
	{
		cout << "���볤�ȹ��̣�" << endl;
		return false;
	}
	if (len >= 18)
	{
		cout << "���볤�ȹ�����" << endl;
		return false;
	}
	for (int i = 0; i < len - 1; i++)
	{

		if (((pwd[i] >= '0' && pwd[i] <= '9') || (pwd[i] >= 'a' && pwd[i] <= 'z') || (pwd[i] >= 'A' && pwd[i] <= 'Z') || (pwd[i] == 0)) == 0)
		{
			cout << "�����뺬�зǷ��ַ���" << endl;
			return false;
		}
	}

	// TODO: �ڴ˴����ʵ�ִ���.
	return true;
}


void CApp::inputPassword(char* passwd)
{
	int i = 0;
	passwd[i] = _getch();
	while (passwd[i] != '\r') {
		if (passwd[i] != '\b') {
			cout << "*";
			i++;
		}
		else {
			if (i != 0) {
				cout << "\b \b";
				i--;
			}
		}
		passwd[i] = _getch();
	}
	passwd[i] = '\0';
	cout << endl;
}


int CApp::DisplayFirstPage()
{
	ShowMain();
	char key;
	cin >> key;
	switch (key)
	{
	case '1':
		if (login() == true)
			return NEXT;
		break;
	case '2':
		logon();
		return STAY;
		break;
	case '0':
		return QUIT;
		break;
	default:
		cout << "��������ȷ��ָ��" << endl;
		system("pause");
		return 1;
		break;
	}
	return 1;// TODO: �ڴ˴����ʵ�ִ���.
}


bool CApp::LoadData()
{
	fstream fp;
	fp.open("user_data.dat", ios::in | ios::binary);
	if (fp.is_open() == false)
	{
		fp.open("user_data.dat", ios::out | ios::binary);
		fp.close();
		fp.open("user_data.dat", ios::in | ios::binary);
	}
	CReader s;
	while (fp.read((char*)& s, sizeof(s)))
		userList.push_back(s);
	fp.close();

	fp.open("book_data.dat", ios::in | ios::binary);
	if (fp.is_open() == false)
	{
		fp.open("book_data.dat", ios::out | ios::binary);
		fp.close();
		fp.open("book_data.dat", ios::in | ios::binary);
	}
	CBook b;
	while (fp.read((char*)& b, sizeof(b)))
		bookList.push_back(b);
	fp.close();
	return false;
}


list<CReader>::iterator CApp::FindUser(const char* n)
{
	for (auto i = userList.begin(); i != userList.end(); i++)
	{
		if (strcmp(n, (*i).GetName()) == 0)
			return i;
	}
	return userList.end();
}


char* CApp::GetCurUserName()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return currentUserName;
}


int CApp::DisplayAdminMenu()
{
	system("cls");
	cout << "***************************************����Ա�˵�*******************************************" << endl;
	cout << "                               1.�����鼮��Ϣ" << endl;
	cout << "                               2.ɾ���鼮��Ϣ" << endl;
	cout << "                               3.�޸��鼮���" << endl;
	cout << "                               4.����δ����ѯ" << endl;
	cout << "                               5.��ʾ�����鼮��Ϣ" << endl;
	cout << "                               6.�˳���¼" << endl;

	cout << "                               0.�˳�" << endl;
	cout << "�������ѡ���ܣ�";
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
		AddBookInfo();
		return STAY;
		break;
	case 2:
		DeleteBook();
		return STAY;
		break;
	case 3:
		return STAY;
		break;
	case 4:
		return STAY;
		break;
	case 5:
		DisplayAllBooks();
		return STAY;
		break;
	case 6:
		return LOGOUT;
		break;
	case 7:
		return STAY;
		break;
	case 0:
		return QUIT;
	default:
		break;
	}
	return 1;
}


int CApp::DisplayReaderMenu()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	system("cls");
	cout << "***************************************�û��˵�*******************************************" << endl;
	cout << "                               1.�����鼮" << endl;
	cout << "                               2.�ѽ����鼮" << endl;
	cout << "                               3.ԤԼ�鼮" << endl;
	cout << "                               4.���ɽ��ѯ" << endl;
	cout << "                               5.�鼮��ѯ" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "�������ѡ���ܣ�";
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 0:
		return false;
		break;
	default:
		break;
	}
	return 1;
}

bool CApp::AddBookInfo()
{

	char name[50], kind[50], author[20];
	cout << "������Ҫ��ӵ�����������" << endl;
	cin >> name;
	cin >> author;
	auto i = Search_BookPos_WithAB(name, author);

	
	if(i==bookList.end()||bookList.size()==0)//���û�и���
	{
		CBook newbook;
		int sum;
		cout << "������ͼ������ţ�" << endl;
		cin >> newbook.book_id;
		cout << "������ͼ���ܿ�������" << endl;
		cin >> newbook.sum;
		cout << "������ͼ�����ࣺ" << endl;
		cin >> newbook.kind;
		//cout << "������ͼ��������" << endl;
		strcpy(newbook.name, name);
		//cout << "������ͼ�����ߣ�" << endl;
		strcpy(newbook.author, author);
		cout << "������ͼ���鼮���ۣ�" << endl;
		cin >> newbook.price;
		newbook.now_sum = newbook.sum;
		newbook.appointment = 0;
		bookList.push_back(newbook);
		cout << "�洢�ɹ�" << endl;
	}
	else
	{
			cout << "��������鼮�Ѵ��ڣ���ȥ�޸��鼮������" << endl;
	}
	return true;
}

bool CApp::DispalyUser_bBook()
{
	char toSrchName[20];
	int cnt = 0;
	cin >> toSrchName;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if (strcmp((*usrlst).GetName(), toSrchName) == 0) {
			cout << "������\t����\t����\t\t����\t����\t����ʱ��" << endl;
			for (int i = 0; i < 10; i++) {
				if ((*usrlst).bBookList[i].bBookId != 0) {
					cnt++;
					cout << (*usrlst).bBookList[i].bBookId << "\t";
					for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
						if ((*blst).book_id == (*usrlst).bBookList[i].bBookId) {
							cout << (*blst).kind << "\t";
							cout << (*blst).name << "\t\t";
							cout << (*blst).author << "\t";
							cout << (*blst).price << "\t";
							break;
						}
					}
					cout << (*usrlst).bBookList[i].bTime.tm_year << "-" << (*usrlst).bBookList[i].bTime.tm_mon << "-" << (*usrlst).bBookList[i].bTime.tm_mday << "\t";
				}
			}
			cout << "����������" << cnt << " ��" << endl;
			break;
		}
	}
	return true;

}

bool CApp::DisplayAllBooks()
{
	cout << "������\t����\t����\t\t\t����\t����\tԤԼ��\t�ֿ����\t�ܿ����" << endl;
	for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
		cout << (*blst).book_id << "\t";
		cout << (*blst).kind << "\t";
		cout << (*blst).name << "\t\t\t";
		cout << (*blst).author << "\t";
		cout << (*blst).price << "\t";
		cout << (*blst).appointment << "\t";
		cout << (*blst).now_sum << "\t";
		cout << (*blst).sum << endl;
	}
	system("pause");
	return true;

}

list<CBook>::iterator CApp::FindBook(int bookid)
{
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		if ((*i).book_id == bookid)
			return i;
	}

}

list<CBook>::iterator CApp::Search_BookPos_WithAB(char thebook[50], char theauthor[50])
{
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		if ((strcmp(thebook, (*i).name)) == 0 && (strcmp(theauthor, (*i).author) == 0))
		{
			//cout << "�ҵ�����" << endl;
			return i;
		}
		else
		{
			//cout << "δ�ҵ�����" << endl;
		}
	}
	return bookList.end();
}

void CApp::DeleteBook()
{
	char bookname[15];
	char author[15];
	cout << "���������������ߣ�" << endl;
	cin >> bookname >> author;
	auto i = Search_BookPos_WithAB(bookname, author);
	if (i != bookList.end())
	{
		bookList.erase(i);
		cout << "ɾ������ɹ���" << endl;
	}
	else
	{
		cout << "�����ڸ��飬�޷�ɾ����" << endl;
	}
}


bool CApp::SaveData()
{
	fstream fp;
	CReader r;
	CBook b;
	fp.open("user_data.dat", ios::binary | ios::out);
	for (auto i = userList.begin(); i != userList.end(); i++)
	{
		fp.write((char*) & (*i), sizeof(r));
	}
	fp.close();
	fp.open("book_data.dat", ios::binary | ios::out);
	for (auto i = userList.begin(); i != userList.end(); i++)
	{
		fp.write((char*) & (*i), sizeof(b));
	}
	fp.close();
	return true;
}
