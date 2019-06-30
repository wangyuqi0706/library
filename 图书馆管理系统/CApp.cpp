#include "CApp.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
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
void CApp::DisplayOverDueBook(const CReader& a)
{
	int x = a.HasPenalty;
	if (x != 1)
	{
		cout << "无逾期书籍！" << endl;
	}
	else
	{
		time_t now_time = time(NULL);//获取系统时间
		tm* t_tm = localtime(&now_time);
		int num = 0;
		for (int i = 0; i < 10; i++)
		{
			if (t_tm->tm_year > a.bBookList[i].bTime.tm_year)//是否有逾期未还
			{
				int daynum = t_tm->tm_yday + (365 - a.bBookList[i].bTime.tm_yday);
				if (daynum > 30)
				{
					list<CBook>::iterator it = FindBook(a.bBookList[i].bBookId);
					printfbook(it);
				}
			}
			else
			{
				if (t_tm->tm_yday - a.bBookList[i].bTime.tm_yday > 30)//是否有逾期未还
				{
					list<CBook>::iterator it = FindBook(a.bBookList[i].bBookId);
					printfbook(it);
				}
			}
		}
	}

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
			cout << "该用户名已被注册！是否使用其它用户名注册？y/n" << endl;
			char k;
			cin >> k;
			if (k == 'y')
				continue;
			else if (k == 'n')
				return false;
			else
			{
				cout << "请输入y或n,按任意键返回首页" << endl;
				system("pause");
				return false;
			}
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

bool CApp::DisplayAllOverDueUser()
{
	cout << "*****************************************************************************************************" << endl;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if ((*usrlst).HasPenalty() == 1) {
			
			cout << "用户：" << (*usrlst).GetName() << endl;
			cout << "逾期书单：" << endl;
			cout << "\t" << setw(12) << left << "检索号";
			cout << setw(12) << left << "种类";
			cout << setw(30) << left << "书名";
			cout << setw(12) << left << "作者";
			cout << setw(12) << left << "定价";
			cout << "借阅时间" << endl;
			time_t now_time = time(NULL);
			for (int i = 0; i < 10; i++) {
				tm* b_time;
				b_time = &(*usrlst).bBookList[i].bTime;
				time_t borrow_time = mktime(b_time);
				if ((*usrlst).bBookList[i].bBookId != 0 && now_time - borrow_time > 2592000) {
					cout << "\t" << setw(12) << left << (*usrlst).bBookList[i].bBookId;
					for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
						if ((*blst).book_id == (*usrlst).bBookList[i].bBookId) {
							cout << setw(12) << left << (*blst).kind;
							cout << setw(30) << left << (*blst).name;
							cout << setw(12) << left << (*blst).author;
							cout << setw(12) << left << (*blst).price;
							break;
						}
					}
					cout << (*usrlst).bBookList[i].bTime.tm_year + 1900 << "-" << (*usrlst).bBookList[i].bTime.tm_mon + 1 << "-" << (*usrlst).bBookList[i].bTime.tm_mday << endl;
				}
			}
			

		}
	}
	cout << "*****************************************************************************************************" << endl << endl;
	system("pause");
	return true;

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
		return STAY;
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
	CReader r;
	while (fp.read((char*)& r, sizeof(r)))
		userList.push_back(r);
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

