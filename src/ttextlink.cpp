#include "../include/ttextlink.h"
#include "../include/ttextmem.h"
#include "../include/ttext.h"

PTTextMem TTextLink::pCurrMemControl = NULL;

void TTextLink::SetMemControl(PTTextMem mc)
{ pCurrMemControl = mc; }

TTextLink::TTextLink(const TStr s, PTTextLink pn, PTTextLink pd)
    : refCount(0), pNext(pn), pDown(pd), pMemControl(pCurrMemControl)
{ strcpy(Str, s); }

TTextLink::~TTextLink(){}


void *TTextLink::operator new(std::size_t)
{
  PTTextLink pLink = NULL;
  if(pCurrMemControl == NULL)
  {
    throw TextNoMem;
  }
  else
  {
    pLink = pCurrMemControl->pFree;
    if(pLink == NULL)
      throw TextNoMem;
    else
      pCurrMemControl->pFree = pLink->pNext;
  }

  pCurrMemControl = NULL;

  return pLink;
}

void TTextLink::operator delete(void *pM) noexcept(false)
{
  PTTextLink pLink = static_cast<PTTextLink>(pM);

  if(pLink == NULL)
  {
    throw TextError;
  }
  else
  {
    pLink->pNext = pLink->pMemControl->pFree;
    pLink->pMemControl->pFree = pLink;
  }
}

bool TTextLink::IsAtom() const
{ return pDown == NULL; }

PTTextLink TTextLink::GetNext() const
{ return pNext; }

PTTextLink TTextLink::GetDown() const
{ return pDown; }

PTTextLink TTextLink::GetCopy(PTTextMem mc) const
{
  if(mc == NULL)
    mc = pMemControl;

  pCurrMemControl = mc;
  return new TTextLink(Str, pNext, pDown);
}

void TTextLink::Print(std::ostream &os) const
{ os << Str << std::endl; }

