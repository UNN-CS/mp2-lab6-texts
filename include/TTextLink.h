#ifndef __TEXTLINK_H__
#define __TEXTLINK_H__

#include <string>
#include <iostream>
#include "TDatValue.h"

#define TextLineLength 20
#define MemSize 20

class TText;
class TTextLink;

typedef TTextLink* PTTextLink;
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
	PTTextLink pNext;
	PTTextLink pDown;
	static TTextMem MemHeader;

public:
	static void InitMemSystem(int size = MemSize);
	static void PrintFreeLink();
	void* operator new(size_t size);
	void operator delete(void* pM);
	static void MemCleaner(TText &txt);

	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL);
	~TTextLink();
	bool IsAtom();
	PTTextLink GetNext();
	PTTextLink GetDown();
	PTDatValue GetCopy();

protected:
	virtual void Print(std::ostream &os);
	friend class TText;
};

#endif 