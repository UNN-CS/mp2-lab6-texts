#include "include/ttextmem.h"
#include <stack>
#include "include/ttextlink.h"

bool TTextMem::IsMemCreated() const
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
    if(pLink->refCount == 0
        && (pLink->pDown != NULL || pLink->pNext != NULL))
    {
      std::stack<PTTextLink> tstack, dstack;
      PTTextLink t = pLink;

      // reset
      tstack.push(t);
      if(t->GetNext() != NULL)
        tstack.push(t->GetNext());
      if(t->GetDown() != NULL)
        tstack.push(t->GetDown());

      dstack.push(t);

      // gonext
      while(tstack.top() != pLink)
      {
        t = tstack.top();
        tstack.pop();
        if(t->GetNext() != NULL)
          tstack.push(t->GetNext());
        if(t->GetDown() != NULL)
          tstack.push(t->GetDown());

        dstack.push(t);
      }

      while(!dstack.empty())
      {
        dstack.top()->SetDown(NULL);
        dstack.top()->SetNext(NULL);
        dstack.pop();
      }
    }

  for(pLink = pFirst; pLink != NULL; ++pLink)
    if(pLink->refCount == 0)
      delete pLink;
}

void TTextMem::ReturnMem()
{
  ::delete[] pFirst;
  pFree = pFirst = pLast = NULL;
}

bool TTextMem::IsThereFreeMem() const
{ return pFirst != NULL; }

TTextMem::TTextMem():
    pFirst(NULL),
    pLast(NULL),
    pFree(NULL)
{}

TTextMem::TTextMem(std::size_t size)
{ CreateMem(size); }


TTextMem::~TTextMem()
{ ReturnMem(); }

