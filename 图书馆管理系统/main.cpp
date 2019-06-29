#pragma once
#include"CBook.h"
#include"CUser.h"
#include"CApp.h"
#include<iostream>
using namespace std;
CApp theApp;
int main()
{
	CApp theApp;
	while (theApp.DisplayFirstPage() == true);
	if (theApp.GetCurUserName() == "Admin");
	return 0;
}