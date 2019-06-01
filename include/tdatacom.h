// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdatacom.h - Copyright (c) Гергель В.П. 30.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Обработка кодов завершения

#ifndef __DATACOM_H__
#define __DATACOM_H__

#define DataOK   0
#define DataErr -1

// TDataCom является общим базовым классом
#define TextOK 0                 //ошибок нет
// коды ситуаций
#define TextNoDown 101           // нет подуровня для текущей позиции
#define TextNoNext 102           // нет следующего раздела текущего уровня
#define TextNoPrev 103           // текущая позиция в начале текста
// коды ошибок
#define TextError -102 // ошибка в тексте
#define TextNoMem -101 // нет памяти

class TDataCom
{
protected:
  int RetCode; // Код завершения

  int SetRetCode(int ret) { return RetCode = ret; }
public:
  TDataCom(): RetCode(DataOK) {}
  virtual ~TDataCom() = 0 {}
  int GetRetCode()
  {
    int temp = RetCode;
    RetCode = DataOK;
    return temp;
  }
};

#endif
