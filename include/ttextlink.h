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
    PTTextLink pFirst;     // ��������� �� ������ �����
    PTTextLink pLast;      // ��������� �� ��������� �����
    PTTextLink pFree;      // ��������� �� ������ ��������� �����
    friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
    TStr Str;  // ���� ��� �������� ������ ������
    PTTextLink pNext, pDown;  // ��������� �� ���. ������� � �� ����������
    static PTTextMem MemHeader; // ������� ���������� �������
public:
    static void InitMemSystem (int size = MemSize); // ������������� ������
    static void PrintFreeLink (void);  // ������ ��������� �������
    void * operator new (size_t size); // ��������� �����
    void operator delete (void *pM);   // ������������ �����
    static void MemCleaner (TText &txt); // ������ ������
    TTextLink (TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr) {
        pNext = pn; pDown = pd;
        if (s) strcpy(Str,s); else Str[0]='\0';
    }
    ~TTextLink() {}
    int IsAtom () {return pDown == nullptr;} // �������� ����������� �����
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
