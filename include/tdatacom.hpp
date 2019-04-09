// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdatacom.h - Copyright (c) Гергель В.П. 30.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Обработка кодов завершения

#ifndef __DATACOM_H__
#define __DATACOM_H__

#define DATAOK 0
#define DATAERR -1

// TDataCom является общим базовым классом
class TDataCom
{
protected:
  int RetCode; // Код завершения

  int SetRetCode(int ret) { return RetCode = ret; }

public:
  TDataCom() : RetCode(DATAOK) {}
  virtual ~TDataCom() = 0 {}
  int GetRetCode()
  {
    int temp = RetCode;
    RetCode = DATAERR;
    return temp;
  }
};

#endif
