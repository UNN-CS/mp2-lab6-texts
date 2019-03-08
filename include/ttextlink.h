#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__

#include <cstring>
#include <iostream>
#include "defines.h"


class TTextLink
{
private:
  int refCount;
  static PTTextMem pCurrMemControl;

public:
  TStr Str;
  PTTextLink pNext, pDown;
  PTTextMem pMemControl;

  TTextLink(const TStr s=NULL, PTTextLink pn=NULL, PTTextLink pd=NULL);
  virtual ~TTextLink();

  static void *operator new(std::size_t);
  static void operator delete(void *pM) noexcept(false);
  static void SetMemControl(PTTextMem mc);

  bool IsAtom() const;
  PTTextLink GetNext() const;
  PTTextLink GetDown() const;
  PTTextLink GetCopy(PTTextMem mc=NULL) const;

  virtual void Print(std::ostream &os) const;

  friend class TTextMem;
};

#endif

