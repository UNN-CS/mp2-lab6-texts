#include "../include/ttext.h"
#include "../include/ttextlink.h"

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
  PTTextLink pLink = pl;
  std::stack<PTTextLink> tstack;

  while(!pLink->IsAtom())
  {
    tstack.push(pLink);
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

    if(pLink->GetDown() != NULL)
    {
      tstack.push(pLink);
      pLink = pLink->GetDown();
      ++lvl;
    }
    else if(pLink->GetNext() != NULL)
    {
      tstack.push(pLink);
      pLink = pLink->GetNext();
    }
    else
    {
      while(!tstack.empty() && (tstack.top()->GetNext() == pLink
          || tstack.top()->GetNext() == NULL))
      {
        pLink = tstack.top();
        tstack.pop();
      }
      if(tstack.empty())
        pLink = NULL;
      else
        pLink = tstack.top()->GetNext();
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
  if(pCurrent == pFirst)
    return false;

  Path.push(pCurrent);
  pCurrent = pFirst;
  return true;
}

bool TText::GoDownLink()
{
  if(pCurrent == NULL)
    return false;

  if(pCurrent->GetDown() == NULL)
    return false;

  Path.push(pCurrent);
  pCurrent = pCurrent->GetDown();
  return true;
}

bool TText::GoNextLink()
{
  if(pCurrent == NULL)
    return false;

  if(pCurrent->GetNext() == NULL)
    return false;

  Path.push(pCurrent);
  pCurrent = pCurrent->GetNext();
  return true;
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
{
  if(pCurrent == NULL)
    throw TextError;

  return std::string(pCurrent->Str);
}

void TText::SetLine(std::string s)
{
  if(pCurrent == NULL)
    throw TextError;

  strncpy(pCurrent->Str, s.c_str(), TextLineLength);
}

void TText::InsDownLine(std::string s)
{
  if(pCurrent == NULL)
    throw TextError;

  PTTextLink pLink = CreateLink(s.c_str(), pCurrent->GetDown(), NULL);
  pCurrent->SetDown(pLink);
}

void TText::InsDownSection(std::string s)
{
  if(pCurrent == NULL)
    throw TextError;

  PTTextLink pLink = CreateLink(s.c_str(), NULL, pCurrent->GetDown());
  pCurrent->SetDown(pLink);
}

void TText::InsNextLine(std::string s)
{
  if(pCurrent == NULL)
    throw TextError;

  PTTextLink pLink = CreateLink(s.c_str(), pCurrent->GetNext(), NULL);
  pCurrent->SetNext(pLink);
}

void TText::InsNextSection(std::string s)
{
  if(pCurrent == NULL)
    throw TextError;

  PTTextLink pLink = CreateLink(s.c_str(), NULL, pCurrent->GetNext());
  pCurrent->SetNext(pLink);
}

void TText::DelDownLine()
{
  if(pCurrent == NULL)
    throw TextError;
  if(pCurrent->GetDown() == NULL)
    throw TextError;
  if(pCurrent->GetDown()->GetDown() != NULL)
    throw TextError;

  PTTextLink pLink = pCurrent->GetDown();
  pCurrent->SetDown(pLink->GetNext());

  pLink->SetDown(NULL);
  pLink->SetNext(NULL);
}

void TText::DelDownSection()
{
  if(pCurrent == NULL)
    throw TextError;
  if(pCurrent->GetDown() == NULL)
    throw TextError;

  std::stack<PTTextLink> tstack, del;
  // link which will remove
  PTTextLink pDel = pCurrent->GetDown(),
      pLink;

  // pDown now on pDown->pNext
  pCurrent->SetDown(pDel->GetNext());
  pDel->SetNext(NULL);


  tstack.push(pDel);
  if(pDel->GetDown() != NULL)
    tstack.push(pDel->GetDown());
  pLink = pDel;

  while(tstack.size() > 0)
  {
    del.push(pLink);

    pLink = tstack.top();
    tstack.pop();
    if(pLink != pCurrent->GetDown())
    {
      if(pLink->GetNext() != NULL)
        tstack.push(pLink->GetNext());
      if(pLink->GetDown() != NULL)
        tstack.push(pLink->GetDown());
    }
  }

  while(del.size() > 0)
  {
    del.top()->SetDown(NULL);
    del.top()->SetNext(NULL);
  }
}

void TText::DelNextLine()
{
  if(pCurrent == NULL)
    throw TextError;
  if(pCurrent->GetNext() == NULL)
    throw TextError;
  if(pCurrent->GetNext()->GetDown() != NULL)
    throw TextError;

  PTTextLink pLink = pCurrent->GetNext();
  pCurrent->SetNext(pLink->GetNext());

  pLink->SetNext(NULL);
  pLink->SetDown(NULL);
}

void TText::DelNextSection()
{

}

/*void TText::DelNextSection()
{
  if(pCurrent == NULL)
    throw TextError;

  PTTextLink pDel = pCurrent->GetNext();

  if(pDel == NULL)
    throw TextError;

  std::stack<PTTextLink> tstack, del;
  PTTextLink pLink = pDel;

  while(pLink != NULL)
  {
    del.push(pLink);

    if(pLink->GetDown() != NULL)

  }

}*/

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

