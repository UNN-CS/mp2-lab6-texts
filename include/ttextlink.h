#ifndef _TTEXTLINK_H_
#define _TTEXTLINK_H_
#include <iostream>
#include <cstring>
#include "tdatvalue.h"
#include "ttext.h"

class TText;
class TTextLink;
typedef TTextLink *PTTextLink;

class TTextMem {
    PTTextLink pFirst;     // указатель на первое звено
    PTTextLink pLast;      // указатель на последнее звено
    PTTextLink pFree;      // указатель на первое свободное звено
    friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
    TStr Str;  // поле для хранения строки текста
    PTTextLink pNext, pDown;  // указатели по тек. уровень и на подуровень
    static PTTextMem MemHeader; // система управления памятью
public:
    static void InitMemSystem (int size = MemSize); // инициализация памяти
    static void PrintFreeLink (void);  // печать свободных звеньев
    void * operator new (size_t size); // выделение звена
    void operator delete (void *pM);   // освобождение звена
    static void MemCleaner (TText &txt); // сборка мусора
    TTextLink (TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr) {
        pNext = pn; pDown = pd;
        if (s) strcpy(Str,s); else Str[0]='\0';
    }
    ~TTextLink() {}
    int IsAtom () {return pDown == nullptr;} // проверка атомарности звена
    PTTextLink GetNext() {return pNext;}
    PTTextLink GetDown() {return pDown;}
    PTDatValue GetCopy() {return new TTextLink(Str,pNext,pDown);}
protected:
    virtual void Print (std::ostream &os) {os << Str;}
    friend std::ostream &operator<<(std::ostream& os, TTextLink& obj) {
        os << obj.Str;
        return os;
    }
    friend class TText;
};

#endif  // _TTEXTLINK_H_
