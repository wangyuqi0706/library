#include "CApp.h"
#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;
CApp::CApp()
{
	admin;
	admin.SetName("Admin");
	admin.SetPasswd("0000");
}
void CApp::ShowMain()
{

	system("cls");
	cout << "****************************************************************************************" << endl;
	cout << "                               1.��¼" << endl;
	cout << "                               2.ע��" << endl;
	cout << "                               3.����" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "�������ѡ���ܣ�";
}

bool CApp::logon()
{
	CReader user;
	char tname[30] = { 0 };
	char tpwd[16] = { 0 };

	while (1)
	{
		system("cls");
		cout << "***************************************�û�ע��*******************************************" << endl;
		cout << "�û�����" << endl;
		cin >> tname;
		if (isFindUser(tname) == true)
		{
			cout << "���û����ѱ�ע�ᣡ" << endl;
			system("pause");
			continue;
		}
		cout << "�������룺";
		inputPassword(tpwd);
		if (isPwdRight(tpwd) == false)
		{
			cout << "�����뺬�зǷ��ַ���" << endl;
			system("pause");
			continue;
		}
		cout << "ȷ�����룺";
		char tpwd2[16] = { 0 };
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
		if (isFindUser(tname) == false)
		{
			cout << "���û�������!" << endl;
			continue;
		}
		cout << "����:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
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
	for (int i = 0; i < sizeof(pwd) / sizeof(pwd[0])-1; i++)
	{
		if (((pwd[i] >= '0' && pwd[i] <= '9') || (pwd[i] >= 'a' && pwd[i] <= 'z') || (pwd[i] >= 'A' && pwd[i] <= 'Z') || (pwd[i] == 0)) == 0)
			return false;
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
	case 3:
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
	// TODO: �ڴ˴����ʵ�ִ���.
	return false;
}


list<CUser>::iterator CApp::FindUser(const char* n)
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
