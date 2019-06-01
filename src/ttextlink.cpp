#include "ttextlink.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size) {
    MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
    MemHeader.pFree = MemHeader.pFirst;
    MemHeader.pLast = MemHeader.pFirst + (size - 1);
    PTTextLink pLink = MemHeader.pFirst;
    for (int i = 0; i < size - 1; ++i, ++pLink) {
        pLink->pNext = pLink + 1;
    }
    pLink->pNext = nullptr;
}

void TTextLink::PrintFreeLink(void) {
    PTTextLink pLink = MemHeader.pFree;
    std::cout << "List of free links" << std::endl;
    for (; pLink != nullptr; pLink = pLink->pNext) {
        std::cout << pLink->Str << std::endl;
    }
}

void* TTextLink::operator new(size_t size) {
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != nullptr)
        MemHeader.pFree = pLink->pNext;
    return pLink;
}

void TTextLink::operator delete(void* pM) {
    if (pM = nullptr)
        throw TextError;
    else {
        ((PTTextLink)pM)->pNext = MemHeader.pFree;
        MemHeader.pFree = (PTTextLink)pM;
    }
}

void TTextLink::MemCleaner(TText& txt) {
    std::string st;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext()) {
        if (st.find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    }
    PTTextLink pLink = MemHeader.pFree;
    for (; pLink != nullptr; pLink = pLink->pNext)
        strcpy(pLink->Str, "&&&");
    pLink = MemHeader.pFirst;
    for (; pLink <= MemHeader.pLast; ++pLink) {
        if (strstr(pLink->Str, "&&&") != nullptr)
            strcpy(pLink->Str, pLink->Str + 3);
        else
            delete pLink;
    }
}
