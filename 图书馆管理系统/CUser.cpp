#include "CUser.h"
#include<iostream>
#include<cstring>
#include"CBook.h"
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

CReader::CReader()
{
	
}

void CReader::CalPenalty(int id)
{
	for (int i = 0; i < 10; i++)
	{
		if (bBookList[i].bBookId == id)
		{
			time_t now_time = time(NULL);//��ȡϵͳʱ��
			tm* t_tm = localtime(&now_time);
			if (t_tm->tm_year > bBookList[i].bTime.tm_year)//�Ƿ�������δ��
			{
				int daynum = t_tm->tm_yday + (365*(t_tm->tm_year- bBookList[i].bTime.tm_year) - bBookList[i].bTime.tm_yday);
				if (daynum - 30 > 0)
				{
					Plenalty = 0.1 * daynum + Plenalty;
				}
			}
			else
			{
				if (t_tm->tm_yday - bBookList[i].bTime.tm_yday - 30 > 0)//�Ƿ�������δ��
				{
					Plenalty = Plenalty + ((t_tm->tm_yday) - bBookList[i].bTime.tm_yday - 30) * 0.1;
				}
			}
		}
	}
}

bool CReader::SetPhone(const char* ph)
{
	strcpy(phone, ph);
	return false;
}

int CReader::HasPenalty()
{
	time_t now_time = time(NULL);//��ȡϵͳʱ��
	tm* t_tm = localtime(&now_time);
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		if (bBookList[i].bBookId != 0)
		{
			if (t_tm->tm_year > bBookList[i].bTime.tm_year)//�Ƿ�������δ��
			{
				int daynum = t_tm->tm_yday + (365 - bBookList[i].bTime.tm_yday);
				if (daynum > 30)
				{
					num++;
				}
			}
			else
			{
				if (t_tm->tm_yday - bBookList[i].bTime.tm_yday > 30)//�Ƿ�������δ��
				{
					num++;
				}
			}
		}
	}
	if (num > 0)
	{
		return 1;
	}
	if (num == 0 && Plenalty != 0)
	{
		return 2;
	}
	if (num == 0 && Plenalty == 0)
	{
		return 0;
	}

}

double CReader::RPlenalty()
{
	return Plenalty;
}
