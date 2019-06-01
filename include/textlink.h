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
#include <cstring>
#include <iostream>

typedef char TStr[TextLineLength];

class TTextMem {
    PTTextLink pFirst;   
    PTTextLink pLast;    
    PTTextLink pFree;   
    friend class TTextLink;
};
typedef TTextMem* PTTextMem;

class TTextLink : public TDatValue {
protected:
    TStr Str;  
    PTTextLink pNext, pDown;  
    static TTextMem MemHeader; 
public:
    static void InitMemSystem(int size = MemSize); 
    static void PrintFreeLink(void);  
    void* operator new (size_t size); 
    void operator delete (void* pM);   
    static void MemCleaner(TText& txt); 
    TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr) {
        pNext = pn; pDown = pd;
        if (s != nullptr)
            strcpy(Str, s);
        else
            Str[0] = '\0';
    }
    ~TTextLink() {}
    int IsAtom() { return pDown == nullptr; } 
    PTTextLink GetNext() { return pNext; }
    PTTextLink GetDown() { return pDown; }
    PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
    virtual void Print(std::ostream& os) { os << Str; }
    friend class TText;
};

#endif
