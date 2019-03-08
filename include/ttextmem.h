#ifndef __TEXTMEM_H__
#define __TEXTMEM_H__

#include "defines.h"

// memory control system
class TTextMem
{
private:
  PTTextLink pFirst;
  PTTextLink pLast;
  PTTextLink pFree;
  PTTextLink pGarbage;

  bool memCreated;

  void CreateMem(std::size_t size=MemSize);

  void GarbageCollect();

  void ReturnMem();

  TTextMem();

  ~TTextMem();

  friend class TTextLink;
  friend class TText;
};

#endif

