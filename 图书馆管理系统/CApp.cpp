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
	char phone[12] = { 0 };
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
	user.SetPhone(phone);
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
		if (isFindUser(tname) == false && strcmp(tname, admin.GetName()) != 0)
		{
			cout << "该用户不存在!是否注册？y/n" << endl;
			char k1;
			cin >> k1;
			switch (k1)
			{
			case 'y':logon(); break;
			case 'n':return false; 
			default:
				cout << "请输入正确的命令！" << endl;
				break;
			}
			continue;
		}
		cout << "密码:";
		char tpasswd[20] = { 0 };
		inputPassword(tpasswd);
		if (strcmp(tname, admin.GetName()) == 0 && strcmp(tpasswd, admin.GetPasswd()) == 0)
		{
			cout << "管理员 "<<admin.GetName()<<" 登录成功" << endl;
			strcpy(currentUserName, tname);
			system("pause");
			return true;
		}
		auto i = FindUser(tname);

		if (strcmp(tpasswd, (*i).GetPasswd()) == 0)
		{
			cout << "登录成功" << endl;
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
	if (len <= 7)
	{
		cout << "密码长度过短！" << endl;
		return false;
	}
	if (len >= 18)
	{
		cout << "密码长度过长！" << endl;
		return false;
	}
	for (int i = 0; i < len - 1; i++)
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
		cout << "请输入正确的指令" << endl;
		system("pause");
		return 1;
		break;
	}
	return 1;// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
	return currentUserName;
}


int CApp::DisplayAdminMenu()
{
	system("cls");
	cout << "***************************************管理员菜单*******************************************" << endl;
	cout << "                               1.增加书籍信息" << endl;
	cout << "                               2.删除书籍信息" << endl;
	cout << "                               3.修改书籍库存" << endl;
	cout << "                               4.逾期未还查询" << endl;
	cout << "                               5.显示所有书籍信息" << endl;
	cout << "                               6.退出登录" << endl;

	cout << "                               0.退出" << endl;
	cout << "输入序号选择功能：";
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
	return 1;
}

bool CApp::AddBookInfo()
{

	char name[50], kind[50], author[20];
	cout << "请输入要添加的书名、作者" << endl;
	cin >> name;
	cin >> author;
	auto i = Search_BookPos_WithAB(name, author);

	
	if(i==bookList.end()||bookList.size()==0)//如果没有该书
	{
		CBook newbook;
		int sum;
		cout << "请输入图书检索号：" << endl;
		cin >> newbook.book_id;
		cout << "请输入图书总库存存量：" << endl;
		cin >> newbook.sum;
		cout << "请输入图书种类：" << endl;
		cin >> newbook.kind;
		//cout << "请输入图书书名：" << endl;
		strcpy(newbook.name, name);
		//cout << "请输入图书作者：" << endl;
		strcpy(newbook.author, author);
		cout << "请输入图书书籍定价：" << endl;
		cin >> newbook.price;
		newbook.now_sum = newbook.sum;
		newbook.appointment = 0;
		bookList.push_back(newbook);
		cout << "存储成功" << endl;
	}
	else
	{
			cout << "您输入的书籍已存在，请去修改书籍数量。" << endl;
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
			cout << "检索号\t种类\t书名\t\t作者\t定价\t借阅时间" << endl;
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
			cout << "借阅总数：" << cnt << " 本" << endl;
			break;
		}
	}
	return true;

}

bool CApp::DisplayAllBooks()
{
	cout << "检索号\t种类\t书名\t\t\t作者\t定价\t预约量\t现库存量\t总库存量" << endl;
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
			//cout << "找到此书" << endl;
			return i;
		}
		else
		{
			//cout << "未找到该书" << endl;
		}
	}
	return bookList.end();
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
