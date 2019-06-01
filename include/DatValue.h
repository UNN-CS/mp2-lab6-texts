//базовый класс объектов-значений
#ifndef __DATVALUE_H__
#define __DATVALUE_H__

#include <iostream>

class TDatValue {
  public:
    virtual TDatValue* GetCopy() = 0; // создание копии
   ~TDatValue() {}
};

typedef TDatValue* PTDatValue;
#endif // __DATVALUE_H__
