#include "CUser.h"
#include<iostream>
#include<cstring>
using namespace std;

void CUser::SetName(const char* n)
{
	strcpy(name, n);
}


char* CUser::GetName()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return name;
}


void CUser::SetPasswd(const char* tpwd)
{
	strcpy(pwd, tpwd);
	// TODO: �ڴ˴����ʵ�ִ���.
}




char* CUser::GetPasswd()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return pwd;
}

void CAdmin::ReviseBook(char name[15], char author[15])
{
}

CReader::CReader()
{
	bBookList.resize(10);
	bBookList.max_size();
}
