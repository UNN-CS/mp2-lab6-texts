#include <string>
#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;

void TTextLink :: InitMemSystem (int size) { // инициализация памяти
  MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink)*size];
  MemHeader.pFree  = MemHeader.pFirst;
  MemHeader.pLast  = MemHeader.pFirst + (size-1);
  PTTextLink pLink = MemHeader.pFirst;
  for (int i = 0; i < size - 1; i++, pLink++ ) { // размерка памяти
    pLink -> pNext = pLink + 1;
  }
  pLink -> pNext = NULL;
}

void TTextLink :: PrintFreeLink (void) { // печать свободных звеньев
  PTTextLink pLink = MemHeader.pFree;
  std::cout << "List of free links" << std::endl;
  for ( ; pLink != NULL; pLink = pLink -> pNext )
    std::cout << pLink -> Str << std::endl;
}

void * TTextLink :: operator new (size_t size) { // выделение звена
  PTTextLink pLink = MemHeader.pFree;
  if (MemHeader.pFree != NULL) 
	  MemHeader.pFree = pLink->pNext;
  else
	  throw -1;
  return pLink;
}

void TTextLink :: operator delete (void *pM) { // освобождение звена
	PTTextLink pLink = (PTTextLink)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

void TTextLink :: MemCleaner(TText &txt) { // сборка мусора
  // пробная версия - в памяти только один текст
  std::string st;
  // маркировка строк текста - маркер "&&&"
  for ( txt.Reset(); !txt.IsTextEnded(); txt.GoNext() ) {
	st = txt.GetLine();
    if ( st.find("&&&") != 0 ) 
		txt.SetLine("&&&" + txt.GetLine());
  }
  // маркировка списка свободных звеньев
  PTTextLink pLink = MemHeader.pFree;
  for ( ; pLink != NULL; pLink = pLink->pNext ) 
	  strcpy(pLink->Str,"&&&");
  // сборка мусора
  pLink = MemHeader.pFirst;
  for ( ; pLink <= MemHeader.pLast; pLink++ ) {
    if ( strstr(pLink->Str,"&&&") != NULL ) { // строка текста или свобоное звено
      strcpy(pLink->Str, pLink->Str+3);        // снятие маркировки
    }
    else 
		delete pLink; // "неучтенное" звено в список свободных
  }
}

TTextLink & TTextLink :: operator= (TTextLink &q) {
	*this = *(PTTextLink)GetCopy();
	return *this;
}

std::ostream& operator<<(std::ostream& os, const TTextLink& instance) {
	return os << " " << instance.Str;
}
