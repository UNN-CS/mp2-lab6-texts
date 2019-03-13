#include "include/ttextviewer.h"
#include "include/ttext.h"
#include "include/ttextlink.h"
#include <stack>

void TTextViewer::print_n(std::ostream &os)
{
  int counter = 1;
  int lvl = 0;
  std::stack<PTTextLink> tstack;
  PTTextLink pLink = pText->pFirst;

  tstack.push(pLink);
  if(pLink->GetNext() != NULL)
    tstack.push(pLink->GetNext());
  if(pLink->GetDown() != NULL)
    tstack.push(pLink->GetDown());

  os << counter << "\t: " << pLink->Str << std::endl;
  counter += 1;

  while(tstack.top() != pText->pFirst)
  {
    if(pLink->GetDown() != NULL)
      lvl += 1;
    else if(pLink->GetNext() == NULL)
      lvl -= 1;

    pLink = tstack.top();
    tstack.pop();
    if(pLink->GetNext() != NULL)
      tstack.push(pLink->GetNext());
    if(pLink->GetDown() != NULL)
      tstack.push(pLink->GetDown());

    os << counter << "\t: ";
    for(int i = 0; i < lvl; ++i)
      os << pText->indent;
    os << pLink->Str << std::endl;
    counter += 1;
  }
}

void TTextViewer::print_p(std::ostream &os)
{
  int lvl = 0;
  std::stack<PTTextLink> tstack;
  PTTextLink pLink = pText->pFirst;
  PTTextLink pCurr = pText->pCurrent;

  tstack.push(pLink);
  if(pLink->GetNext() != NULL)
    tstack.push(pLink->GetNext());
  if(pLink->GetDown() != NULL)
    tstack.push(pLink->GetDown());

  if(pCurr == pLink)
    os << "=> ";
  else
    os << "   ";
  os << pLink->Str << std::endl;

  while(tstack.top() != pText->pFirst)
  {
    if(pLink->GetDown() != NULL)
      lvl += 1;
    else if(pLink->GetNext() == NULL)
      lvl -= 1;

    pLink = tstack.top();
    tstack.pop();
    if(pLink->GetNext() != NULL)
      tstack.push(pLink->GetNext());
    if(pLink->GetDown() != NULL)
      tstack.push(pLink->GetDown());

    if(pCurr == pLink)
      os << "=> ";
    else
      os << "   ";
    for(int i = 0; i < lvl; ++i)
      os << pText->indent;
    os << pLink->Str << std::endl;
  }
}

void TTextViewer::print_pn(std::ostream &os)
{
  int counter = 1;
  int lvl = 0;
  std::stack<PTTextLink> tstack;
  PTTextLink pLink = pText->pFirst;
  PTTextLink pCurr = pText->pCurrent;

  tstack.push(pLink);
  if(pLink->GetNext() != NULL)
    tstack.push(pLink->GetNext());
  if(pLink->GetDown() != NULL)
    tstack.push(pLink->GetDown());

  if(pCurr == pLink)
    os << "=> ";
  else
    os << "   ";
  os << counter << "\t: ";
  os << pLink->Str << std::endl;

  while(tstack.top() != pText->pFirst)
  {
    if(pLink->GetDown() != NULL)
      lvl += 1;
    else if(pLink->GetNext() == NULL)
      lvl -= 1;

    pLink = tstack.top();
    tstack.pop();
    if(pLink->GetNext() != NULL)
      tstack.push(pLink->GetNext());
    if(pLink->GetDown() != NULL)
      tstack.push(pLink->GetDown());

    if(pCurr == pLink)
      os << "=> ";
    else
      os << "   ";
    os << counter << "\t: ";
    for(int i = 0; i < lvl; ++i)
      os << pText->indent;
    os << pLink->Str << std::endl;
    counter += 1;
  }
}

TTextViewer::TTextViewer(PTText pt)
    : pText(pt)
{
  if(pt == NULL)
    throw -1;
}

void TTextViewer::FPrint(int mode)
{
  switch(mode)
  {
  case FP_NUM:
    print_n(std::cout);
    break;
  case FP_PTR:
    print_p(std::cout);
    break;
  case (FP_NUM | FP_PTR):
    print_pn(std::cout);
    break;
  case 0:
    pText->Print();
    break;
  default:
    throw -1;
    break;
  };
}

