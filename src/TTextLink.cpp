#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

TTextLink::TTextLink(TStr s, PTTextLink pn, PTTextLink pd)
{
	pNext = pn;
	pDown = pd;
	if (s != nullptr)
		strcpy(Str, s);
	else
		Str[0] = '\0';

}
void TTextLink::InitMemSystem(int size)
{
	if (size<1)
		MemHeader.pFirst = MemHeader.pFree = MemHeader.pLast = nullptr;
	else
	{
		MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) *size];
		MemHeader.pFree = MemHeader.pFirst;
		MemHeader.pLast = MemHeader.pFirst + (size - 1);
		PTTextLink pLink = MemHeader.pFirst;
		for (int i = 0; i<size - 1; i++, pLink++)
			pLink->pNext = pLink + 1;
		pLink->pNext = nullptr;
	}
}
void TTextLink::PrintFreeLink(void)
{
	PTTextLink pLink = MemHeader.pFree;
	cout << "List of free links" << endl;
	for (; pLink != nullptr; pLink = pLink->pNext)
		cout << pLink->Str << endl;
}
void* TTextLink::operator new (size_t size)
{
	PTTextLink pLink = MemHeader.pFree;
	if (MemHeader.pFree != nullptr)
		MemHeader.pFree = pLink->pNext;
	return pLink;
}
void TTextLink::operator delete(void* pM)
{
	PTTextLink pLink = (PTTextLink)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}
void TTextLink::MemCleaner(TText txt)
{
	//string st;	
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
		if (txt.GetLine().find("&&&") != 0)
			txt.SetLine("&&&" + txt.GetLine());
	PTTextLink pLink = MemHeader.pFirst;
	for (; pLink <= MemHeader.pLast; pLink++)
	{
		if (strstr(pLink->Str, "&&&") != nullptr)
			strcpy(pLink->Str, pLink->Str + 3);
		else
			delete pLink;
	}
}