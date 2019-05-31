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
		PTTextLink pFirst;  
		PTTextLink pLast;   
		PTTextLink pFree;   
		friend class TTextLink;
};

class TTextLink : public TDatValue
{
	protected:
		TStr Str;         
		PTTextLink pNext, pDown; 
		static TTextMem MemHeader;  
		virtual void Print(ostream &os) { os << Str; }
		friend class TText;
	public:
		TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr);

		~TTextLink() {}
		static void InitMemSystem(int size = MemSize); 
		static void PrintFreeLink(void);            
		void * operator new (size_t size);   
		void operator delete (void *pM);   
		void MemCleaner(TText txt); 
		
		int IsAtom()
		{
			return pDown == nullptr;
		}  
		
		PTTextLink GetNext()
		{
			return pNext;
		}
		
		PTTextLink GetDown()
		{
			return pDown;
		}
		
		PTDatValue GetCopy()
		{
			return new TTextLink(Str, pNext, pDown);
		}
};

#endif