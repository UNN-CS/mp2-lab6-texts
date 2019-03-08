#include "../include/ttext.h"
#include "../include/ttextlink.h"

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
  PTTextLink pLink = pl;
  while(!pLink->IsAtom())
  {
    St.push(pLink);
    pLink = pLink->GetDown();
  }

  return pLink;
}

void TText::PrintText(PTTextLink ptl)
{
  int lvl = 0;
  const char *indent = "  ";
  std::stack<PTTextLink> tstack;
  PTTextLink pLink = ptl;

  while(pLink != NULL)
  {
    for(int i = 0; i < lvl; ++i)
      std::cout << indent;
    std::cout << ptl->Str << std::endl;

    if(pLink->pDown != NULL)
    {
      tstack.push(pLink);
      pLink = pLink->pDown;
      ++lvl;
    }
    else if(pLink->pNext != NULL)
    {
      tstack.push(pLink);
      pLink = pLink->pNext;
    }
    else
    {
      while(tstack.top()->pNext == pLink)
      {
        pLink = tstack.top();
        tstack.pop();
      }
      pLink = tstack.top()->pNext;
      --lvl;
    }
  }
}

/*
 * Using recursion
void TText::PrintText(PTTextLink ptl, textLevel=0)
{
  const char *indent = "  ";
  if(ptl != NULL)
  {
    for(int i = 0; i < textLevel; ++i)
      std::cout << indent;
    std::cout << ptl->Str << std::endl;
    PrintText(ptl->pDown, textLevel + 1);
    PrintText(ptl->pNext, textLevel);
  }
}
*/

PTTextLink TText::ReadText(std::ifstream &TxtFile)
{
}

PTTextLink TText::CreateLink(const TStr s, PTTextLink pn, PTTextLink pd)
{
  if(!MemControl.IsMemCreated())
    MemControl.CreateMem();

  TTextLink::SetMemControl(&MemControl);
  PTTextLink pLink = new TTextLink(s, pn, pd);

  return pLink;
}

TText::TText(PTTextLink pl)
{
  if(pl == NULL)
  {
    pl = CreateLink();
  }

  pFirst = pl;
  pFirst->refCount += 1;
}

TText::~TText(){}

PTText TText::GetCopy()
{
}

int TText::GoFirstLink()
{
}

int TText::GoDownLink()
{
}

int TText::GoNextLink()
{
}

int TText::GoPrevLink()
{
}

std::string TText::GetLine()
{
}

void TText::SetLine(std::string s)
{
}

void TText::InsDownLine(std::string s)
{
}

void TText::InsDownSection(std::string s)
{
}

void TText::InsNextLine(std::string s)
{
}

void TText::InsNextSection(std::string s)
{
}

void TText::DelDownLine()
{
}

void TText::DelDownSection()
{
}

void TText::DelNextLine()
{
}

void TText::DelNextSection()
{
}

int TText::Reset()
{
}

bool TText::IsTextEnded() const
{
}

int TText::GoNext()
{
}

void TText::Read(const char *pFileName)
{
}

void TText::Write(const char *pFileName)
{
}

void TText::Print()
{
}

