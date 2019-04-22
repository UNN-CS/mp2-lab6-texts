#include "textlinc.h"

TTextMem TTextLink::MemHeader;

static void TTextLink::InitMemSystem (int size=MemSize) {
    char *p = new char[sizeof(TTextLink)*size];
    MemHeader.pFirst = (PTTextLink) p;
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size-1);
    PTTextLink pLink = MemHeader.pFirst;
    for(int i = 0; i < size-1; i++, pLink++) {
        pLink->pNext = pLink+1;
    }
    pLink->pNext = NULL;
} // Выделение и форматирование памяти
static void TTextLink::PrintFreeLink () {
    for(PTTextLink pLink = MemHeader.pFree; pLink != nullptr; pLink = pLink->pNext)
    std::cout<<pLink->Str<<std::endl;
}
void * operator new (size_t size) {
    PTTextLink pLink = MemHeader.pFree;
    if(MemHeader.pFree != nullptr)
        MemHeader.pFree = pLink->pNext;
    return pLink;
}
void operator delete (void *pM) {
    PTTextLink pLink = (PTTextLink)pM;
    pLink->pNext = MemHeader.pFree;
    MemHeader.pFree = pLink;
}
static void TTextLink::MemCleaner (TText &txt) {
    std::string st;
    for(txt.Reset(); !txt.IsTextEnded(); txt.GoNext()) {
        if(st.find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    }

    PTTextLink pLink = MemHeader.pFree;

    for(; pLink != nullptr; pLink = pLink->pNext)
        strcpy(pLink->Str, "&&&");

    pLink = MemHeader.pFirst;
    for(; pLink <= MemHeader.pLast; pLink++) {
        if(strstr(pLink->Str, "&&&") != nullptr)
            strcpy(pLink->Str, pLink->Str+3);
        else
            delete pLink;
    }
}
