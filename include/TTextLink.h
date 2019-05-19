#ifndef __TTEXTLINK_H__
#define __TTEXTLINK_H__

#include <string.h>
#include <iostream>
#include "tdatvalue.h"
#include "TText.h"

#define TextLineLength  20
#define MemSize         20

class TText;
class TTextLink;
typedef TTextLink *PTTextLink;

typedef char TStr[TextLineLength];

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
 static TTextMem MemHeader; // система управления памятью
public:
 static void InitMemSystem (int size=MemSize); // инициализация памяти
 static void PrintFreeLink (void);  // печать свободных звеньев
 void * operator new (size_t size); // выделение звена
 void operator delete (void *pM);   // освобождение звена
 static void MemCleaner (TText &txt); // сборка мусора
 TTextLink (TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL){
  pNext = pn; pDown = pd;
  if (s != NULL) 
	  strcpy(Str,s); 
  else Str[0]='\0';
 }
 ~TTextLink() {}
 int IsAtom () {return pDown == NULL;} // проверка атомарности звена
 PTTextLink GetNext() {return pNext;}
 PTTextLink GetDown() {return pDown;}
 PTDatValue GetCopy() {return new TTextLink(Str,pNext,pDown);}
protected:
 virtual void Print (std::ostream &os) {os << " " << Str;}
 TTextLink & operator=( TTextLink &q); // присваивание
 friend std::ostream& operator<<(std::ostream& os, const TTextLink& instance);
 friend class TText;
};

#endif