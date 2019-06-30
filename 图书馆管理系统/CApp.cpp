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
	cout << "                               1.登录" << endl;
	cout << "                               2.注册" << endl;
	cout << "                               0.退出" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "输入序号选择功能：";
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
		cout << "***************************************用户注册*******************************************" << endl;
		cout << "用户名：";
		cin >> tname;
		if (isFindUser(tname) == true)
		{
			cout << "该用户名已被注册！" << endl;
			system("pause");
			continue;
		}
		cout << "输入电话号码：";
		char phone[12];
		cin >> phone;
		cout << "输入密码：";
		inputPassword(tpwd);
		if (isPwdRight(tpwd) == false)
		{
			system("pause");
			continue;
		}
		cout << "确认密码：";
		char tpwd2[20] = { 0 };
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
		if (isFindUser(tname) == false&& strcmp(tname, admin.GetName()) != 0)
		{
			cout << "该用户不存在!" << endl;
			system("pause");
			continue;
		}
		cout << "密码:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
		if (strcmp(tname, admin.GetName()) == 0 && strcmp(tpasswd, admin.GetPasswd())==0)
		{
			cout << "登陆成功" << endl;
				strcpy(currentUserName, tname);
				system("pause");
				return true;
		}
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
	int len = strlen(pwd);
	if (len <= 6)
	{
		cout << "密码长度过短！" << endl;
		return false;
	}
	if (len>= 18)
	{
		cout << "密码长度过长！" << endl;
		return false;
	}
	for (int i = 0; i < len-1; i++)
	{
		
		if (((pwd[i] >= '0' && pwd[i] <= '9') || (pwd[i] >= 'a' && pwd[i] <= 'z') || (pwd[i] >= 'A' && pwd[i] <= 'Z') || (pwd[i] == 0)) == 0)
		{
			cout << "该密码含有非法字符！" << endl;
			return false;
		}
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
		cout << "请输入正确的指令" << endl;
		break;
	}
	return true;// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
	return currentUserName;
}


bool CApp::DisplayAdminMenu()
{
	system("cls");
	cout << "***************************************管理员菜单*******************************************" << endl;
	cout << "                               1.增删书籍信息" << endl;
	cout << "                               2.逾期未还查询" << endl;
	cout << "                               3.手动归还" << endl;
	cout << "                               4.用户借阅查询" << endl;
	cout << "                               5.用户信息查询修改" << endl;
	cout << "                               6.馆藏查询" << endl;
	cout << "                               7.缴纳滞纳金" << endl;
	cout << "                               0.退出" << endl;
	cout << "输入序号选择功能：";
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

	// TODO: 在此处添加实现代码.
	return true;
}


bool CApp::DisplayReaderMenu()
{
	// TODO: 在此处添加实现代码.
	system("cls");
	cout << "***************************************用户菜单*******************************************" << endl;
	cout << "                               1.借阅书籍" << endl;
	cout << "                               2.已借阅书籍" << endl;
	cout << "                               3.预约书籍" << endl;
	cout << "                               4.滞纳金查询" << endl;
	cout << "                               5.书籍查询" << endl;
	cout << "                               0.退出" << endl;
	cout << "输入序号选择功能：";
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
	return false; cout << "检索号\t种类\t书名\t\t作者\t定价\t预约量\t现库存量\t总库存量" << endl;
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
			cout << "找到此书" << endl;
			return i;
		}
		else
		{
			cout << "未找到该书" << endl;
			return bookList.end();
		}
	}
}

void CApp::DeleteBook()
{
	char bookname[15];
	char author[15];
	cout << "请输入书名与作者！" << endl;
	cin >> bookname >> author;
	auto i = Search_BookPos_WithAB(bookname, author);
	if (i != bookList.end())
	{
		bookList.erase(i);
		cout << "删除此书成功！" << endl;
	}
	else
	{
		cout << "不存在该书，无法删除。" << endl;
	}
}
