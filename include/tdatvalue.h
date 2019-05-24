#pragma once
#include <iostream>

class TDatValue;
typedef TDatValue *PTDatValue;
class TDatValue
{
  public:
    virtual TDatValue *GetCopy() = 0; //create copy
    ~TDatValue() {}
};