#include "../include/ttextlink.h"

void TTextLink::InitMemSystem(int size)
{
  PTTextLink pLink = MemHeader.pFree = MemHeader.pFirst
      = ::new TTextLink[size];
  MemHeader.pLast = MemHeader.pFirst + size - 1;

  for(int i = 0; i < size - 1; ++i, ++pLink)
    pLink->pNext = pLink + 1;

  pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink()
{
}

void TTextLink::MemCleaner(const TText &txt)
{
  
}

void *TTextLink::operator new(std::size_t)
{
  PTTextLink pLink = MemHeader.pFree;

  if(MemHeader.pFree)
    MemHeader.pFree = MemHeader.pFree->pNext;

  return pLink;
}

void TTextLink::operator delete(void *pM)
{
  PTTextLink pLink = static_cast<PTTextLink>(pM);

  pLink->pNext = MemHeader.pFree;
  MemHeader.pFree = pLink;
}


