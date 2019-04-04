#include "ttext.h"

const int BufLength = 20;
static int TextLevel = 0;
char StrBuf[BufLength];

TText::TText(PTTextLink pl) {
    if (!pl)
        pl = new TTextLink();
    pFirst = pCurrent = pl;
}

int TText::GoFirstLink() {
    while(Path.size())
        Path.pop();
    pCurrent = pFirst;
    if (!pCurrent)
        throw TextError;
    return 0;
}

int TText::GoDownLink() {
    if (pCurrent) {
        if (pCurrent->pDown) {
            Path.push(pCurrent);
            pCurrent = pCurrent->pDown;
        }
        else throw TextNoDown;
    }
    else throw TextError;
    return 0;
}

int TText::GoNextLink() {
    if (pCurrent) {
        if (pCurrent->pNext) {
            Path.push(pCurrent);
            pCurrent = pCurrent->pNext;
        }
        else throw TextNoNext;
    }
    else throw TextError;
    return 0;
}

int TText::GoPrevLink() {
    if (Path.empty())
        throw TextNoPrev;
    pCurrent = Path.top();
    Path.pop();
    return 0;
}

std::string TText::GetLine() {
    if (pCurrent)
        return pCurrent->Str;
    return "";
}

void TText::SetLine(std::string s) {
    if (!pCurrent)
        throw TextError;
    strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = 0;
}

void TText::InsDownLine(std::string s) {
    if (!pCurrent)
        throw TextError;
    PTTextLink pl = new TTextLink("", pCurrent->pDown, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = 0;
    pCurrent->pDown = pl;
}

void TText::InsDownSection(std::string s) {
    if (!pCurrent)
        throw TextError;
    PTTextLink pl = new TTextLink("", nullptr, pCurrent->pDown);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = 0;
    pCurrent->pDown = pl;
}

void TText::InsNextLine(std::string s) {
    if (!pCurrent)
        throw TextError;
    PTTextLink pl = new TTextLink("", pCurrent->pNext, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = 0;
    pCurrent->pNext = pl;
}

void TText::InsNextSection(std::string s) {
    if (!pCurrent)
        throw TextError;
    PTTextLink pl = new TTextLink("", nullptr, pCurrent->pNext);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = 0;
    pCurrent->pNext = pl;
}

void TText::DelDownLine() {
    if (!pCurrent)
        throw TextError;
    if (pCurrent->pDown)
        pCurrent->pDown = pCurrent->pDown->pNext;
    else throw TextNoDown;
}

void TText::DelDownSection() {
    if (!pCurrent)
        throw TextError;
    if (pCurrent->pDown)
        pCurrent->pDown = pCurrent->pDown->pNext;
    else throw TextNoDown;
}

void TText::DelNextLine() {
    if (!pCurrent)
        throw TextError;
    if (pCurrent->pNext)
        pCurrent->pNext = pCurrent->pNext->pNext;
    else throw TextNoNext;
}

void TText::DelNextSection() {
    if (!pCurrent)
        throw TextError;
    if (pCurrent->pNext)
        pCurrent->pNext = pCurrent->pNext->pNext;
    else throw TextNoNext;
}

int TText::Reset() {
    while (St.size())
        St.pop();
    pCurrent = pFirst;
    if (pCurrent) {
        St.push(pCurrent);
        if (pCurrent->pNext)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded() const {
    return St.empty();
}

int TText::GoNext() {
    if (!IsTextEnded()) {
        pCurrent = St.top();
        St.pop();
        if (pCurrent != pFirst) {
            if (pCurrent->pNext)
                St.push(pCurrent->pNext);
            if (pCurrent->pDown)
                St.push(pCurrent->pDown);
        }
    }
    return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) {
    PTTextLink tmp = pl;
    while(!tmp->IsAtom()) {
        St.push(tmp);
        tmp = tmp->pDown;
    }
    return tmp;
}

PTText TText::GetCopy() {
    PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;
    if (pFirst) {
        while (St.size())
            St.pop();
        while (true) {
            if (pl) {
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->GetDown();
            } else if (!St.size()) {
                break;
            } else {
                pl1 = St.top();
                St.pop();
                if (!strstr(pl1->Str, "Copy")) { // 1
                    pl2 = new TTextLink("Copy", pl1, cpl);
                    St.push(pl2);
                    pl = pl1->pNext;
                    cpl = nullptr;
                } else { // 2
                    pl2 = pl1->pNext;
                    strcpy(pl1->Str, pl2->Str);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
        }
    }
    return new TText(cpl);
}

void TText::Print(std::ostream& out) {
    TextLevel = 0;
    PrintText(out, pFirst);
}

void TText::PrintText(std::ostream& out, PTTextLink ptl) {
    if (ptl) {
        for (int i = 0; i < TextLevel; ++i)
            out << " ";
        out << " " << *ptl << std::endl;
        ++TextLevel;
        PrintText(out, ptl->GetDown());
        --TextLevel;
        PrintText(out, ptl->GetNext());
    }
}

void TText::Read(char *pFileName) {
    std::ifstream TxtFile;
    TxtFile.open(pFileName);
    TextLevel = 0;
    if (TxtFile)
        pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(std::ifstream &TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while(!TxtFile.eof()) {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}') {
            --TextLevel;
            break;
        }
        if (StrBuf[0] == '{') {
            ++TextLevel;
            ptl->pDown = ReadText(TxtFile);
        } else {
            ptl->pNext = new TTextLink(StrBuf, nullptr, nullptr);
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if (!pHead->pDown) {
        pHead = pHead->pNext;
        delete ptl;
    }
    return pHead;
}
