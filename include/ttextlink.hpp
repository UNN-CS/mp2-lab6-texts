#pragma once

#include <tdatavalue.hpp>

#include <iostream>

#define TEXTLINELENGTH 20
#define MEMSIZE 20

class TText;
class TTextLink;
typedef char TStr[TEXTLINELENGTH];
typedef TTextLink *PTTextLink;

class TTextMem
{
public:
  PTTextLink pFirst; // указатель на первое звено
  PTTextLink pLast;  // указатель на последнее звено
  PTTextLink pFree;  // указатель на первое свободное звено

  friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue
{
protected:
  TStr Str;                  // поле для хранения строки текста
  PTTextLink pNext, pDown;   // указатели по тек. уровень и на подуровень
  static TTextMem MemHeader; // система управления памятью
public:
  static void InitMemSystem(int size = MEMSIZE); // инициализация памяти
  static void PrintFreeLink(void);               // печать свободных звеньев
  static void MemCleaner(const TText &txt);      // сборка мусора

  void *operator new(size_t size); // выделение звена
  void operator delete(void *pM);  // освобождение звена

  TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL);
  ~TTextLink() {}
  int IsAtom() { return pDown == NULL; } // проверка атомарности звена
  PTTextLink GetNext() { return pNext; }
  PTTextLink GetDown() { return pDown; }
  PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }

protected:
  virtual void Print(std::ostream &os) { os << Str; }
  friend class TText;
};