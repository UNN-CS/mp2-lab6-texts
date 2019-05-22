#include "TText.h"

static char StrBuf[BufLength + 1];
static int TextLevel;

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
    if (pl == nullptr)
        throw std::runtime_error("Link is nullptr!");
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
    if (ptl == nullptr)
        throw std::runtime_error("Argument = nullptr");
    if (ptl == nullptr)
    {
        for (int i = 0; i < TextLevel; i++)
            std::cout << '-';
        std::cout << '|' << ptl->Str << std::endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}

PTTextLink TText::ReadText(std::ifstream &TxtFile)
{
    PTTextLink pRoot, pCur;
    pRoot = pCur = new TTextLink();
    while (!TxtFile.eof())
    {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}')
        {
            TextLevel--;
            break;
        }
        else if (StrBuf[0] == '{')
        {
            TextLevel++;
            pCur->pDown = ReadText(TxtFile);
        }
        else
        {
            pCur->pNext = new TTextLink(StrBuf);
            pCur = pCur->pNext;
        }
    }
    pCur = pRoot;
    if (pRoot->pDown == nullptr)
    {
        pRoot = pRoot->pNext;
        delete pCur;
    }
    return pRoot;
}

TText::TText(PTTextLink pl)
{
    if (pl == nullptr)
        pl = new TTextLink();
    pFirst = pl;
    pCurrent = nullptr;

    textLevel = 0;
}

int TText::GoFirstLink(void)
{
    SetRetCode(TextError);
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;
    if (pCurrent != nullptr)
        SetRetCode(TextOk);
    return RetCode;
}

int TText::GoDownLink(void)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent->pDown == nullptr)
        SetRetCode(TextNoDown);
    else
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pDown;
        SetRetCode(TextOk);
    }
    return RetCode;
}

int TText::GoNextLink(void)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent->pNext == nullptr)
        SetRetCode(TextNoNext);
    else
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pNext;
        SetRetCode(TextOk);
    }
    return RetCode;
}

int TText::GoPrevLink(void)
{
    if (Path.empty())
        SetRetCode(TextNoPrev);
    else
    {
        pCurrent = Path.top();
        Path.pop();
        SetRetCode(TextOk);
    }
    return RetCode;
}

std::string TText::GetLine(void)
{
    if (pCurrent == nullptr)
    {
        SetRetCode(TextError);
        return "";
    }
    else
        return std::string(pCurrent->Str);
}

void TText::SetLine(std::string s)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (s.length() > TextLineLength)
        SetRetCode(TextTooLongString);
    else
    {
        strncpy_s(pCurrent->Str, s.c_str(), TextLineLength);
    }
}

void TText::InsDownLine(std::string s)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (s.length() > TextLineLength)
        SetRetCode(TextTooLongString);
    else
    {
        PTTextLink downLine = new TTextLink("", pCurrent->pDown, nullptr);
        strncpy_s(downLine->Str, s.c_str(), TextLineLength);
        pCurrent->pDown = downLine;
        SetRetCode(TextOk);
    }
}

void TText::InsDownSection(std::string s)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (s.length() > TextLineLength)
        SetRetCode(TextTooLongString);
    else
    {
        PTTextLink pl = new TTextLink("", nullptr, pCurrent->pDown);
        strncpy_s(pl->Str, s.c_str(), TextLineLength);
        pCurrent->pDown = pl;
        SetRetCode(TextOk);
    }
}

void TText::InsNextLine(std::string s)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (s.length() > TextLineLength)
        SetRetCode(TextTooLongString);
    else
    {
        PTTextLink nextLine = new TTextLink("", pCurrent->pNext, nullptr);
        strncpy_s(nextLine->Str, s.c_str(), TextLineLength);
        pCurrent->pNext = nextLine;
        SetRetCode(TextOk);
    }
}

void TText::InsNextSection(std::string s)
{
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (s.length() > TextLineLength)
        SetRetCode(TextTooLongString);
    else
    {
        PTTextLink nextSection = new TTextLink("", nullptr, pCurrent->pNext);
        strncpy_s(nextSection->Str, s.c_str(), TextLineLength);
        pCurrent->pNext = nextSection;
        SetRetCode(TextOk);
    }
}

void TText::DelDownLine(void)
{
    SetRetCode(TextOk);
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent -> pDown == nullptr)
        SetRetCode(TextNoDown);
    else
    {
        PTTextLink downLine = pCurrent->pDown;
        if (downLine->pDown == nullptr)
            pCurrent->pDown = downLine->pNext;
    }
}

void TText::DelDownSection(void)
{
    SetRetCode(TextOk);
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent->pDown == nullptr)
        SetRetCode(TextNoDown);
    else
        pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelNextLine(void)
{
    SetRetCode(TextOk);
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent->pNext == nullptr)
        SetRetCode(TextNoNext);
    else
    {
        PTTextLink nextLine = pCurrent->pNext;
        if (nextLine->pDown == nullptr)
            pCurrent->pNext = nextLine->pNext;
    }
}

void TText::DelNextSection(void)
{
    SetRetCode(TextOk);
    if (pCurrent == nullptr)
        SetRetCode(TextError);
    else if (pCurrent->pNext == nullptr)
        SetRetCode(TextNoNext);
    else
        pCurrent->pNext = pCurrent->pNext->pNext;
}

int TText::Reset(void)
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

int TText::GoNext(void)
{
    if (!IsTextEnded())
    {
        SetRetCode(TextOk);
        pCurrent = St.top();
        St.pop();
        if (pCurrent != pFirst)
        {
            if (pCurrent->pNext != nullptr)
                St.push(pCurrent->pNext);
            if (pCurrent->pDown != nullptr)
                St.push(pCurrent->pDown);
        }
    }
    if (IsTextEnded())
        SetRetCode(TextEnded);
    return GetRetCode();
}

PTText TText::GetCopy()
{
    PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;
    if (pFirst != nullptr)
    {
        while (!St.empty())
            St.pop();
        while (1)
            if (pl != nullptr)
            {
                St.push(pl);
                pl = pl->GetDown();
            }
            else if (St.empty())
                break;
            else
            {
                pl1 = St.top();
                St.pop();
                if (strstr(pl1->Str, "Copy") == nullptr)
                {
                    pl2 = new TTextLink("Copy", pl1, cpl);
                    St.push(pl2);
                    pl = pl1->GetNext();
                    cpl = nullptr;
                }
                else
                {
                    strncpy_s(pl1->Str, pl1->pNext->Str, TextLineLength);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
    }
    return new TText(cpl);
}

void TText::Print()
{
    TextLevel = 0;
    PrintText(pFirst);
}

void TText::Read(char *pFileName)
{
    std::ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (TxtFile.is_open())
        pFirst = ReadText(TxtFile);
}

void TText::Write(char *pFileName)
{
    std::ofstream TxtFile(pFileName);
    TextLevel = 0;
    PTTextLink pl = pFirst;
    if (pl != nullptr)
    {
        if (TxtFile.is_open())
        {
            TxtFile << "{" << std::endl;
            while (!St.empty())
                St.pop();
            while (1)
            {
                if (pl != nullptr)
                {
                    TxtFile << pl->Str << std::endl;
                    St.push(pl);
                    pl = pl->GetDown();
                    if (pl != nullptr)
                        TxtFile << "{" << std::endl;
                }
                else if (St.empty())
                    break;
                else
                {
                    pl = St.top();
                    St.pop();
                    pl = pl->GetNext();
                    if (pl == nullptr)
                        TxtFile << "}" << std::endl;
                }
            }
        }
    }
}