#include "TTextLink.h"
#include "TText.h"
// #include <conio.h>
#include <iostream>

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size) { // инициализация памяти
    char Line[100];
    MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink)*size];
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size -1);
    PTTextLink pLink = MemHeader.pFirst;
    for (int i = 0; i < size-1; i++, pLink++) { // разметка памяти
        pLink->pNext = pLink + 1;
    }
    pLink->pNext = NULL;
}

void TTextLink::PrintFreeLink(void) { // печать свободных звеньев
    PTTextLink pLink = MemHeader.pFree;
    cout << "List of free links" << endl;
    for ( ; pLink != NULL; pLink = pLink->pNext)
        cout << pLink->Str << endl;
}

void * TTextLink::operator new(size_t size) { //выделение звена
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != NULL) 
        MemHeader.pFree = pLink->pNext;
    return pLink;
}

void TTextLink::operator delete(void *pm) { // освобождение звена
    /// WRITE // ready
    PTTextLink pLink = (PTTextLink)pm;
    pLink->pNext = MemHeader.pFree;
    MemHeader.pFree = pLink;
}

void TTextLink::MemCleaner(TText &txt) { // сборка мусора
    string st;
    // маркировка строк текста маркером "&&&"
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext()) {
        if (st.find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    }
    // маркировка списка свободных звеньев
    PTTextLink pLink = MemHeader.pFree;
    for ( ; pLink != NULL; pLink = pLink->pNext)
        strcpy(pLink->Str, "&&&");
    // сборка мусора
    pLink = MemHeader.pFirst;
    for ( ; pLink <= MemHeader.pLast; pLink++) {
        if (strstr(pLink->Str, "&&&") != NULL) { // строка текста или свободное звено
            strcpy(pLink->Str, pLink->Str+3); // снятие маркировки
        }
        else delete pLink; // "неучтенное звено в список свободных"
    }
}


ostream& operator<<(ostream& out, TTextLink ptl) {
    out << ptl.Str;
    return out;
}
