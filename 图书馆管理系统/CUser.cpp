#include "CUser.h"
#include<iostream>
#include<cstring>
#include"CBook.h"
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

CReader::CReader()
{
	bBookList.resize(10);
}

bool CReader::SetPhone(const char* ph)
{
	strcpy(phone, ph);
	return false;
}