void CApp::BorrowBook(CReader &a)
{
	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		if (a.bBookList[i].bBookId != 0)
		{
			x++;
		}
	}
	int y = a.HasPenalty();
	if (y != 0)
	{
		cout << "您有滞纳金未缴纳！请缴纳后再借书。" << endl;
		system("pause");
	}
	else
	{
		if (x >= 10)
		{
			cout << "您同时最多只能同时借10本书！" << endl;
			system("pause");
		}
		else
		{
			cout << "请输入借阅书籍的检索号：";
			int id_num;
			cin >> id_num;
			auto i = bookList.begin();
			i = FindBook(id_num);//索书号找书
			if (i == bookList.end())
			{
				cout << "您输入的检索号有误！" << endl;
				system("pause");
			}
			else
			{
				if ((*i).now_sum == 0)
				{
					cout << "该书已全部外借！" << endl;
					system("pause");
				}
				else
				{
					int d = 0;
					for (int m = 0; m < 10; m++)
					{
						if (a.bBookList[m].bBookId == id_num)
						{
							d++;
						}
					}
					if (d > 0)
					{
						cout << "您已借阅该书，请勿重复借阅" << endl;
						system("pause");
					}
					else
					{
						for (x = 0; x < 10; x++)
						{

							{
								if (a.bBookList[x].bBookId == 0)
								{
									a.bBookList[x].bBookId = id_num;
									time_t now_time = time(NULL);//获取系统时间
									tm* t_tm = localtime(&now_time);
									a.bBookList[x].bTime = *t_tm;
									break;
								}
							}
						}
						(*i).now_sum--;
						cout << "您已成功借阅 《" << (*i).name << "》 !" << endl;
						system("pause");
					}
				}
			}
		}
	}

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
	cout << "                               6.手动归还" << endl;
	cout << "                               7.退出登录" << endl;
	cout << "                               0.退出" << endl;
	cout << "输入序号选择功能：";
	char key;
	cin >> key;
	switch (key)
	{
	case '1':
		AddBookInfo();
		return STAY;
		break;
	case'2':
		DeleteBook();
		return STAY;
		break;
	case'3':
		RevertByAdmin();
		return STAY;
		break;
	case '4':
		DisplayAllOverDueUser();
		return STAY;
		break;
	case '5':
		DisplayAllBooks();
		return STAY;
		break;
	case '6':
		AdminReturnBook();
		return STAY;
		break;
	case '7':
		return LOGOUT;
		break;
	case '0':
		return QUIT;
	default:
		cout << "请输入正确的指令" << endl;
		system("pause");
		return STAY;
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
	cout << "                               2.查询已借阅书籍" << endl;
	cout << "                               3.滞纳金查询" << endl;
	cout << "                               4.书籍查询" << endl;
	cout << "                               5.逾期书籍查询" << endl;
	cout << "                               0.退出" << endl;
	cout << "输入序号选择功能：";
	int key;
	cin >> key;
	switch (key)
	{
	case 1:
	{
		BorrowBook(*FindUser(currentUserName));
		return STAY;
		break;
	}
	case 2:
		DisplayUser_bBook(currentUserName);
		return STAY;
		break;
	case 3:
		break;
	case 4:
		DisplayAllBooks();
		return STAY;
		break;
	case 5:
		DisplayOverDueBook(*FindUser(currentUserName));
	case 0:
		return QUIT;
		break;
	default:
		cout << "请输入正确的指令" << endl;
		system("pause");
		return STAY;
		break;
	}
	return 1;
}

void CApp::Search_BookPos_WithKind(char Kind[15])
{
	cout << "图书馆主要类型有工科，理科，医学，农学，艺术，人文。" << endl;
	int num = 0;
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		cout << "检索号\t种类\t书名\t\t作者\t定价\t预约量\t现库存量\t总库存量" << endl;
		if ((strcmp(Kind, (*i).kind)) == 0)
		{
			num++;
			printfbook(i);
		}
	}
	if (num == 0)
	{
		cout << "抱歉，图书馆未找到该类型的书籍。" << endl;
	}
	else
	{
		cout << "以为您检索到" << num << "本该类型书籍" << endl;
	}

}

void CApp::AdminReturnBook()
{
	bool exam = false;
	cout << "请输入用户名和归还的索书号" << endl;
	char userid[50];
	int bookid;
	cin >> userid >> bookid;
	auto reader = FindUser(userid);
	if (reader == userList.end())
	{
		cout << "未找到该用户！" << endl;
		system("pause");
	}
	else
	{
		for (int j = 0; j < 10; j++)
		{
			if (((*reader).bBookList[j]).bBookId == bookid)//遍历借书数组
			{
				auto book = FindBook(bookid);
				(*book).now_sum++;//改变书籍剩余数量
				((*reader).bBookList[j]).bBookId = 0;//改变用户借书情况
				exam = true;
				cout << "还书成功" << endl;
				system("pause");
			}
		}
		if (exam == false)
		{
			cout << "该用户并未借阅此书籍" << endl;
			system("pause");
		}
	}
}

bool CApp::AddBookInfo()
{
	system("cls");
	cout << "***************************************添加书目*******************************************" << endl;
	char name[50], kind[50], author[20];
	cout << "请输入要添加的书名、作者" << endl;
	cin >> name;
	cin >> author;
	auto i = Search_BookPos_WithAB(name, author);

	
	if(i==bookList.end()||bookList.size()==0)//如果没有该书
	{
		CBook newbook;
		int sum;
		int id;
		cout << "请输入图书检索号：" << endl;
		while (1)
		{
			cin >> id;
			if (id > 0 && FindBook(id) == bookList.end())
			{
				newbook.book_id = id;
				break;
			}
			else
				cout << "不能输入已存在的检索号!重新输入：" << endl;
		}
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
			system("pause");
	}
	return true;
}

bool CApp::RevertByAdmin()
{
	cout << "请输入修改的图书检索号" << endl;
	int a;
	cin >> a;
	auto i = FindBook(a);
	if (i == bookList.end())
	{
		cout << "未找到该图书" << endl;
		system("pause");
	}
	else
	{
		cout << "当前总库存：" << (*i).sum;
		cout << "当前借出量" << (*i).sum - (*i).now_sum << endl;
		cout << "输入新的库存量:";
		int nSum;
		while (1)
		{
			cin >> nSum;
			if (nSum < (*i).sum - (*i).now_sum)
			{
				cout << "总库存不能小于借出量！重新输入：";
			}
			else
			{
				cout << "修改库存成功！现在库存为:" << nSum << endl;
				(*i).now_sum = nSum - ((*i).sum - (*i).now_sum);
				(*i).sum = nSum;
				system("pause");
				return true;
			}
		}
	}
	return false;
}

