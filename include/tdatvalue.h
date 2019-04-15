#pragma once

class TDatValue
{
public:
  virtual TDatValue * GetCopy() = 0; // создание копии

  ~TDatValue() {}
};
typedef TDatValue *PTDatValue;