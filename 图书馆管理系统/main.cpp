#pragma once
#include"CBook.h"
#include"CUser.h"
#include"CApp.h"
#include<iostream>
using namespace std;
int main()
{
	CApp theApp;
	while (1)
	{
		auto a = theApp.DisplayFirstPage();
		if (a < 0)
			return 0;
		else if (a == 0)
			break;
		else
			continue;
	}
	if (strcmp(theApp.GetCurUserName(), theApp.GetAdminName()) == 0)
		while (1)
		{
			auto a = theApp.DisplayAdminMenu();
			if (a < 0) return 0;
			else if (a == 0) break;
			else continue;
		}
	else
		while (theApp.DisplayReaderMenu() == true);

	return 0;
}