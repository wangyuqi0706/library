#pragma once
#include<ctime>
class CBook
{
public:
	int book_id=0;//ͼ�������
	int sum=0;//ͼ���ܿ�����
	int now_sum=0;//ͼ���ֿ����
	char kind[20]="";//����
	int appointment = 0;//ͼ��ԤԼ��,��ʼ��Ϊ0
	char name[50]="";//����
	char author[50]="";//����
	double price=0;//�鼮����
	void PrintInfo();
	CBook(int b_id,const char* n,const char* aut,int sum,double p);
	CBook() {}
};

