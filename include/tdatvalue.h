#ifndef __DATVALUE_H__
#define __DATVALUE_H__

#include "defines.h"

class TDatValue
{
public:
  virtual PTDatValue GetCopy() const = 0;
  virtual ~TDatValue(){}
};

#endif

