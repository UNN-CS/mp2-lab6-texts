#include "../include/ttextmem.h"
#include "../include/ttextlink.h"
#include "../include/ttext.h"

void TTextMem::CreateMem(std::size_t size)
{
  PTTextLink pLink = pFirst = pFree = ::new TTextLink[size];
  pLast = pFirst + size - 1;

  for(std::size_t i = 0; i < size - 1; ++i, ++pLink)
    pLink->pNext = pLink + 1;

  pLink->pNext = NULL;

  memCreated = true;
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
  memCreated = false;
}

TTextMem::TTextMem():
    pFirst(NULL),
    pLast(NULL),
    pFree(NULL),
    pGarbage(NULL),
    memCreated(false)
{}

TTextMem::~TTextMem()
{ ReturnMem(); }

