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
	PTTextLink pFirst;     // указатель на первое звено
	PTTextLink pLast;      // указатель на последнее звено
	PTTextLink pFree;      // указатель на первое свободное звено
	TTextMem() : pFirst(NULL), pLast(NULL), pFree(NULL) {};
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
	TStr Str;  // поле для хранения строки текста
	PTTextLink pNext, pDown;  // указатели по тек. уровень и на подуровень
	static TTextMem MemHeader; // система управления памятью
public:
	static void InitMemSystem(int size); // инициализация памяти
	static void PrintFreeLink(void);  // печать свободных звеньев
	void * operator new (size_t size); // выделение звена
	void operator delete (void *pM);   // освобождение звена
	static void MemCleaner(TText &txt); // сборка мусора
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
	int IsAtom() { return pDown == NULL; } // проверка атомарности звена
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
};