#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size)
{
	char *tmp = new char[sizeof(TTextLink)*size];
	MemHeader.pFirst = (PTTextLink)tmp;
	MemHeader.pFree = (PTTextLink)tmp;
	MemHeader.pLast = (PTTextLink)tmp + size - 1;
	PTTextLink pLink = MemHeader.pFirst;

	for (int i = 0; i < size - 1; i++, pLink++)
		pLink->pNext = pLink + 1;
	pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink(void)
{
	PTTextLink pLink = MemHeader.pFree;
	while (pLink != NULL)
	{
		cout << pLink->Str << endl;
		pLink = pLink->pNext;
	}
}

void * TTextLink::operator new(size_t size)
{
	PTTextLink pLink = MemHeader.pFree;
	if (MemHeader.pFree != NULL)  MemHeader.pFree = pLink->pNext;
	return pLink;
}

void TTextLink::operator delete(void * pM)
{
	PTTextLink pLink = (PTTextLink)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

void TTextLink::MemCleaner(TText & txt)
{
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
		txt.SetLine("&&&" + txt.GetLine());

	PTTextLink pLink = MemHeader.pFree;
	for (; pLink != nullptr; pLink = pLink->pNext)
		strcpy_s(pLink->Str, "&&&");

	for (pLink = MemHeader.pFirst; pLink <= MemHeader.pLast; pLink++)
		if (strstr(pLink->Str, "&&&") != NULL)
			strcpy_s(pLink->Str, pLink->Str + 3);
		else
			delete pLink;
}