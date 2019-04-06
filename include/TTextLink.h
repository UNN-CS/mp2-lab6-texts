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
	PTTextLink pFirst;     // указатель на первое звено
	PTTextLink pLast;      // указатель на последнее звено
	PTTextLink pFree;      // указатель на первое свободное звено
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;
using namespace std;
class TTextLink : public TDatValue {
protected:
	TStr Str;  // поле для хранения строки текста
	PTTextLink pNext, pDown;  // указатели по тек. уровень и на подуровень
	static PTTextMem MemHeader; // система управления памятью
public:
	static void InitMemSystem(int size = MemSize); // инициализация памяти
	static void PrintFreeLink(void);  // печать свободных звеньев
	void * operator new (size_t size); // выделение звена
	void operator delete (void *pM);   // освобождение звена
	static void MemCleaner(  TText& txt); // сборка мусора
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) {
		pNext = pn; pDown = pd;
		if (s != NULL) strcpy(Str, s); else Str[0] = '\0';
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
#endif // ! 
