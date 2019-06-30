#include "CApp.h"
#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;
CApp::CApp()
{
	admin.SetName("Admin");
	admin.SetPasswd("0000");

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
		char phone[12];
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
		if (isFindUser(tname) == false&& strcmp(tname, admin.GetName()) != 0)
		{
			cout << "���û�������!" << endl;
			system("pause");
			continue;
		}
		cout << "����:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
		if (strcmp(tname, admin.GetName()) == 0 && strcmp(tpasswd, admin.GetPasswd())==0)
		{
			cout << "��½�ɹ�" << endl;
				strcpy(currentUserName, tname);
				system("pause");
				return true;
		}
		auto i = FindUser(tname);

		if (strcmp(tpasswd, (*i).GetPasswd()) == 0)
		{
			cout << "��½�ɹ�" << endl;
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
	if (len <= 6)
	{
		cout << "���볤�ȹ��̣�" << endl;
		return false;
	}
	if (len>= 18)
	{
		cout << "���볤�ȹ�����" << endl;
		return false;
	}
	for (int i = 0; i < len-1; i++)
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


bool CApp::DisplayFirstPage()
{
	ShowMain();
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
		if (login() == true)
			return false;
		break;
	case 2:
		logon();
		break;
	case 0:
		return false;
		break;
	default:
		cout << "��������ȷ��ָ��" << endl;
		break;
	}
	return true;// TODO: �ڴ˴����ʵ�ִ���.
}


bool CApp::LoadData()
{
	fstream fp("data.dat", ios::in | ios::binary);
	if (fp.is_open() == false)
	{
		fp.open("data.dat", ios::out | ios::binary);
		fp.close();
		fp.open("data.dat", ios::in | ios::binary);
	}

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


bool CApp::DisplayAdminMenu()
{
	system("cls");
	cout << "***************************************����Ա�˵�*******************************************" << endl;
	cout << "                               1.��ɾ�鼮��Ϣ" << endl;
	cout << "                               2.����δ����ѯ" << endl;
	cout << "                               3.�ֶ��黹" << endl;
	cout << "                               4.�û����Ĳ�ѯ" << endl;
	cout << "                               5.�û���Ϣ��ѯ�޸�" << endl;
	cout << "                               6.�ݲز�ѯ" << endl;
	cout << "                               7.�������ɽ�" << endl;
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
	case 6:
		break;
	case 7:
		break;
	case 0:
		return false;
	default:
		break;
	}

	// TODO: �ڴ˴����ʵ�ִ���.
	return true;
}


bool CApp::DisplayReaderMenu()
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
	return false;
}

bool CApp::AddBookInfo()
{

	return true;
}

bool CApp::DisplayAllBooks()
{
	return false; cout << "������\t����\t����\t\t����\t����\tԤԼ��\t�ֿ����\t�ܿ����" << endl;
	for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
		cout << (*blst).book_id << "\t";
		cout << (*blst).kind << "\t";
		cout << (*blst).name << "\t\t";
		cout << (*blst).author << "\t";
		cout << (*blst).price << "\t";
		cout << (*blst).appointment << "\t";
		cout << (*blst).now_sum << "\t";
		cout << (*blst).sum << endl;
	}
	return true;

}

list<CBook>::iterator CApp::Search_BookPos_WithAB(char thebook[15], char theauthor[15])
{
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		if ((strcmp(thebook, (*i).name)) == 0 && (strcmp(theauthor, (*i).author) == 0))
		{
			cout << "�ҵ�����" << endl;
			return i;
		}
		else
		{
			cout << "δ�ҵ�����" << endl;
			return bookList.end();
		}
	}
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
