#include "TText.h"
#define BufLength 90
static char StrBuf[BufLength + 1]; //Буфер для ввода строк
static int TextLevel;              // номер текущего уровня текста

TText::TText(PTTextLink pl)
{
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
    pCurrent = pl;
}
// Navigation
int TText::GoFirstLink()
{
    while (!Path.empty())
        Path.pop();
    pCurrent = pFirst;
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        SetRetCode(TextOK);
    return RetCode;
}
int TText::GoDownLink() //go to next string on Down
{
    SetRetCode(TextError);
    if (pCurrent != NULL)
        if (pCurrent->pDown != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pDown;
            SetRetCode(TextOK);
        }
    return RetCode;
}
int TText::GoNextLink() // go to next string on Next
{
    SetRetCode(TextError);
    if (pCurrent != NULL)
        if (pCurrent->pNext != NULL)
        {
            Path.push(pCurrent);
            pCurrent = pCurrent->pNext;
            SetRetCode(TextOK);
        }
    return RetCode;
}
int TText::GoPrevLink() // go to previous string
{
    if (Path.empty())
        SetRetCode(TextNoPrev);
    else
    {
        pCurrent = Path.top();
        Path.pop();
        SetRetCode(TextOK);
    }
    return RetCode;
}

//Access

string TText::GetLine() // reading current string
{
    if (pCurrent == NULL)
        return string("");
    else
        return string(pCurrent->Str);
}
void TText::SetLine(string s) // replacement current string
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}

//     Modification

void TText::InsDownLine(string s) //insertion string to Down(SubLevel)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink(NULL, pd, NULL); // я думаю при инициализации можно передать s.c_str()!!!!!
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set 0 if s.length > Str.length
        pCurrent->pDown = pl;
        SetRetCode(TextOK);
    }
}
void TText::InsDownSection(string s) // insertion section to Down (SubLevel)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink(NULL, NULL, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set 0 if s.length > Str.length
        pCurrent->pDown = pl;
        SetRetCode(TextOK);
    }
}
void TText::InsNextLine(string s) // insert string to cur level
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        strncpy(StrBuf, s.c_str(), TextLineLength);
        pCurrent->pNext = new TTextLink(StrBuf, pCurrent->pNext, nullptr);
        SetRetCode(TextOK);
    }
}
void TText::InsNextSection(string s)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        strncpy(StrBuf, s.c_str(), TextLineLength);
        pCurrent->pNext = new TTextLink(StrBuf, nullptr, pCurrent->pNext);
        SetRetCode(TextOK);
    }
}
void TText::DelDownSection() // delete sublevel (down section)
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}
void TText::DelDownLine() // delete down line
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == NULL)
            pCurrent->pDown = pl2;
    }
}

void TText::DelNextLine()
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL)
    {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pNext == NULL)
            pCurrent->pNext = pl2;
    }
}
void TText::DelNextSection()
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL)
    {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
}

/*     Iterator   */

int TText::Reset()
{
    while (!St.empty()) // clear stack
        St.pop();
    pCurrent = pFirst;
    if (pCurrent != NULL)
        St.push(pCurrent);
    if (pCurrent->pNext != NULL)
        St.push(pCurrent->pNext);
    if (pCurrent->pDown != NULL)
        St.push(pCurrent->pDown);
    return IsTextEnded();
}
int TText::IsTextEnded() const
{
    return (St.size() == 0);
}
int TText::GoNext()
{
    if (!IsTextEnded())
    {
        pCurrent = St.top();
        St.pop();
        if (pCurrent != pFirst)
        {
            if (pCurrent->pNext != NULL)
                St.push(pCurrent->pNext);
            if (pCurrent->pDown != NULL)
                St.push(pCurrent->pDown);
        }
    }
    return IsTextEnded();
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
PTText TText::getCopy() //text copying
{
    PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;

    if (pFirst != NULL)
    {
        while (!St.empty())
            St.pop(); // очистка стека
        while (true)
        {
            if (pl != NULL)
            { // переход к первому атому
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->GetDown();
            }
            else if (St.empty())
                break;
            else
            {
                pl1 = St.top();
                St.pop();
                if (strstr(pl1->Str, (char *)"Copy") == NULL)
                { // первый этап создания копии
                    // создание копии - pDown на уже скопированный подуровень
                    pl2 = new TTextLink((char *)"Copy", pl1, cpl); // pNext на оригинал
                    St.push(pl2);
                    pl = pl1->GetNext();
                    cpl = NULL;
                }
                else
                { // второй этап создания копии
                    pl2 = pl1->GetNext();
                    strncpy(pl1->Str, pl2->Str, TextLineLength);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
        }
    }
    return new TText(cpl);
}
void TText::Print()
{
    TextLevel = 0;
    PrintText(pFirst);
    Reset();
}

void TText::PrintText(PTTextLink ptl)
{
    if (ptl != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
            cout << " ";
        cout << " " << ptl->Str << endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}

void TText::Read(char *pFileName)
{
    ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (&TxtFile != NULL)
        pFirst = ReadText(TxtFile);
}
PTTextLink TText::ReadText(ifstream &TxtFile)
{
    string buf;
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    if (!TxtFile.is_open())
    {
        SetRetCode(TextError);
        throw "file didn't open";
    }
    while (TxtFile.eof() == 0)
    {
        GetLine();
        if (buf.front() == '}')
        {
            TextLevel--;
            break;
        }
        else if (buf.front() == '{')
        {
            TextLevel++;
            ptl->pDown = ReadText(TxtFile);
        }
        else //присоеднение следующей строки
        {
            ptl->pNext = new TTextLink((char *)buf.c_str());
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if (pHead->pDown == NULL) //удаление первой строки если нет подуровня
    {
        pHead = pHead->pNext;
        delete ptl;
    }
    return pHead;
}
void TText::Write(char *pFileName)
{
    TextLevel = 0;
    ofstream TxtFile(pFileName);
    PrintTextFile(pFirst, TxtFile);
    Reset();
}
void TText::PrintTextFile(PTTextLink pl, ofstream &txtFile)
{
    SetRetCode(TextError);
    if (pl != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
            txtFile << " ";
        txtFile << pl->Str << endl;
        TextLevel++;
        PrintTextFile(pl->GetDown(), txtFile);
        TextLevel--;
        PrintTextFile(pl->GetNext(), txtFile);
    }
}