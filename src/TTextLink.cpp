#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size)
{
	PTTextLink t = new TTextLink[size];
	MemHeader.pFree = MemHeader.pFirst = t;
	MemHeader.pLast = &t[size-1];
	for (int i = 0; i < size-1; i++)	
		t[i].pNext = &t[i + 1];
	MemHeader.pLast->pNext = NULL;
}

void TTextLink::PrintFreeLink()
{
	PTTextLink t = MemHeader.pFree;
	while (t != NULL)
	{
		std::cout << t->Str << std::endl;
		t = t->GetNext();
	}
}

void* TTextLink::operator new(size_t size)
{
	PTTextLink t = MemHeader.pFree;
	if (t != NULL)
		MemHeader.pFree = t->GetNext();
	else
		throw -1;
	return t;
}

void TTextLink::operator delete(void* pM)
{
	PTTextLink t = (PTTextLink)pM;
	t->pNext = MemHeader.pFree;
	MemHeader.pFree = t;
}

void TTextLink::MemCleaner(TText &txt)
{
	txt.Reset();
	while (!(txt.IsTextEnded()))
	{
		txt.SetLine("&&&" + txt.GetLine());
		txt.GoNext();
	}

	PTTextLink t = MemHeader.pFree;
	for(;t != NULL;t = t->pNext)
		strcpy(t->Str, "&&&");

	t = MemHeader.pFirst;
	for (;t <= MemHeader.pLast;t++)
	{
		if (strstr(t->Str, "&&&") != NULL)
			strcpy(t->Str, t->Str + 3);
		else
			delete t;
	}
}

TTextLink::TTextLink(TStr s, PTTextLink pn, PTTextLink pd) : pNext(pn), pDown(pd)
{
	if (s != NULL)
		strcpy_s(Str, TextLineLength, s);
	else
		Str[0] = '\0';
}

TTextLink::~TTextLink() {}

bool TTextLink::IsAtom()
{
	return pDown == NULL;
}

PTTextLink TTextLink::GetNext()
{
	return pNext;
}

PTTextLink TTextLink::GetDown()
{
	return pDown;
}

PTDatValue TTextLink::GetCopy()
{
	return new TTextLink(Str, pNext, pDown);
}

void TTextLink::Print(std::ostream &os)
{
	os << Str;
}