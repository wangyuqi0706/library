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

bool CAdmin::AddBookInfo()
{
	return false;
}
