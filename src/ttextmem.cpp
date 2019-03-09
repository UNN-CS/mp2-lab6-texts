#include "../include/ttextmem.h"
#include "../include/ttextlink.h"

bool TTextMem::IsMemCreated()
{ return pFirst != NULL; }

void TTextMem::CreateMem(std::size_t size)
{
  PTTextLink pLink = pFirst = pFree = ::new TTextLink[size];
  pLast = pFirst + size - 1;

  for(std::size_t i = 0; i < size - 1; ++i, ++pLink)
    pLink->pNext = pLink + 1;

  pLink->pNext = NULL;
}

void TTextMem::GarbageCollect()
{
  PTTextLink pLink;

  for(pLink = pFirst; pLink != NULL; ++pLink)
    if(pLink->refCount == 0)
      delete pLink;
}

void TTextMem::ReturnMem()
{
  ::delete[] pFirst;
  pFree = pFirst = pLast = NULL;
}

TTextMem::TTextMem():
    pFirst(NULL),
    pLast(NULL),
    pFree(NULL)
{}

TTextMem::~TTextMem()
{ ReturnMem(); }

