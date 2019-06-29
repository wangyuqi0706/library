#pragma once
#include<ctime>
#include<vector>
#include<string>
class CBook
{
public:
	int book_id;//图书检索号
	int sum;//图书总库存存量
	int now_sum;//图书现库存量
	char kind[20];//种类
	int appointment = 0;//图书预约量,初始化为0
	char name[50];//书名
	char author[50];//作者
	double price;//书籍定价
	void PrintInfo();
	CBook(int b_id,const char* n,const char* aut,int sum,double p);

};

