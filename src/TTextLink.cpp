#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

TTextLink::TTextLink(TStr s, PTTextLink pn, PTTextLink pd) : pNext(pn), pDown(pd)
{
    if (s)
    {
        if (strlen(s) > TextLineLength)
            throw std::out_of_range("String is too long");
        strcpy_s(Str, s);
    }
    else
        Str[0] = '\0';
}

void TTextLink::InitMemSystem(int size)
{
    if (size <= 0)
        throw std::invalid_argument("In \"InitMemSystem\" size <= 0");
    if (MemHeader.pFirst)
        DelMemSystem();
    MemHeader.pFirst = MemHeader.pFree = (PTTextLink) new char[size * sizeof(TTextLink)];
    MemHeader.pLast = MemHeader.pFirst + size - 1;
    while (MemHeader.pFree != MemHeader.pLast)
    {
        MemHeader.pFree->pNext = MemHeader.pFree + 1;
        MemHeader.pFree = MemHeader.pFree->pNext;
    }
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast->pNext = nullptr;
    MemHeader.freeCount = size;
}

void TTextLink::PrintFreeLink(void)
{
    PTTextLink tmp = MemHeader.pFree;
    std::cout << "List of free links:\n";
    if (!tmp)
        std::cout << "List is empty.\n";
    else
        while (tmp)
        {
            std::cout << tmp->Str << std::endl;
            tmp = tmp->pNext;
        }
    std::cout << "Count of free links = " << MemHeader.freeCount << std::endl;
}

void* TTextLink::operator new (size_t size)
{
    if (!MemHeader.pFree)
        throw std::runtime_error("Memory system if full or not initialized!");
    PTTextLink tmp = MemHeader.pFree;
    MemHeader.freeCount--;
    if (MemHeader.pFree)
        MemHeader.pFree = tmp->pNext;
    return tmp;
}

void TTextLink::operator delete(void* pM)
{
    if (pM)
    {
        PTTextLink tmp = (PTTextLink)pM;
        tmp->pNext = MemHeader.pFree;
        MemHeader.pFree = tmp;
        MemHeader.freeCount++;
    }
}

void TTextLink::MemCleaner(TText txt)
{
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
        if (txt.GetLine().find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    PTTextLink tmp = MemHeader.pFirst;
    for (; tmp <= MemHeader.pLast; tmp++)
        if (strstr(tmp->Str, "&&&") != nullptr)
            strcpy_s(tmp->Str, tmp->Str + 3);
        else
            delete tmp;
}

void TTextLink::DelMemSystem()
{
    if (MemHeader.pFirst != nullptr)
    {
        delete[](char *)MemHeader.pFirst;
        MemHeader.pFirst = MemHeader.pFree = MemHeader.pLast = nullptr;
        MemHeader.freeCount = 0;
    }
}