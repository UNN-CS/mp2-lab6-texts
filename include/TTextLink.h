#ifndef  __TTextLink_H
#define  __TTextLink_H


#include "TDatValue.h"
#include "TText.h"
#include "string.h"
#include "texters.h"
#include <iostream>

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
using namespace std;
class TTextLink : public TDatValue {
protected:
	TStr Str;  // ���� ��� �������� ������ ������
	PTTextLink pNext, pDown;  // ��������� �� ���. ������� � �� ����������
	static PTTextMem MemHeader; // ������� ���������� �������
public:
	static void InitMemSystem(int size = MemSize); // ������������� ������
	static void PrintFreeLink(void);  // ������ ��������� �������
	void * operator new (size_t size); // ��������� �����
	void operator delete (void *pM);   // ������������ �����
	static void MemCleaner(  TText& txt); // ������ ������
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) {
		pNext = pn; pDown = pd;
		if (s != NULL) strcpy(Str, s); else Str[0] = '\0';
	}
	~TTextLink() {}
	int IsAtom() { return pDown == NULL; } // �������� ����������� �����
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
};
#endif // ! 
