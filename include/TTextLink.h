#pragma once

#include "tdatvalue.h"
#include <iostream>

using namespace std;

const int TextLineLength = 40;

class TText;
class TTextLink;

typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];


class TTextMem {
	PTTextLink pFirst;     // ��������� �� ������ �����
	PTTextLink pLast;      // ��������� �� ��������� �����
	PTTextLink pFree;      // ��������� �� ������ ��������� �����
	TTextMem() : pFirst(NULL), pLast(NULL), pFree(NULL) {};
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
	TStr Str;  // ���� ��� �������� ������ ������
	PTTextLink pNext, pDown;  // ��������� �� ���. ������� � �� ����������
	static TTextMem MemHeader; // ������� ���������� �������
public:
	static void InitMemSystem(int size); // ������������� ������
	static void PrintFreeLink(void);  // ������ ��������� �������
	void * operator new (size_t size); // ��������� �����
	void operator delete (void *pM);   // ������������ �����
	static void MemCleaner(TText &txt); // ������ ������
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) {
		pNext = pn; pDown = pd;
		if (s != NULL) strcpy_s(Str, s); 
		else Str[0] = '\0';
	}
	TTextLink(string s)
	{
		pNext = nullptr; pDown = nullptr;
		strcpy_s(Str, s.c_str());
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