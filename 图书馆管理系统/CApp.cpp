#include "CApp.h"
#define QUIT -1
#define NEXT 1
#define STAY 0
#define LOGOUT 2
#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
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
void CApp::DisplayOverDueBook(CReader& a)
{
	int x = a.HasPenalty();
	if (x != 1)
	{
		cout << "�������鼮��" << endl;
		system("pause");
	}
	else
	{
		time_t now_time = time(NULL);//��ȡϵͳʱ��
		tm* t_tm = localtime(&now_time);
		int num = 0;
		PrintTitle();
		for (int i = 0; i < 10; i++)
		{
			if (a.bBookList[i].bBookId != 0)
			{
				if (t_tm->tm_year > a.bBookList[i].bTime.tm_year)//�Ƿ�������δ��
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
					if (t_tm->tm_yday - a.bBookList[i].bTime.tm_yday > 30)//�Ƿ�������δ��
					{
						list<CBook>::iterator it = FindBook(a.bBookList[i].bBookId);
						printfbook(it);
					}
				}
			}
		}
		system("pause");
	}

}
void CApp::ReviseReader()
{

	char rname[15];
	int cho = 0;
	cout << "�������û�����" << endl;
	cin >> rname;
	auto i = FindUser(rname);
	if (i != userList.end())
	{
		do
		{
			system("cls");
			cout << "***************************************�û���Ϣ�޸�*******************************************" << endl;
			cout << "\t\t\t1.�û�����" << endl;
			cout << "\t\t\t2.�û���ϵ��ʽ" << endl;
			cout << "\t\t\t3.�û����ɽ���" << endl;
			cout << "\t\t\t4.�˳�" << endl;
			cout << "��Ҫ�޸ĵ������ǣ�" << endl;
			cin >> cho;
			switch (cho)
			{
			case 1:
			{
				char pwd1[15];
				while (1)
				{
					cout << "�����������룺" << endl;
					inputPassword(pwd1);
					if (isPwdRight(pwd1) == false)
					{
						system("pause");
						continue;
					}
					cout << "ȷ�����룺";
					char pwd2[20] = { 0 };
					inputPassword(pwd2);
					if (strcmp(pwd1, pwd2) == 0)
					{
						(*i).SetPasswd(pwd2);
						cout << "���������óɹ���" << endl;
						break;
					}
					else
					{
						cout << "������������벻һ��!" << endl;
						system("pause");
						continue;
					}
				}
				break;
			}
			case 2:
			{
				char phone[15];
				cout << "����������ϵ��ʽ:" << endl;
				cin >> phone;
				(*i).SetPhone(phone);
				cout << "����ϵ��ʽ���óɹ���" << endl;
				system("pause");
				break;
			}
			case 3://���ɽ�����
			{
				(*i).Plenalty = 0;
				cout << "���Ľ��ɽ������㣬���´μ�ʱ����ร�" << endl;
				system("pause");
				break;
			}
			default:
				break;
			}
		} while (cho >= 1 && cho <= 3);
	}
	else
	{
		cout << "�û��������ڣ����������롣" << endl;
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
	cout << "                               1.��¼" << endl;
	cout << "                               2.ע��" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "�������ѡ���ܣ�";
}

void CApp::ReturnBook(CReader& a)
{
	cout << "������黹�������" << endl;
	int id_num;
	cin >> id_num;
	bool exam = false;
	for (int i = 0; i < 10; i++)
	{
		if (a.bBookList[i].bBookId == id_num)
		{
			exam = true;
			a.CalPenalty(id_num);
			a.bBookList[i].bBookId = 0;
			auto book = FindBook(id_num);
			(*book).now_sum++;//�ı��鼮ʣ������
			cout << "���ѳɹ��黹��" << (*FindBook(id_num)).name << "��" << endl;
			system("pause");
			break;
		}
	}
	if (exam == false)
	{
		cout << "����δ���Ĵ��鼮" << endl;
		system("pause");
	}

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
			cout << "���û����ѱ�ע�ᣡ�Ƿ�ʹ�������û���ע�᣿y/n" << endl;
			char k;
			cin >> k;
			if (k == 'y')
				continue;
			else if (k == 'n')
				return false;
			else
			{
				cout << "������y��n,�������������ҳ" << endl;
				system("pause");
				return false;
			}
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
			cout << "����Ա " << admin.GetName() << " ��¼�ɹ�" << endl;
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
	if (len < 6)
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

bool CApp::DisplayAllOverDueUser()
{
	cout << "*****************************************************************************************************" << endl;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if ((*usrlst).HasPenalty() == 1) {

			cout << "�û���" << (*usrlst).GetName() << endl;
			cout << "�����鵥��" << endl;
			cout << "\t" << setw(12) << left << "������";
			cout << setw(12) << left << "����";
			cout << setw(30) << left << "����";
			cout << setw(12) << left << "����";
			cout << setw(12) << left << "����";
			cout << "����ʱ��" << endl;
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
		cout << "��������ȷ��ָ��" << endl;
		system("pause");
		return STAY;
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

void CApp::BorrowBook(CReader& a)
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
		cout << "�������ɽ�δ���ɣ�����ɺ��ٽ��顣" << endl;
		system("pause");
	}
	else
	{
		if (x >= 10)
		{
			cout << "��ͬʱ���ֻ��ͬʱ��10���飡" << endl;
			system("pause");
		}
		else
		{
			cout << "����������鼮�ļ����ţ�";
			int id_num;
			cin >> id_num;
			auto i = bookList.begin();
			i = FindBook(id_num);//���������
			if (i == bookList.end())
			{
				cout << "������ļ���������" << endl;
				system("pause");
			}
			else
			{
				if ((*i).now_sum == 0)
				{
					cout << "������ȫ����裡" << endl;
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
						cout << "���ѽ��ĸ��飬�����ظ�����" << endl;
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
									time_t now_time = time(NULL);//��ȡϵͳʱ��
									tm* t_tm = localtime(&now_time);
									a.bBookList[x].bTime = *t_tm;
									break;
								}
							}
						}
						(*i).now_sum--;
						cout << "���ѳɹ����� ��" << (*i).name << "�� !" << endl;
						system("pause");
					}
				}
			}
		}
	}

}

