#include "ttext.h"
#include <cstring>

#define BufLength 80

static char StrBuf[BufLength + 1];
static int TextLevel;

TText::TText(PTTextLink pl)
{
    if (pl == nullptr)
        pl = new TTextLink();
    pCurrent = pFirst = pl;
}

PTText TText::GetCopy()
{
    PTTextLink pl, pl1, pl2, cpl;
    pl = pFirst;
    cpl = nullptr;
    char s[5] = "Copy";

    if (pFirst != nullptr)
    {
        while (!St.empty())
            St.pop();

        while (true)
        {
            if (pl != nullptr)
            {
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->pDown;
            }
            else 
                if (St.empty()) break;
                else
                {
                    pl1 = St.top();
                    St.pop();

                    if (strstr(pl1->Str, "Copy") == nullptr)
                    {
                        pl2 = new TTextLink (s, pl1, cpl);
                        St.push(pl2);
                        pl = pl1->pNext;
                        cpl = nullptr;
                    }
                    else
                    {
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


void TText::GoFirstLink()
{
    while (!Path.empty())
        Path.pop(); 
    pCurrent = pFirst;
    if (pCurrent == nullptr)
        throw "Text error";
}

void TText::GoDownLink()
{
    if ((pCurrent != nullptr) && (pCurrent->pDown != nullptr))
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pDown;
    }
    else
        throw "Text error";
}

void TText::GoNextLink()
{
    if ((pCurrent != nullptr) && (pCurrent->pNext != nullptr))
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pNext;
    }
    else
        throw "text error";
}

void TText::GoPrevLink()
{
    if (Path.empty())
        throw "text no prev";
    else
    {
        pCurrent = Path.top();
        Path.pop();
    }
}


std::string TText::GetLine()
{
    if (pCurrent == nullptr)
        return std::string("");
    else
        return pCurrent->Str;
}

void TText::SetLine(std::string s)
{
    if (pCurrent == nullptr)
        throw "text error";
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}


void TText::InsDownLine(std::string s)
{
    if (pCurrent == nullptr)
        throw "text error";
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", pd, nullptr);
        std::strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl;
    }
}

void TText::InsDownSection(std::string s)
{
    if (pCurrent == nullptr)
        throw "text error";
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", nullptr, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pDown = pl;
    }
}

void TText::InsNextLine(std::string s)
{
    if (pCurrent == nullptr)
        throw "text error";
    else {
        PTTextLink pd = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", pd, nullptr);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
    }
}

void TText::InsNextSection(std::string s)
{
    if (pCurrent == nullptr)
        throw "text error";
    else {
        PTTextLink pd = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", nullptr, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0';
        pCurrent->pNext = pl;
    }
}

void TText::DelDownLine()
{
    if (pCurrent == nullptr)
        throw "text error";
    else if (pCurrent->pDown != nullptr)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == nullptr)
            pCurrent->pDown = pl2;
    }
}

void TText::DelDownSection()
{
    if (pCurrent == nullptr)
        throw "text error";
    else if (pCurrent->pDown != nullptr)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}

void TText::DelNextLine()
{
    if (pCurrent == nullptr)
        throw "text error";
    else if (pCurrent->pNext != nullptr)
    {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pNext == nullptr)
            pCurrent->pNext = pl2;
    }
}

void TText::DelNextSection()
{
    if (pCurrent == nullptr)
        throw "text error";
    else if (pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
}


int TText::Reset()
{
    while (!St.empty())
        St.pop();
    pCurrent = pFirst;
    if (pCurrent != nullptr)
    {
        St.push(pCurrent);
        if (pCurrent->pNext != nullptr)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != nullptr)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded()const
{
    return !St.size();
}

int TText::GoNext()
{
    if (!IsTextEnded())
    {
        pCurrent = St.top();
        St.pop();
        if (pCurrent->pNext != nullptr)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != nullptr)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}


void TText::Read(const char *pFileName)
{
    std::ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (!TxtFile.is_open())
        throw - 1;
    pFirst = ReadText(TxtFile);
}

void TText::Print()
{
    TextLevel = 0;
    PrintText(pFirst);
}


PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
    PTTextLink tmp = pl;
    while (!tmp->IsAtom())
    {
        St.push(tmp);
        tmp = tmp->GetDown();
    }
    return tmp;
}

void TText::PrintText(PTTextLink ptl)
{
    if (ptl != nullptr)
    {
        for (int i = 0; i < TextLevel; i++)
            std::cout << "  ";
        std::cout << " " << ptl->Str << std::endl;
        ++TextLevel; PrintText(ptl->GetDown());
        --TextLevel; PrintText(ptl->GetNext());
    }
}

PTTextLink TText::ReadText(std::ifstream &TxtFile)
{
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while (TxtFile.eof() == 0) {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}') {
            TextLevel--;
            break;
        }
        else if (StrBuf[0] == '{') {
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
