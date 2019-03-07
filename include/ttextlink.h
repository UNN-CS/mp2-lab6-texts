#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__
#include <cstddef>
#include <cstring>
#include <iostream>
#include "tdatvalue.h"

#define TextLineLength 80

class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem
{
  PTTextLink pFirst;
  PTTextLink pLast;
  PTTextLink pFree;

  friend class TTextLink;
};

class TTextLink: public TDatValue
{
protected:
  TStr Str;
  PTTextLink pNext, pDown;
  static TTextMem MemHeader;    //memory control system

public:
  static void InitMemSystem(int size=MemSize);
  static void PrintFreeLink();
  static void MemCleaner(const TText &txt);

  TTextLink(TStr s=NULL, PTTextLink pn=NULL, PTTextLink pd=NULL)
  {
    pNext = pn;
    pDown = pd;
    if(s != NULL)
      strcpy(Str, s);
    else
      Str[0]='\0';
  }
  TTextLink(int i);
  virtual ~TTextLink(){}

  void *operator new(std::size_t size);
  void operator delete(void *pM);

  int IsAtom()
  { return pDown == NULL; }
  PTTextLink GetNext()
  { return pNext; }
  PTTextLink GetDown()
  { return pDown; }
  TDatValue* GetCopy() const
  { return new TTextLink(Str, pNext, pDown); }

protected:
  virtual void Print(std::ostream &os)
  { os << Str; }

  friend class TText;
};

#endif