void CApp::RevertByAdmin(CReader a)
{
	int id_num;
	int x = 0;
	char bookname[15], author[15];
	cout << "������������";
	cin >> bookname;
	cout << "���������ߣ�";
	cin >> author;
	list<CBook>::iterator i = Search_BookPos_WithAB(bookname, author);//������������
	id_num = (*i).book_id;
	for (int d = 0; d < 10; d++)
	{
		if (a.bBookList[d].bBookId == id_num)
		{
			a.bBookList[d].bBookId = 0;//����
			a.CalPenalty(id_num); //�������ɽ�
			(*i).sum--;
			if ((*i).sum == 0)//������ݲ�Ϊ0����ɾ������
			{
				bookList.erase(i);
			}
			x++;
			cout << "�黹�ɹ���" << endl;
			system("pause");
		}
	}
	if (x == 0)
	{
		cout << "���û�δ���Ĺ����飡������������š�" << endl;
		system("pause");
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
	cout << "                               6.��ʧ�鼮�ֶ��黹" << endl;
	cout << "                               7.�޸��û���Ϣ" << endl;
	cout << "                               8.�˳���¼" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "�������ѡ���ܣ�";
	char key;
	char name[50];
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
		ChangeBookInfo();
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
		cout << "�������û���:" << endl;
		cin >> name;
		if (FindUser(name) == userList.end())
			cout << "δ�ҵ����û���" << endl;
		else
			RevertByAdmin(*FindUser(name));
		return STAY;
		break;
	case '7':
		ReviseReader();
		return STAY;
		break;
	case'8':
		
		return LOGOUT;
	case '0':
		return QUIT;
	default:
		cout << "��������ȷ��ָ��" << endl;
		system("pause");
		return STAY;
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
	cout << "                               2.��ѯ�ѽ����鼮" << endl;
	cout << "                               3.���ɽ��ѯ" << endl;
	cout << "                               4.�鼮��ѯ" << endl;
	cout << "                               5.�����鼮��ѯ" << endl;
	cout << "                               6.�黹�鼮" << endl;
	cout << "                               7.�˳���¼" << endl;
	cout << "                               0.�˳�" << endl;
	cout << "�������ѡ���ܣ�";
	char key, key1, input[50],input2[50];
	int r;
	cin >> key;
	switch (key)
	{
	case '1':
	{
		BorrowBook(*FindUser(currentUserName));
		return STAY;
		break;
	}
	case '2':
		DisplayUser_bBook(currentUserName);
		return STAY;
		break;
	case '3':
		r = (*FindUser(currentUserName)).HasPenalty();
		if (r == 2)
		{
			cout << "���轻���ɽ�" << (*FindUser(currentUserName)).RPlenalty() << "Ԫ" << endl;
			system("pause");
		}
		else if (r == 1)
		{
			cout << "����������δ���鼮,��黹���ѯ��" << endl;
			system("pause");
		}
		else if (r == 0)
		{
			cout << "��û�����ɽ������" << endl;
			system("pause");
		}
		break;
	case '4':
		system("cls");
		cout << "                               1.��ʾȫ���鼮" << endl;
		cout << "                               2.�������ѯ�鼮" << endl;
		cout << "                               3.�����������߲�ѯ�鼮" << endl;
		cout << "                               4.�������Ų�ѯ�鼮" << endl;
		cout << "�������ѡ����:";
		cin >> key1;
		switch (key1)
		{
		case '1':
			DisplayAllBooks();
			break;
		case'2':
			cout << "����������" << endl;
			cin >> input;
			PrintTitle();
			Search_BookPos_WithKind(input);
			system("pause");
			break;
		case'3':
			cout << "�������������ߣ�";
			cin >> input >> input2;
			PrintTitle();
			printfbook(Search_BookPos_WithAB(input, input2));
			system("pause");
			break;
		case'4':
			cout << "���������:";
			cin >> r;
			PrintTitle();
			printfbook(FindBook(r));
			system("pause");
			break;
		default:
			cout << "��������ȷ�����" << endl;
			system("pause");
			break;
		}
		return STAY;
		break;
	case '5':
		DisplayOverDueBook(*FindUser(currentUserName));
		return STAY;
		break;
	case '6':
		ReturnBook(*FindUser(currentUserName));
		return STAY;
	case '7':
		return LOGOUT;
	case '0':
		return QUIT;
		break;
	default:
		cout << "��������ȷ��ָ��" << endl;
		system("pause");
		return STAY;
		break;
	}
	return STAY;
}

void CApp::Search_BookPos_WithKind(char Kind[15])
{
	cout << "ͼ�����Ҫ�����й��ƣ���ƣ�ҽѧ��ũѧ�����������ġ�" << endl;
	int num = 0;
	for (auto i = bookList.begin(); i != bookList.end(); i++)
	{
		//cout << "������\t����\t����\t\t����\t����\tԤԼ��\t�ֿ����\t�ܿ����" << endl;
		if ((strcmp(Kind, (*i).kind)) == 0)
		{
			num++;
			printfbook(i);
		}
	}
	if (num == 0)
	{
		cout << "��Ǹ��ͼ���δ�ҵ������͵��鼮��" << endl;
	}
	else
	{
		cout << "��Ϊ��������" << num << "���������鼮" << endl;
	}

}

void CApp::AdminReturnBook()
{
	bool exam = false;
	cout << "�������û����͹黹�������" << endl;
	char userid[50];
	int bookid;
	cin >> userid >> bookid;
	auto reader = FindUser(userid);
	if (reader == userList.end())
	{
		cout << "δ�ҵ����û���" << endl;
		system("pause");
	}
	else
	{
		for (int j = 0; j < 10; j++)
		{
			if (((*reader).bBookList[j]).bBookId == bookid)//������������
			{
				auto book = FindBook(bookid);
				(*book).now_sum++;//�ı��鼮ʣ������
				((*reader).bBookList[j]).bBookId = 0;//�ı��û��������
				exam = true;
				cout << "����ɹ�" << endl;
				system("pause");
			}
		}
		if (exam == false)
		{
			cout << "���û���δ���Ĵ��鼮" << endl;
			system("pause");
		}
	}
}

bool CApp::AddBookInfo()
{
	system("cls");
	cout << "***************************************�����Ŀ*******************************************" << endl;
	char name[50], kind[50], author[20];
	cout << "������Ҫ��ӵ�����������" << endl;
	cin >> name;
	cin >> author;
	auto i = Search_BookPos_WithAB(name, author);
	if (i == bookList.end() || bookList.size() == 0)//���û�и���
	{
		CBook newbook;
		int sum;
		int id;
		cout << "������ͼ������ţ�" << endl;
		while (1)
		{
			cin >> id;
			if (id <= 0)
			{
				cout << "������ֻ��Ϊ������" << endl;
				continue;
			}
			if (FindBook(id) == bookList.end())
			{
				newbook.book_id = id;
				break;
			}
			else
				cout << "���������Ѵ��ڵļ�����!�������룺" << endl;
		}
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
		system("pause");
	}
	return true;
}

bool CApp::ChangeBookInfo()
{
	cout << "�������޸ĵ�ͼ�������" << endl;
	int a;
	cin >> a;
	auto i = FindBook(a);
	if (i == bookList.end())
	{
		cout << "δ�ҵ���ͼ��" << endl;
		system("pause");
	}
	else
	{
		cout << "��" << (*i).name << "��" << endl;
		cout << "��ǰ�ܿ�棺" << (*i).sum;
		cout << "��ǰ�����" << (*i).sum - (*i).now_sum << endl;
		cout << "�����µĿ����:";
		int nSum;
		while (1)
		{
			cin >> nSum;
			if (nSum < (*i).sum - (*i).now_sum)
			{
				cout << "�ܿ�治��С�ڽ�������������룺";
				continue;
			}
			else
			{
				cout << "�޸Ŀ��ɹ������ڿ��Ϊ:" << nSum << endl;
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
	cout << "������Ҫ��ѯ���û���" << endl;
	cin >> toSrchName;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if (strcmp((*usrlst).GetName(), toSrchName) == 0) {
			cout << setw(12) << left << "������";
			cout << setw(12) << left << "����";
			cout << setw(30) << left << "����";
			cout << setw(12) << left << "����";
			cout << setw(12) << left << "����";
			cout << "����ʱ��" << endl;
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
			cout << "����������" << cnt << " ��" << endl;
			break;
		}
	}
	return true;
}

bool CApp::DisplayUser_bBook(const char* toSrchName)
{
	int cnt = 0;
	for (list<CReader>::iterator usrlst = userList.begin(); usrlst != userList.end(); ++usrlst) {
		if (strcmp((*usrlst).GetName(), toSrchName) == 0) {
			cout << setw(12) << left << "������";
			cout << setw(12) << left << "����";
			cout << setw(30) << left << "����";
			cout << setw(12) << left << "����";
			cout << setw(12) << left << "����";
			cout << "����ʱ��" << endl;
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
					cout << (*usrlst).bBookList[i].bTime.tm_year + 1900 << "-" << (*usrlst).bBookList[i].bTime.tm_mon + 1 << "-" << (*usrlst).bBookList[i].bTime.tm_mday << "\t" << endl;;
				}
			}
			cout << "����������" << cnt << " ��" << endl;
			break;
		}
	}
	system("pause");
	return false;
}

bool CApp::DisplayAllBooks()
{
	system("cls");
	cout << "***************************************ͼ���嵥*******************************************" << endl;
	cout << setw(12) << left << "������";
	cout << setw(12) << left << "����";
	cout << setw(30) << left << "����";
	cout << setw(12) << left << "����";
	cout << setw(12) << left << "����";
	cout << setw(12) << left << "ԤԼ��";
	cout << setw(12) << left << "�ֿ����";
	cout << "�ܿ����" << endl;
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
	system("cls");
	cout << "***************************************ɾ����Ŀ*******************************************" << endl;
	char bookname[15];
	char author[15];
	cout << "���������������ߣ�" << endl;
	cin >> bookname >> author;
	auto i = Search_BookPos_WithAB(bookname, author);
	if (i != bookList.end())
	{
		bookList.erase(i);
		cout << "ɾ������ɹ���" << endl;
		system("pause");
	}
	else
	{
		cout << "�����ڸ��飬�޷�ɾ����" << endl;
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
	cout << setw(12) << left << (*blst).book_id;
	cout << setw(12) << left << (*blst).kind;
	cout << setw(30) << left << (*blst).name;
	cout << setw(12) << left << (*blst).author;
	cout << setw(12) << left << (*blst).price;
	cout << setw(12) << left << (*blst).appointment;
	cout << setw(12) << left << (*blst).now_sum;
	cout << (*blst).sum << endl;
}




void CApp::PrintTitle()
{
	cout << setw(12) << left << "������";
	cout << setw(12) << left << "����";
	cout << setw(30) << left << "����";
	cout << setw(12) << left << "����";
	cout << setw(12) << left << "����";
	cout << setw(12) << left << "ԤԼ��";
	cout << setw(12) << left << "�ֿ����";
	cout << "�ܿ����" << endl;
}
