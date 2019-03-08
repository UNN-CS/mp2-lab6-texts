#include "../include/ttext.h"
#include "../include/ttextlink.h"

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
}

void TText::PrintText(PTTextLink ptl)
{
}

PTTextLink TText::ReadText(std::ifstream &TxtFile)
{
}

PTTextLink TText::CreateLink(const TStr s, PTTextLink pn, PTTextLink pd)
{
  if(!MemControl.memCreated)
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

