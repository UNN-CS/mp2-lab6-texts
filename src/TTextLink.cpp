 #include "TTextLink.h"
#include <iostream>
using namespace std;
PTTextMem TTextLink::MemHeader = new TTextMem();
void TTextLink::InitMemSystem(int size)
{
	MemHeader->pFirst = (PTTextLink) new char[sizeof(TTextLink)*size];
	MemHeader->pFree = MemHeader->pFirst;
	MemHeader->pLast = MemHeader->pFirst + (size - 1);
	PTTextLink pLink = MemHeader->pFirst;
	for (int i = 0; i < size - 1; ++i, pLink++)
	{
		   pLink->pNext = pLink + 1;
	}
	pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink()
{
	PTTextLink pLink = MemHeader->pFree;
	cout << "List of free links" << endl;
	for (; pLink != NULL; pLink = pLink->pNext)
	{
		cout << pLink->Str << endl;
	}
}

void* TTextLink::operator new (size_t size) //выделение звена
{
	PTTextLink pLink = MemHeader->pFree;
	if (MemHeader->pFree != NULL) MemHeader->pFree = pLink->pNext;
	return pLink;
}

void TTextLink::operator delete (void*pM) // освобождение звена
{
	PTTextLink pLink = MemHeader->pFree;
	MemHeader->pFree = (PTTextLink)pM;
	MemHeader->pFree->pNext = pLink;
}

void TTextLink::MemCleaner( TText&  txt)
{
	string st;
	//маркировка строк текста
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	{
		if (st.find("&&&") != 0) txt.SetLine("&&&" + txt.GetLine());
	}
	//маркировка списка свободных звеньев
	PTTextLink pLink = MemHeader->pFree;
	for (; pLink !=NULL; pLink=pLink->pNext)
	{
		strcpy(pLink->Str, "&&&");
	}
	//сборка мусора
	pLink = MemHeader->pFirst;
	for (; pLink <= MemHeader->pLast; pLink++)
	{
		if (strstr(pLink->Str, "&&&") != 0) // строка текста или свободное звено?
			strcpy(pLink->Str, pLink->Str + 3); // снятие маркировки
		else
			delete pLink; //неучтенное звено в список свободных 
	}
}