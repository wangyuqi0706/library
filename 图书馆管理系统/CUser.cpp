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
	// TODO: 在此处添加实现代码.
	return name;
}


void CUser::SetPasswd(const char* tpwd)
{
	strcpy(pwd, tpwd);
	// TODO: 在此处添加实现代码.
}




char* CUser::GetPasswd()
{
	// TODO: 在此处添加实现代码.
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