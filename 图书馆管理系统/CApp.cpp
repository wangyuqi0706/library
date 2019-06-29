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
	cout << "                               1.登录" << endl;
	cout << "                               2.注册" << endl;
	cout << "                               3.还书" << endl;
	cout << "                               0.退出" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "输入序号选择功能：";
}

bool CApp::logon()
{
	CReader user;
	char tname[30] = { 0 };
	char tpwd[16] = { 0 };

	while (1)
	{
		system("cls");
		cout << "***************************************用户注册*******************************************" << endl;
		cout << "用户名：" << endl;
		cin >> tname;
		if (isFindUser(tname) == true)
		{
			cout << "该用户名已被注册！" << endl;
			system("pause");
			continue;
		}
		cout << "输入密码：";
		inputPassword(tpwd);
		if (isPwdRight(tpwd) == false)
		{
			cout << "该密码含有非法字符！" << endl;
			system("pause");
			continue;
		}
		cout << "确认密码：";
		char tpwd2[16] = { 0 };
		inputPassword(tpwd2);
		if (strcmp(tpwd, tpwd2) == 0)
		{
			break;
		}
		else
		{
			cout << "两次输入的密码不一致!" << endl;
			system("pause");
			continue;
		}

	}
	cout << "用户 " << tname << " 注册成功" << endl;
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
		cout << "***************************************用户登录*******************************************" << endl;
		cout << "用户名：";
		char tname[20] = { 0 };
		cin >> tname;
		if (isFindUser(tname) == false)
		{
			cout << "该用户不存在!" << endl;
			continue;
		}
		cout << "密码:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
		auto i = FindUser(tname);
		if (strcmp(tpasswd, (*i).GetPasswd()) == 0)
		{
			cout << "登陆成功" << endl;
			strcpy(currentUserName, tname);
			system("pause");
			return true;
		}
		else
		{
			cout << "密码输入错误！" << endl;
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
	// TODO: 在此处添加实现代码.
	return false;
}




bool CApp::isPwdRight(const char* pwd)
{
	for (int i = 0; i < sizeof(pwd) / sizeof(pwd[0])-1; i++)
	{
		if (((pwd[i] >= '0' && pwd[i] <= '9') || (pwd[i] >= 'a' && pwd[i] <= 'z') || (pwd[i] >= 'A' && pwd[i] <= 'Z') || (pwd[i] == 0)) == 0)
			return false;
	}
	// TODO: 在此处添加实现代码.
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
		cout << "请输入正确的指令" << endl;
		break;
	}
	return true;// TODO: 在此处添加实现代码.
}


bool CApp::LoadData()
{
	fstream fp("data.dat", ios::in | ios::binary);
	// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
	return currentUserName;
}
