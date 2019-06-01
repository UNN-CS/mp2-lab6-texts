#include "ttext.h"

#define BufLength 80

static char StrBuf[BufLength + 1];
static int TextLevel;

TText::TText(PTTextLink pl) {
    if (pl == nullptr)
        pl = new TTextLink();
    pFirst = pCurrent =pl;
}

void TText::GoFirstLink(void) {
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;
    if (pCurrent == nullptr)
        throw TextError;
}

void TText::GoDownLink(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pDown == nullptr)
        throw TextNoDown;
    Path.push(pCurrent);
    pCurrent = pCurrent->pDown;
}

void TText::GoNextLink(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext == nullptr)
        throw TextNoNext;
    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
}

void TText::GoPrevLink(void) {
    if (Path.empty())
        throw TextNoPrev;
    pCurrent = Path.top();
    Path.pop();
}

std::string TText::GetLine(void) {
    if (pCurrent == nullptr)
        return std::string("");
    else
        return std::string(pCurrent->Str);
}
void TText::SetLine(std::string s) {
    if (pCurrent == nullptr)
        throw TextError;
    strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}

void TText::InsDownLine(std::string s) {
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", pd, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = pl;
}

void TText::InsDownSection(std::string s) {
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", nullptr, pd);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = pl;
}

void TText::InsNextLine(std::string s) {
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pn = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", pn, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pNext = pl;
}

void TText::InsNextSection(std::string s) {
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pn = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", nullptr, pn);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pNext = pl;
}

void TText::DelDownLine(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pDown != nullptr) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == nullptr)
            pCurrent->pDown = pl2;
    }
}

void TText::DelDownSection(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pDown != nullptr) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}

void TText::DelNextLine(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == nullptr)
            pCurrent->pNext = pl2;
    }
}

void TText::DelNextSection(void) {
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
}

int TText::Reset(void) {
    while (!St.empty())
        St.pop();
    pCurrent = pFirst;
    if (pCurrent != nullptr) {
        St.push(pCurrent);
        if (pCurrent->pNext != nullptr)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != nullptr)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded(void) const {
    return !St.size();
}

int TText::GoNext(void) {
    if (!IsTextEnded()) {
        pCurrent = St.top();
        St.pop();
        if (pCurrent != pFirst) {
            if (pCurrent->pNext != nullptr)
                St.push(pCurrent->pNext);
            if (pCurrent->pDown != nullptr)
                St.push(pCurrent->pDown);
        }
    }
    return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) {
    PTTextLink tmp = pl;
    while (!tmp->IsAtom()) {
        St.push(tmp);
        tmp = tmp->GetDown();
    }
    return tmp;
}

PTText TText::GetCopy() {
    PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;
    if (pFirst != nullptr) {
        while (!St.empty()) St.pop();
        while (1) {
            if (pl != nullptr) {
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->GetDown();
            }
            else if (St.empty()) break;
            else {
                pl1 = St.top();
                St.pop();
                if (strstr(pl1->Str, "Copy") == nullptr) {
                    pl2 = new TTextLink("Copy", pl1, cpl);
                    St.push(pl2);
                    pl = pl1->pNext;
                    cpl = nullptr;
                }
                else {
                    pl2 = pl1->GetNext();
                    strcpy(pl1->Str, pl2->Str);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
        }
    }
    return new TText(cpl);
}

void TText::Print() {
    TextLevel = 0;
    PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl) {
    if (ptl != nullptr) {
        for (int i = 0; i < TextLevel; ++i)
            std::cout << " ";
        std::cout << " " << ptl->Str << std::endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}

void TText::Read(char* pFileName) {
    std::ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (!TxtFile.is_open())
        throw "Read error";
    pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(std::ifstream & TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while (TxtFile.eof() == 0) {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}') {
            TextLevel--;
            break;
        }
        else if (StrBuf[0] == '{') {
            ++TextLevel;
            ptl->pDown = ReadText(TxtFile);
        }
        else {
            ptl->pNext = new TTextLink(StrBuf, nullptr, nullptr);
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if (pHead->pDown == nullptr) {
        pHead = pHead->pNext;
        delete ptl;
    }
    return pHead;
}
