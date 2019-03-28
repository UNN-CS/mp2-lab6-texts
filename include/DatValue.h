#pragma once
#include <iostream>
using namespace std;

class TDatValue;
typedef TDatValue * PTDatValue;

class TDatValue {  //модуль, объ€вл€ющий абстрактный класс объектов-значений списка
  public:
    virtual TDatValue * GetCopy() =0; // создание копии
   ~TDatValue() {}
};

