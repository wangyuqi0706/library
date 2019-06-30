#include "CBook.h"

void CBook::PrintInfo()
{

}

CBook::CBook(int b_id, const char* n, const char* aut, int su, double p, const char* k)
{
	book_id = b_id;
	strcpy(name, n);
	strcpy(author,aut);
	sum = su;
	price = p;
	strcpy(kind,k);
}


