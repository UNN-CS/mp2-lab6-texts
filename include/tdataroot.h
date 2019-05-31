// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdataroot.h - Copyright (c) Гергель В.П. 28.07.2000 (06.08)
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Динамические структуры данных - базовый (абстрактный) класс - версия 3.2
//   память выделяется динамически или задается методом SetMem

#ifndef __DATAROOT_H__
#define __DATAROOT_H__

#include "tdatacom.h"

#define DefMemSize   25  // размер памяти по умолчанию

#define DataEmpty  -101  // СД пуста
#define DataFull   -102  // СД переполнена
#define DataNoMem  -103  // нет памяти

typedef int    TElem;    // тип элемента СД
typedef TElem* PTElem;
typedef int    TData;    // тип значений в СД

enum TMemType { MEM_HOLDER, MEM_RENTER };

class TDataRoot: public TDataCom
{
protected:
  PTElem pMem;      // память для СД
  int MemSize;      // размер памяти для СД
  int DataCount;    // количество элементов в СД
  TMemType MemType; // режим управления памятью

  void SetMem(void *p, int Size);             // задание памяти
public:
  virtual ~TDataRoot();
  TDataRoot(int Size = DefMemSize);
  virtual bool IsEmpty(void) const;           // контроль пустоты СД
  virtual bool IsFull (void) const;           // контроль переполнения СД
  virtual void  Put   (const TData &Val) = 0; // добавить значение
  virtual TData Get   (void)             = 0; // извлечь значение

  // служебные методы
  virtual int  IsValid() = 0;                 // тестирование структуры
  virtual void Print()   = 0;                 // печать значений

  // дружественные классы
  friend class TMultiStack;
  friend class TSuperMultiStack;
  friend class TComplexMultiStack;
};

#endif
