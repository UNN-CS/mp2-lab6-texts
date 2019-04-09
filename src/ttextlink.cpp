#include <ttextlink.hpp>
#include <ttext.hpp>

#include <conio.h>

TTextLink::TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL)
{
    pNext = pn;
    pDown = pd;

    if (s != NULL)
        strcpy(Str, s);
    else
        Str[0] = '\0';
}

void TTextLink::InitMemSystem(int size)
{
    char Line[100];

    MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size - 1);

    PTTextLink pLink = MemHeader.pFirst;

    for (int i = 0; i < size - 1; i++, pLink++)
    {
        pLink->pNext = pLink + 1;
    }

    pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink(void)
{
    PTTextLink pLink = MemHeader.pFree;

    std::cout << "Free links list: " << std::endl;
    for (; pLink != NULL; pLink = pLink->pNext)
        std::cout << pLink->Str << std::endl;
}

void *TTextLink::operator new(size_t size)
{
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != NULL)
        MemHeader.pFree = pLink->pNext;

    return pLink;
}

void TTextLink::operator delete(void *pM)
{
    PTTextLink pLink = (PTTextLink)pM;

    pLink->pNext = MemHeader.pFree;
    MemHeader.pFree = pLink;
}

void TTextLink::MemCleaner(const TText &txt)
{
}
