#include "TText.h"
#include <string>

TText::TText (PTTextLink pl)
{
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
    pCurrent = pFirst;
}

int TText::GoFirstLink (void)
{
    while (Path.size())
        Path.pop();
    pCurrent = pFirst;
    return pCurrent != NULL;
}

int TText::GoDownLink (void)
{
    if ((pCurrent != NULL) && (pCurrent->pDown != NULL))
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pDown;
        return 0;
    }
    return 1;
}

int TText::GoNextLink (void)
{
    if ((pCurrent != NULL) && (pCurrent->pNext != NULL))
    {
        Path.push(pCurrent);
        pCurrent = pCurrent->pNext;
        return 0;
    }
    return 1;
}

int TText::GoPrevLink (void)
{
    if (Path.empty())
        return 1;
    pCurrent = Path.top();
    Path.pop();
    return 0;
}

string TText::GetLine(void)
{
    if (pCurrent == NULL)
        return "";
    return string(pCurrent->Str);
}

void TText::SetLine ( string s)
{
    if (pCurrent == NULL)
        throw -1;
    const char* p = s.c_str();
    char* q = pCurrent->Str;
    int i = 1;
    while (p && (i < TextLineLength))
        *(q++) = *(p++);
    *q = '\0';
}

void TText::InsDownLine (string s)
{
    if (pCurrent == NULL)
        throw -1;
    PTTextLink p = new TTextLink(NULL, pCurrent->GetDown());
    strncpy(p->Str, s.c_str(), TextLineLength);
    p->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = p;
}

void TText::InsDownSection (string s)
{
    if (pCurrent == NULL)
        throw -1;
    PTTextLink p = new TTextLink(NULL, NULL, pCurrent->GetDown());
    strncpy(p->Str, s.c_str(), TextLineLength);
    p->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = p;
}

void TText::InsNextLine (string s)
{
    if (pCurrent == NULL)
        throw -1;
    PTTextLink p = new TTextLink(NULL, pCurrent->GetNext());
    strncpy(p->Str, s.c_str(), TextLineLength);
    p->Str[TextLineLength - 1] = '\0';
    pCurrent->pNext = p;
}

void TText::InsNextSection (string s)
{
    if (pCurrent == NULL)
        throw -1;
    PTTextLink p = new TTextLink(NULL, NULL, pCurrent->GetDown());
    strncpy(p->Str, s.c_str(), TextLineLength);
    p->Str[TextLineLength - 1] = '\0';
    pCurrent->pNext = p;
    pCurrent->pDown = NULL;
}

void TText::DelDownLine (void)
{
    if (pCurrent == NULL)
        throw -1;
    if ((pCurrent->pDown == NULL) || (pCurrent->pDown->pDown != NULL))
        return;
    pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelDownSection (void)
{
    if (pCurrent == NULL)
        throw -1;
    if (pCurrent->pDown == NULL)
        return;
    pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelNextLine (void)
{
    if (pCurrent == NULL)
        throw -1;
    if ((pCurrent->pNext == NULL) || (pCurrent->pNext->pDown != NULL))
        return;
    pCurrent->pNext = pCurrent->pNext->pNext;
}

void TText::DelNextSection (void)
{
    if (pCurrent == NULL)
        throw -1;
    if (pCurrent->pNext == NULL)
        return;
    pCurrent->pNext = pCurrent->pNext->pNext;
}
