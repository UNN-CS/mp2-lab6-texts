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

public:
  bool IsMemCreated() const;
  void CreateMem(std::size_t size=MemSize);
  void GarbageCollect();
  void ReturnMem();
  bool IsThereFreeMem() const;
  //int FreeMem() const;

  TTextMem();
  TTextMem(std::size_t size);
  ~TTextMem();

  friend class TTextLink;
};

#endif

