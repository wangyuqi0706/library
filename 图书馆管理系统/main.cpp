#pragma once
#include"CBook.h"
#include"CUser.h"
#include"CApp.h"
#include<iostream>
using namespace std;
#define QUIT -1
#define NEXT 1
#define STAY 0
#define LOGOUT 2
int main()
{
	CApp theApp;
mainmeun:
	while (1)
	{
		auto a = theApp.DisplayFirstPage();
		if (a == QUIT)
			return 0;
		else if (a == NEXT)
			break;
		else if (a == STAY)
			continue;
	}
	if (strcmp(theApp.GetCurUserName(), theApp.GetAdminName()) == 0)
		while (1)
		{
			auto a = theApp.DisplayAdminMenu();
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
			auto a = theApp.DisplayReaderMenu();
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