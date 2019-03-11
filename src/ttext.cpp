#include "../include/ttext.h"
#include <queue>
#include "../include/ttextlink.h"

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
  if(pl == NULL)
    throw TextError;

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
  if(ptl == NULL)
    throw TextError;

  //int lvl = 0;
  //const char *indent = "  ";
  std::stack<PTTextLink> tstack;
  PTTextLink pLink;

  // reset
  if(ptl->GetNext() != NULL)
    tstack.push(ptl->GetNext());
  if(ptl->GetDown() != NULL)
    tstack.push(ptl->GetDown());

  os << ptl->Str << std::endl;

  while(!tstack.empty())
  {
    pLink = tstack.top();
    tstack.pop();

    if(pLink->GetNext() != NULL)
      tstack.push(pLink->GetNext());
    if(pLink->GetDown() != NULL)
      tstack.push(pLink->GetDown());

    os << pLink << std::endl;
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
  std::stack<PTTextLink> tstack;
  std::string line;
  PTTextLink pLink;

  std::getline(TxtFile, line);
  pLink = pFirst = CreateLink(line.c_str());

  pRoot->SetNext(pFirst);

  while(std::getline(TxtFile, line))
  {
    if(line == "}")
    {
      pLink = tstack.top();
      tstack.pop();
    }
    else if(line == "{")
    {
      tstack.push(pLink);
      std::getline(TxtFile, line);
      pLink = CreateLink(line.c_str());
      tstack.top()->SetDown(pLink);
    }
    else
    {
      pLink->SetNext(CreateLink(line.c_str()));
      pLink = pLink->GetNext();
    }
  }

  return pFirst;
}

PTTextLink TText::CreateLink(const TStr s, PTTextLink pn, PTTextLink pd)
{
  TTextLink::SetMemControl(&MemControl);
  PTTextLink pLink = new TTextLink(s, pn, pd); //TODO: fix segfault

  return pLink;
}

TText::TText(PTTextLink pl)
{
  pRoot = ::new TTextLink;
  if(pl == NULL)
    pl = CreateLink("", NULL, NULL); //TODO: fix segfault
  pRoot->SetNext(pl);

  pFirst = pl;
  Reset();
}

TText::~TText()
{
  ::delete pRoot;
}

PTText TText::GetCopy()
{
  PTText pText = new TText;
  PTTextLink pStart, pLink;
  std::stack<PTTextLink> tstack;

  Reset();
  pLink = pStart = pText->CreateLink(pCurrent->Str);
  pText->pRoot->SetNext(pStart);

  while(!IsTextEnded())
  {
    if(!tstack.empty()
        && pCurrent->GetDown() == NULL && pCurrent->GetNext() == NULL)
    {
      pLink->SetNext(pText->CreateLink(pCurrent->Str));
      pLink = tstack.top();
      tstack.pop();
    }
    else if(pCurrent->GetDown() != NULL)
    {
      pLink->SetNext(pText->CreateLink(pCurrent->Str));
      tstack.push(pLink->GetNext());
      GoNext();
      pLink = pText->CreateLink(pCurrent->Str);
      tstack.top()->SetDown(pLink);
    }
    else
    {

    }
  }
  return NULL;
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

  //pLink->SetDown(NULL);
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
  PTTextLink pDel = pCurrent->GetDown();
  PTTextLink pLink = pDel;

  // pDown now on pDown->pNext
  pCurrent->SetDown(pDel->GetNext());
  pDel->SetNext(NULL);


  tstack.push(pDel);
  if(pDel->GetDown() != NULL)
    tstack.push(pDel->GetDown());

  while(tstack.size() > 0)
  {
    del.push(pLink);

    pLink = tstack.top();
    tstack.pop();
    if(pLink != pDel)
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
  //pLink->SetDown(NULL);
}

void TText::DelNextSection()
{
  if(pCurrent == NULL)
    throw TextError;
  if(pCurrent->GetNext() != NULL)
    throw TextError;

  std::stack<PTTextLink> tstack, del;
  PTTextLink pDel = pCurrent->GetNext();
  PTTextLink pLink = pDel;

  pCurrent->SetNext(pDel->GetNext());
  pDel->SetNext(NULL);

  tstack.push(pDel);
  if(pDel->GetDown() != NULL)
    tstack.push(pDel->GetDown());

  while(tstack.size() > 0)
  {
    del.push(pLink);

    pLink = tstack.top();
    tstack.pop();
    if(pLink != pDel)
    {
      if(pLink->GetNext() != NULL)
        tstack.push(pLink->GetNext());
      if(pLink->GetDown() != NULL)
        tstack.push(pLink->GetDown());
    }
  }
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
  if(pFirst == NULL)
    throw TextError;

  while(!St.empty())
    St.pop();

  pCurrent = pFirst;

  if(pCurrent->GetNext() != NULL)
    St.push(pCurrent->GetNext());
  if(pCurrent->GetDown() != NULL)
    St.push(pCurrent->GetDown());
}

bool TText::IsTextEnded() const
{ return St.empty(); }

bool TText::GoNext()
{
  if(!IsTextEnded())
  {
    pCurrent = St.top();
    St.pop();

    if(pCurrent->GetNext() != NULL)
      St.push(pCurrent->GetNext());
    if(pCurrent->GetDown() != NULL)
      St.push(pCurrent->GetDown());
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
  PrintText(pFirst, fout);
}

void TText::Print()
{ PrintText(pFirst, std::cout); }

