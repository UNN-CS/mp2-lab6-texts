#ifndef _TTEXTLINK_H_
#define _TTEXTLINK_H_

#include "DatValue.h"
#include <string.h>
#include <iostream>
#include <stdexcept>

class TTextLink;
class TTextMem;
class TText;

const int TextLineLength = 255;
const int MemSize = 100;

typedef TTextLink *PTTextLink;
typedef TTextMem *PTTextMem;
typedef char TStr[TextLineLength];

class TTextMem {
    PTTextLink pFirst;     // указатель на первое звено
    PTTextLink pLast;      // указатель на последнее звено
    PTTextLink pFree;      // указатель на первое свободное звено
    friend class TTextLink;

 public:
    unsigned int freeCount;
};

class TTextLink : public TDatValue {
 protected:
    TStr Str;  // поле для хранения строки текста
    PTTextLink pNext, pDown;  // указатели по тек. уровень и на подуровень
    static TTextMem MemHeader; // система управления памятью

    virtual void Print(std::ostream &os) { os << Str << std::endl; }
    friend class TText;
 public:
    TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr);
    ~TTextLink() {}

    static void InitMemSystem(int size = MemSize);  // инициализация памяти
    static void PrintFreeLink(void);  // печать свободных звеньев
    void * operator new (size_t size);  // выделение звена
    void operator delete (void *pM);  // освобождение звена
    static void MemCleaner(TText txt);  // сборка мусора	
    int IsAtom() { return pDown == nullptr; }  // проверка атомарности звена
    PTTextLink GetNext() { return pNext; }
    PTTextLink GetDown() { return pDown; }
    PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }

    static void DelMemSystem();
    static unsigned int GetFreeCount() { return MemHeader.freeCount; }
};

#endif