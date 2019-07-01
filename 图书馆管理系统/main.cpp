#pragma once
#include"CBook.h"
#include"CUser.h"
#include"CApp.h"
#include<iostream>
using namespace std;
constexpr auto QUIT = -1;
constexpr auto NEXT = 1;
constexpr auto STAY = 0;
constexpr auto LOGOUT = 2;
int main()
{
	CApp theApp;//Ӧ�ó�����
mainmeun:
	while (1)
	{
		auto a = theApp.DisplayFirstPage();//��¼��ע��ҳ��
		if (a == QUIT)
			return 0;
		else if (a == NEXT)
			break;
		else if (a == STAY)
			continue;
	}
	if (strcmp(theApp.GetCurUserName(), theApp.GetAdminName()) == 0)//�ж��Ƿ�Ϊ����Ա
		while (1)
		{
			auto a = theApp.DisplayAdminMenu();//����Աҳ��
			if (a == QUIT)
				return 0;
			else if (a == NEXT)
				break;
			else if (a == STAY)
				continue;
			else if (a == LOGOUT)
				goto mainmeun;
		}
	else
		while (1)
		{
			auto a = theApp.DisplayReaderMenu();//����ҳ��
			if (a == QUIT)
				return 0;
			else if (a == NEXT)
				break;
			else if (a == STAY)
				continue;
			else if (a == LOGOUT)
				goto mainmeun;
		}

	return 0;
}