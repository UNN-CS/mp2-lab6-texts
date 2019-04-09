#pragma once

#include <iostream>

class TDatValue
{
public:
  virtual TDatValue *GetCopy() = 0;
  ~TDatValue() {}
};
typedef TDatValue *PTDatValue;