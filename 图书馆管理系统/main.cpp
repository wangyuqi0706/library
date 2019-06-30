#pragma once
#include"CBook.h"
#include"CUser.h"
#include"CApp.h"
#include<iostream>
using namespace std;
int main()
{
	CApp theApp;
	while (theApp.DisplayFirstPage() == true);
	if (strcmp(theApp.GetCurUserName(), "Admin") == 0)
		while (theApp.DisplayAdminMenu() == true);
	else
		while (theApp.DisplayReaderMenu() == true);

	return 0;
}