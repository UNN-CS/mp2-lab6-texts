#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__

#include <cstring>
#include <iostream>
#include "defines.h"
#include "tdatvalue.h"
#include "ttextmem.h"


class TTextLink: public TDatValue
{
protected:
  TStr Str;
  PTTextLink pNext, pDown;
  static TTextMem MemHeader;

public:
  static void InitMemSystem(int size=MemSize);
  static void PrintFreeLink();
  static void MemCleaner(const TText &txt);

  TTextLink(const TStr s=NULL, PTTextLink pn=NULL, PTTextLink pd=NULL)
    : pNext(pn), pDown(pd)
  {
    if(s != NULL)
      strcpy(Str, s);
    else
      Str[0]='\0';
  }
  virtual ~TTextLink(){}

  void *operator new(std::size_t);
  void operator delete(void *pM);

  int IsAtom()
  { return pDown == NULL; }
  PTTextLink GetNext()
  { return pNext; }
  PTTextLink GetDown()
  { return pDown; }
  virtual TDatValue* GetCopy() const override
  { return new TTextLink(Str, pNext, pDown); }

protected:
  virtual void Print(std::ostream &os)
  { os << Str; }

  friend class TText;
};

#endif

