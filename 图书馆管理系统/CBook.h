#pragma once
#include<ctime>
#include<vector>
#include<string>
class CBook
{
public:
	int book_id;//ͼ�������
	int sum;//ͼ���ܿ�����
	int now_sum;//ͼ���ֿ����
	char kind[20];//����
	int appointment = 0;//ͼ��ԤԼ��,��ʼ��Ϊ0
	char name[50];//����
	char author[50];//����
	double price;//�鼮����
	void PrintInfo();
	CBook(int b_id,const char* n,const char* aut,int sum,double p);

};

