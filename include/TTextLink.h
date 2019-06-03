#ifndef _TEXTLINK_H
#define _TEXTLINK_H

#include <iostream>
#include <string.h>
#include "TDatValue.h"

#define TextLineLength 20
#define MemSize 20

class TText;
class TTextMem;
typedef TTextMem *PTTextMem;
class TTextLink;
typedef TTextLink *PTTextLink;

using namespace std;
typedef char TStr[TextLineLength];

class TTextMem
{
protected:
	PTTextLink pFirst;     // указатель на первое звено
	PTTextLink pLast;      // указатель на последнее звено
	PTTextLink pFree;      // указатель на первое свободное звено
	friend class TTextLink;
};

class TTextLink : public TDatValue
{
protected:
	TStr Str;                  // поле для хранения строки текста
	PTTextLink pNext, pDown;   // указатели по тек. уровень и на подуровень
	static TTextMem MemHeader; // система управления памятью
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
public:
	TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr);

	~TTextLink() {}
	static void InitMemSystem(int size = MemSize); // инициализация памяти
	static void PrintFreeLink(void);               // печать свободных звеньев
	void * operator new (size_t size);             // выделение звена
	void operator delete (void *pM);               // освобождение звена
	void MemCleaner(TText txt);                    // сборка мусора
	int IsAtom() { return pDown == nullptr; }      // проверка атомарности звена
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
};

#endif