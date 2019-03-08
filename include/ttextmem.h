#ifndef __TEXTMEM_H__
#define __TEXTMEM_H__

#include "defines.h"

// memory control system
struct TTextMem
{
private:
  PTTextLink pFirst;
  PTTextLink pLast;
  PTTextLink pFree;

  friend class TTextLink;
};

#endif

