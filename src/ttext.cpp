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

void TText::PrintText(PTTextLink ptl, std::ostream &os)
{
  int lvl = 0;
  const char *indent = "  ";
  std::stack<PTTextLink> tstack;
  PTTextLink pLink = ptl;

  while(pLink != NULL)
  {
    for(int i = 0; i < lvl; ++i)
      os << indent;
    os << ptl->Str << std::endl;

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
      while(!tstack.empty()
          && (tstack.top()->pNext == pLink || tstack.top()->pNext == NULL))
      {
        pLink = tstack.top();
        tstack.pop();
      }
      if(tstack.empty())
        pLink = NULL;
      else
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
    pl = CreateLink();

  pFirst = pl;
}

TText::~TText(){}

PTText TText::GetCopy()
{
}

bool TText::GoFirstLink()
{
  if(pFirst == NULL)
  {
    return false;
  }
  else
  {
    Path.push(pCurrent);
    pCurrent = pFirst;
    return true;
  }
}

bool TText::GoDownLink()
{
  if(pCurrent == NULL)
    return false;
  if(pCurrent->pDown != NULL)
  {
    Path.push(pCurrent);
    pCurrent = pCurrent->pDown;
    return true;
  }
  else
  {
    return false;
  }
}

bool TText::GoNextLink()
{
  if(pCurrent == NULL)
    return false;
  if(pCurrent->pNext != NULL)
  {
    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
    return true;
  }
  else
  {
    return false;
  }
}

bool TText::GoPrevLink()
{
  if(Path.empty())
    return false;
  pCurrent = Path.top();
  Path.pop();
  return true;
}

std::string TText::GetLine()
{ return std::string(pCurrent->Str); }

void TText::SetLine(std::string s)
{ strncpy(pCurrent->Str, s.c_str(), TextLineLength); }

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

void TText::Reset()
{
  pCurrent = pFirst;
  while(!St.empty())
    St.pop();
}

bool TText::IsTextEnded() const
{ return pCurrent == NULL; }

bool TText::GoNext()
{
  if(!IsTextEnded())
  {
    if(pCurrent->pDown != NULL)
    {
      St.push(pCurrent);
      pCurrent = pCurrent->pDown;
    }
    else if(pCurrent->pNext != NULL)
    {
      St.push(pCurrent);
      pCurrent = pCurrent->pNext;
    }
    else
    {
      while(!St.empty()
          && (St.top()->pNext == pCurrent || St.top()->pNext == NULL))
      {
        pCurrent = St.top();
        St.pop();
      }
      if(St.empty())
        pCurrent = NULL;
      else
        pCurrent = St.top()->pNext;
    }
  }

  return IsTextEnded();
}

void TText::Read(const char *pFileName)
{
  std::ifstream fin(pFileName);
  ReadText(fin);
}

void TText::Write(const char *pFileName)
{
  std::ofstream fout(pFileName);
  Print(fout);
}

void TText::Print(std::ostream &os)
{ PrintText(pFirst, os); }

