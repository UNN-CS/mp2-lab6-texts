#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__

#include <cstring>
#include <iostream>
#include "defines.h"


class TTextLink
{
private:
  static PTTextMem pCurrMemControl;
  int refCount;
  PTTextLink pNext, pDown;
  PTTextMem pMemControl;

public:
  TStr Str;

  TTextLink(const TStr s, PTTextLink pn=NULL, PTTextLink pd=NULL);
  TTextLink();
  virtual ~TTextLink();

  static void *operator new(std::size_t);
  static void operator delete(void *pM);
  static void SetMemControl(PTTextMem mc);

  bool IsAtom() const;
  PTTextLink GetCopy(PTTextMem mc=NULL) const;
  void SetNext(PTTextLink pn);
  void SetDown(PTTextLink pd);
  PTTextLink GetNext() const;
  PTTextLink GetDown() const;

  virtual void Print(std::ostream &os) const;

  friend class TTextMem;
};

#endif

