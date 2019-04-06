#include "TText.h"

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
    while (*p && (i < TextLineLength))
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

int TText::Reset (void)
{
    while (St.size())
        St.pop();
    pCurrent = pFirst;
    if (pCurrent != NULL)
    {
        St.push(pCurrent);
        if (pCurrent->pNext != NULL)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != NULL)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

int TText::IsTextEnded (void) const
{
    return St.empty();
}

int TText::GoNext (void)
{
    if (IsTextEnded())
        return 1;
    pCurrent = St.top();
    St.pop();
    if (pCurrent != pFirst)
    {
        if (pCurrent->pNext != NULL)
            St.push(pCurrent->pNext);
        if (pCurrent->pDown != NULL)
            St.push(pCurrent->pDown);
    }
    return IsTextEnded();
}

PTTextLink TText::GetFirstAtom (PTTextLink pl)
{
    PTTextLink t = pl;
    while (t->pDown)
    {
        St.push(t);
        t = t->pDown;
    }
    return t;
}

PTText TText::GetCopy()
{
    PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
    if (pFirst)
    {
        while (St.size())
            St.pop();
        while (1)
        {
            if (pl)
            {
                pl = GetFirstAtom(pl);
                St.push(pl);
                pl = pl->pDown;
            }
            else if (St.empty())
                break;
            else
            {
                pl1 = St.top();
                St.pop();
                if (strstr(pl1->Str, "CoPY") == NULL)
                {
                    pl2 = new TTextLink("CoPY", pl1, cpl);
                    St.push(pl2);
                    pl = pl1->pNext;
                    cpl = NULL;
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

void TText::PrintText (PTTextLink ptl)
{
    struct pt
    {
        PTTextLink ptr;
        int depth;
    } tmp, t;
    stack<pt> ts;
    if (ptl == NULL)
        return;
    tmp.ptr = ptl;
    tmp.depth = 0;
    ts.push(tmp);
    while (ts.size())
    {
        tmp = ts.top();
        ts.pop();
        for (int i = 0; i < tmp.depth; ++i)
            std::cout << "  ";
        tmp.ptr->Print(cout);
        cout << '\n';
        if (tmp.ptr->pNext != NULL)
        {
            t.ptr = tmp.ptr->pNext;
            t.depth = tmp.depth;
            ts.push(t);
        }
        if (tmp.ptr->pDown != NULL)
        {
            t.ptr = tmp.ptr->pDown;
            t.depth = tmp.depth + 1;
            ts.push(t);
        }
    }
}

void TText::Print (void)
{
    PrintText(pFirst);
}

PTTextLink TText::ReadText (ifstream &TxtFile)
{
    PTTextLink head = NULL, ptl;
    TStr s;
    int depth = 0;
    char c;
    bool branch = true;
    stack<PTTextLink> heigh;
    while (!TxtFile.eof())
    {
        if (depth > 0)
        {
            TxtFile.seekg(2 * (depth - 1), ios_base::cur);
            TxtFile.get(c);
            if (c == '}')
            {
                TxtFile.getline(s, TextLineLength);
                heigh.pop();
                --depth;
                continue;
            }
            TxtFile.get(c);
        }
        TxtFile.getline(s, TextLineLength);
        if (s[0] == '{')
        {
            branch = false;
            ++depth;
        }
        else
        {
            head = new TTextLink(s);
            if (branch)
            {
                if (heigh.size())
                {
                    heigh.top()->pNext = head;
                    heigh.pop();
                }
                else
                    ptl = head;
                heigh.push(head);
            }
            else
                heigh.top()->pDown = head;
            branch = true;
        }
    }
    return ptl;
}

void TText::Read (char * pFileName)
{
    ifstream file(pFileName);
    pFirst = ReadText(file);
    file.close();
}

void TText::Write (char * pFileName)
{
    ofstream file(pFileName);
    struct pt
    {
        PTTextLink ptr;
        int depth;
    } tmp, t;
    stack<pt> ts;
    int pre_depth = 0;
    if (pFirst == NULL)
        return;
    tmp.ptr = pFirst;
    tmp.depth = 0;
    ts.push(tmp);
    while (ts.size())
    {
        tmp = ts.top();
        ts.pop();
        if (pre_depth < tmp.depth)
        {
            for (int i = 0; i < pre_depth; ++i)
                file << "  ";
            file << "{\n";
        }
        if (pre_depth > tmp.depth)
        {
            for (int i = 0; i < tmp.depth; ++i)
                file << "  ";
            file << "}\n";
        }
        for (int i = 0; i < tmp.depth; ++i)
            file << "  ";
        file << tmp.ptr->Str << '\n';
        pre_depth = tmp.depth;
        if (tmp.ptr->pNext != NULL)
        {
            t.ptr = tmp.ptr->pNext;
            t.depth = tmp.depth;
            ts.push(t);
        }
        if (tmp.ptr->pDown != NULL)
        {
            t.ptr = tmp.ptr->pDown;
            t.depth = tmp.depth + 1;
            ts.push(t);
        }
    }
    file.close();
}
