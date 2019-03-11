#include "include/ttextlink.h"
#include "include/ttextmem.h"
#include "include/ttext.h"

PTTextMem TTextLink::pCurrMemControl = NULL;

void TTextLink::SetMemControl(PTTextMem mc)
{ pCurrMemControl = mc; }

TTextLink::TTextLink(const TStr s, PTTextLink pn, PTTextLink pd)
    : refCount(0), pNext(pn), pDown(pd), pMemControl(pCurrMemControl)
{
  strcpy(Str, s);

  if(pd != NULL)
    pd->refCount += 1;

  if(pn != NULL)
    pn->refCount += 1;
}

TTextLink::TTextLink(){}

TTextLink::~TTextLink(){}


void *TTextLink::operator new(std::size_t)
{
  PTTextLink pLink = NULL;

  if(pCurrMemControl == NULL)
  {
    return ::new TTextLink;
  }
  else
  {
    if(!pCurrMemControl->IsMemCreated())
      pCurrMemControl->CreateMem(); // works

    pLink = pCurrMemControl->pFree;
    pCurrMemControl->pFree = pCurrMemControl->pFree->pNext;
  }

  pCurrMemControl = NULL;

  return (void*)pLink;
}

void TTextLink::operator delete(void *pM)
{
  PTTextLink pLink = static_cast<PTTextLink>(pM);

  if(pLink != NULL)
  {
    if(pLink->pMemControl != NULL)
    {
      pLink->pNext = pLink->pMemControl->pFree;
      pLink->pDown = NULL;
      pLink->pMemControl->pFree = pLink;
    }
    else
    {
      ::delete pLink;
    }
  }
}

bool TTextLink::IsAtom() const
{ return pDown == NULL; }

PTTextLink TTextLink::GetCopy(PTTextMem mc) const
{
  if(mc == NULL)
    mc = pMemControl;

  pCurrMemControl = mc;
  return new TTextLink(Str, pNext, pDown);
}

void TTextLink::SetNext(PTTextLink pn)
{
  if(pNext != NULL)
    pNext->refCount -= 1;

  pNext = pn;

  if(pn != NULL)
    pn->refCount += 1;
}

void TTextLink::SetDown(PTTextLink pd)
{
  if(pDown != NULL)
    pDown->refCount -= 1;

  pDown = pd;

  if(pd != NULL)
    pd->refCount += 1;
}

PTTextLink TTextLink::GetNext() const
{ return pNext; }

PTTextLink TTextLink::GetDown() const
{ return pDown; }

void TTextLink::Print(std::ostream &os) const
{ os << Str << std::endl; }

