#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size)
{
    MemHeader.pFirst = (PTTextLink)new char[sizeof(TTextLink) * size];
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + size - 1;
    for (int i = 0; i < size - 1; ++i)
        MemHeader.pFirst[i].pNext = MemHeader.pFirst + i + 1;
    MemHeader.pFirst[size - 1].pNext = NULL;
}

void TTextLink::PrintFreeLink (void)
{
    for (PTTextLink p = MemHeader.pFree; p != NULL; p = p->pNext)
        std::cout << p->Str << '\n';
}

void* TTextLink::operator new(size_t size)
{
    PTTextLink p = MemHeader.pFree;
    if (MemHeader.pFree != NULL)
        MemHeader.pFree = MemHeader.pFree->pNext;
    return p;
}

void TTextLink::operator delete (void *pM)
{
    PTTextLink p = (PTTextLink)pM;
    p->pDown = NULL;
    p->pNext = MemHeader.pFree;
    MemHeader.pFree = p;
}

void TTextLink::MemCleaner (TText &txt)
{
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
        txt.SetLine("&&&" + txt.GetLine());
    for (PTTextLink p = MemHeader.pFree; p != NULL; p = p->pNext)
        strcpy(p->Str, "&&&");
    for (PTTextLink p = MemHeader.pFirst; p <= MemHeader.pLast; ++p)
        if (strstr(p->Str, "&&&") != NULL)
            strcpy(p->Str, p->Str + 3);
        else
            delete p;
}


