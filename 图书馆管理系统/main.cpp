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
	CApp theApp;//应用程序类
mainmeun:
	while (1)
	{
		auto a = theApp.DisplayFirstPage();//登录、注册页面
		if (a == QUIT)
			return 0;
		else if (a == NEXT)
			break;
		else if (a == STAY)
			continue;
	}
	if (strcmp(theApp.GetCurUserName(), theApp.GetAdminName()) == 0)//判断是否为管理员
		while (1)
		{
			auto a = theApp.DisplayAdminMenu();//管理员页面
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
			auto a = theApp.DisplayReaderMenu();//读者页面
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