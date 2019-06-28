#pragma once
#include<ctime>
#include<vector>
typedef struct b
{
	tm bTime;
	//std::vector<char[20]> bUserList;
}Borrowed;
class CBook
{
	char name[20];
	char id[10];
	std::vector<Borrowed> bInfo;
};

