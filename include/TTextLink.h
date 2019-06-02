#pragma once
#include <string.h>
#include "TDatValue.h"

#define TextLineLength 20
#define MemSize 20

using namespace std;

class TText;
class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem {
	PTTextLink pFirst;     // óêàçàòåëü íà ïåðâîå çâåíî
	PTTextLink pLast;      // óêàçàòåëü íà ïîñëåäíåå çâåíî
	PTTextLink pFree;      // óêàçàòåëü íà ïåðâîå ñâîáîäíîå çâåíî
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
	TStr Str;  // ïîëå äëÿ õðàíåíèÿ ñòðîêè òåêñòà
	PTTextLink pNext, pDown;  // óêàçàòåëè ïî òåê. óðîâåíü è íà ïîäóðîâåíü
	static TTextMem MemHeader; // ñèñòåìà óïðàâëåíèÿ ïàìÿòüþ
public:
	static void InitMemSystem(int size = MemSize); // èíèöèàëèçàöèÿ ïàìÿòè
	static void PrintFreeLink(void);  // ïå÷àòü ñâîáîäíûõ çâåíüåâ
	void * operator new (size_t size); // âûäåëåíèå çâåíà
	void operator delete (void *pM);   // îñâîáîæäåíèå çâåíà
	static void MemCleaner(TText &txt); // ñáîðêà ìóñîðà
	TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr) {
		pNext = pn; pDown = pd;
		if (s != nullptr)
			strcpy(Str, s);
		else
			Str[0] = '\0';
	}
	~TTextLink() {}
	int IsAtom() { return pDown == NULL; } // ïðîâåðêà àòîìàðíîñòè çâåíà
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
	friend ostream& operator <<(ostream& os, TTextLink tl);
};

