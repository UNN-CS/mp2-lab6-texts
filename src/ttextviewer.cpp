#include "include/ttextviewer.h"
#include "include/ttext.h"

TTextViewer::TTextViewer(PTText pt)
    : pText(pt)
{
  if(pt == NULL)
    throw -1;
}

TTextViewer::~TTextViewer(){}

void TTextViewer::FPrint(int mode)
{
  switch(mode)
  {
  case FP_NUM:
    {
      fpnum_ostream fpos(1);
      pText->PrintText(pText->pFirst, fpos);
    }
    break;

  case FP_PTR:
    {
      PTTextLink pLink = pText->pCurrent;
      int pos = 1;
      pText->Reset();
      while(pText->pCurrent != pLink)
      {
        ++pos;
        pText->GoNext();
      }
      fpptr_ostream fpos(pos, 1);
      pText->PrintText(pText->pFirst, fpos);
    }
    break;

  case (FP_NUM | FP_PTR):
    {
      PTTextLink pLink = pText->pCurrent;
      int pos = 1;
      pText->Reset();
      while(pText->pCurrent != pLink)
      {
        ++pos;
        pText->GoNext();
      }
      fppn_ostream fpos(pos, 1);
      pText->PrintText(pText->pFirst, fpos);
    }
    break;

  case 0:
    pText->PrintText(pText->pFirst, std::cerr);
    break;

  default:
    throw -1;
    break;
  };
}

TTextViewer::fpnum_ostream& operator<<(TTextViewer::fpnum_ostream &os, const char *s)
{
      std::cout << os.counter << ": " << s;
      return os;
}

