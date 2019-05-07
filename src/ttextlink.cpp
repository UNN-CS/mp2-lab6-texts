#include "ttextlink.h"
#include "ttext.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size)
{
	MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink)*size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);

	PTTextLink pLink = MemHeader.pFirst;
	for (int i = 0; i < (size - 1); ++i)
	{
		pLink->pNext = pLink + 1;
		++pLink;
	}
	pLink->pNext = nullptr;
}

void TTextLink::PrintFreeLink()
{
	PTTextLink pLink = MemHeader.pFree;

	if (pLink == nullptr) cout << "No free links" << endl;

	while (pLink != nullptr)
	{
		cout << pLink->Str << endl;
		pLink = pLink->pNext;
	}
}

void* TTextLink::operator new (size_t size)
{
	PTTextLink pLink = MemHeader.pFree;
	
	if (MemHeader.pFree != nullptr)
		MemHeader.pFree = MemHeader.pFree->pNext;

	return pLink;
}

void TTextLink::operator delete (void *pM)
{
	if (pM == nullptr) throw - 1;

	PTTextLink pLink = (PTTextLink)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

void TTextLink::MemCleaner(TText &txt)
{									   
	string st;

	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	{
		st = txt.GetLine();

		if (st.find("&&&") != 0)
			txt.SetLine("&&&" + txt.GetLine());
	}

	PTTextLink pLink = MemHeader.pFree;
	while (pLink != nullptr)
	{
		strcpy(pLink->Str, "&&&");
		pLink = pLink->pNext;
	}

	pLink = MemHeader.pFirst;
	while (pLink <= MemHeader.pLast)
	{
		if (strstr(pLink->Str, "&&&") != nullptr)
			strcpy(pLink->Str, pLink->Str + 3);
		else
			delete pLink;
	}
}

ostream& operator << (ostream& os, TTextLink tl)
{
    os << tl.Str;
    return os;
}


