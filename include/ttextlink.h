#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__

#define TextOK 0

#define TextNoDown 101
#define TextNoNext 102
#define TextNoPrev 103

#define TextError -102
#define TextNoMem -101

#define TextLineLength 20
#define MemSize 20

#include "tdatvalue.h"
#include "ttext.h"
#include <string>
#include <iostream>

typedef char TStr[TextLineLength];

class TTextMem {
    PTTextLink pFirst;     // указатель на первое звено
    PTTextLink pLast;      // указатель на последнее звено
    PTTextLink pFree;      // указатель на первое свободное звено
    friend class TTextLink;
};
typedef TTextMem* PTTextMem;

class TTextLink : public TDatValue {
protected:
    TStr Str;  // поле для хранения строки текста
    PTTextLink pNext, pDown;  // указатели по тек. уровень и на подуровень
    static TTextMem MemHeader; // система управления памятью
public:
    static void InitMemSystem(int size = MemSize); // инициализация памяти
    static void PrintFreeLink(void);  // печать свободных звеньев
    void* operator new (size_t size); // выделение звена
    void operator delete (void* pM);   // освобождение звена
    static void MemCleaner(TText& txt); // сборка мусора
    TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr) {
        pNext = pn; pDown = pd;
        if (s != nullptr)
            std::strcpy(Str, s);
        else
            Str[0] = '\0';
    }
    ~TTextLink() {}
    int IsAtom() { return pDown == nullptr; } // проверка атомарности звена
    PTTextLink GetNext() { return pNext; }
    PTTextLink GetDown() { return pDown; }
    PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
    virtual void Print(std::ostream& os) { os << Str; }
    friend class TText;
};

#endif