bool CApp::DisplayUser_bBook()
{
	char toSrchName[20];
	int cnt = 0;
	cout << "请输入要查询的用户名" << endl;
	cin >> toSrchName;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if (strcmp((*usrlst).GetName(), toSrchName) == 0) {
			cout << setw(12) << left << "检索号";
			cout << setw(12) << left << "种类";
			cout << setw(30) << left << "书名";
			cout << setw(12) << left << "作者";
			cout << setw(12) << left << "定价";
			cout << "借阅时间" << endl;
			for (int i = 0; i < 10; i++) {
				if ((*usrlst).bBookList[i].bBookId != 0) {
					cnt++;
					cout << setw(12) << left << (*usrlst).bBookList[i].bBookId;
					for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
						if ((*blst).book_id == (*usrlst).bBookList[i].bBookId) {
							cout << setw(12) << left << (*blst).kind;
							cout << setw(30) << left << (*blst).name;
							cout << setw(12) << left << (*blst).author;
							cout << setw(12) << left << (*blst).price;
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

bool CApp::DisplayUser_bBook(const char * toSrchName)
{
	int cnt = 0;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if (strcmp((*usrlst).GetName(), toSrchName) == 0) {
			cout << setw(12) << left << "检索号";
			cout << setw(12) << left << "种类";
			cout << setw(30) << left << "书名";
			cout << setw(12) << left << "作者";
			cout << setw(12) << left << "定价";
			cout << "借阅时间" << endl;
			for (int i = 0; i < 10; i++) {
				if ((*usrlst).bBookList[i].bBookId != 0) {
					cnt++;
					cout << setw(12) << left << (*usrlst).bBookList[i].bBookId;
					for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
						if ((*blst).book_id == (*usrlst).bBookList[i].bBookId) {
							cout << setw(12) << left << (*blst).kind;
							cout << setw(30) << left << (*blst).name;
							cout << setw(12) << left << (*blst).author;
							cout << setw(12) << left << (*blst).price;
							break;
						}
					}
					cout << (*usrlst).bBookList[i].bTime.tm_year+1900 << "-" << (*usrlst).bBookList[i].bTime.tm_mon+1 << "-" << (*usrlst).bBookList[i].bTime.tm_mday << "\t" << endl;;
				}
			}
			cout << "借阅总数：" << cnt << " 本" << endl;
			break;
		}
	}
	system("pause");
	return false;
}

bool CApp::DisplayAllBooks()
{
	system("cls");
	cout << "***************************************图书清单*******************************************" << endl;
	cout << setw(12) << left << "检索号";
	cout << setw(12) << left << "种类";
	cout << setw(30) << left << "书名";
	cout << setw(12) << left << "作者";
	cout << setw(12) << left << "定价";
	cout << setw(12) << left << "预约量";
	cout << setw(12) << left << "现库存量";
	cout << "总库存量" << endl;
	for (list<CBook>::iterator blst = bookList.begin(); blst != bookList.end(); ++blst) {
		cout << setw(12) << left << (*blst).book_id;
		cout << setw(12) << left << (*blst).kind;
		cout << setw(30) << left << (*blst).name;
		cout << setw(12) << left << (*blst).author;
		cout << setw(12) << left << (*blst).price;
		cout << setw(12) << left << (*blst).appointment;
		cout << setw(12) << left << (*blst).now_sum;
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
	return bookList.end();
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
	system("cls");
	cout << "***************************************删除书目*******************************************" << endl;
	char bookname[15];
	char author[15];
	cout << "请输入书名与作者！" << endl;
	cin >> bookname >> author;
	auto i = Search_BookPos_WithAB(bookname, author);
	if (i != bookList.end())
	{
		bookList.erase(i);
		cout << "删除此书成功！" << endl;
		system("pause");
	}
	else
	{
		cout << "不存在该书，无法删除。" << endl;
		system("pause");
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
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		fp.write((char*) & (*i), sizeof(b));
	}
	fp.close();
	return true;
}


void CApp::printfbook(std::list<CBook>::iterator blst)
{
	cout << setw(12) << left << "检索号";
	cout << setw(12) << left << "种类";
	cout << setw(30) << left << "书名";
	cout << setw(12) << left << "作者";
	cout << setw(12) << left << "定价";
	cout << setw(12) << left << "预约量";
	cout << setw(12) << left << "现库存量";
	cout << "总库存量" << endl;
	cout << setw(12) << left << (*blst).book_id;
	cout << setw(12) << left << (*blst).kind;
	cout << setw(30) << left << (*blst).name;
	cout << setw(12) << left << (*blst).author;
	cout << setw(12) << left << (*blst).price;
	cout << setw(12) << left << (*blst).appointment;
	cout << setw(12) << left << (*blst).now_sum;
	cout << (*blst).sum << endl;
}


