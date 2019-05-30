#define BufLength 80
#include <conio.h>
#include "TText.h"
#include "texters.h"
#include <iostream>

static char StrBuf[BufLength+1]; // buffer for inserting strings
static int TextLevel; // number of current text level

TText::TText(PTTextLink pl)
{
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
}

// navigation
int TText::GoFirstLink() // go to first string
{
    while (!Path.empty())
        Path.pop(); // clean stack
    pCurrent = pFirst;
    if (pCurrent == NULL) 
        SetRetCode(TextError);
    else    
        SetRetCode(TextOK);
    
    return RetCode;
}

int TText::GoDownLink() // go to next string by down
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

int TText::GoNextLink() // go to next string by next
{
    /// WRITE  // ready
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

int TText::GoPrevLink() // go to last position in text
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

// access
string TText::GetLine() // reading next string
{
    if(pCurrent == NULL)
        return string("");
    else 
        return string(pCurrent->Str);
}

void TText::SetLine(string s) // replace current string
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength-1] = '\0';
}

// modification
void TText::InsDownLine(string s) // inserting string to down
{
    if(pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", pd, NULL);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength-1] = '\0'; // set, if s > Str
        pCurrent->pDown = pl; // set pointer to new string
        SetRetCode(TextOK);
    }
}

void TText::InsDownSection(string s) // inserting section to down
{
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", NULL, pd);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength-1] = '\0'; // set, if s > Str
        pCurrent->pDown = pl; // set pointer to new string
        SetRetCode(TextOK);
    }
}

void TText::InsNextLine(string s) // insert string in the same level
{
    /// WRITE // ready
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pn = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", pn, NULL);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set, if s > Str
        pCurrent->pNext = pl; // set pointer to new string
        SetRetCode(TextOK);
    }
}

void TText::InsNextSection(string s) // insert section in the same level
{
    /// WRITE // ready
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
    {
        PTTextLink pn = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", NULL, pn);
        strncpy(pl->Str, s.c_str(), TextLineLength);
        pl->Str[TextLineLength - 1] = '\0'; // set, if s > Str
        pCurrent->pNext = pl; // set pointer to new string
        SetRetCode(TextOK);
    }
}

void TText::DelDownLine() // delete string in the down level
{
    SetRetCode(TextOK);
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == NULL)
            pCurrent->pDown = pl2; // only for atom
    }
}

void TText::DelDownSection() // delete section in the down level
{
    SetRetCode(TextOK);
    if(pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}

void TText::DelNextLine() // delete string in the same level
{
    /// WRITE // ready
    SetRetCode(TextOK);
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL)
    {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == NULL)
            pCurrent->pNext = pl2; // only for atom
    }
}

void TText::DelNextSection() // delete section in the same level
{
    /// WRITE // ready
    SetRetCode(TextOK);
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL)
    {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
}

// iterator
int TText::Reset() // set to first record
{
    while (!St.empty())
        St.pop(); // clean stack
    // current string is not being stored in the stack
    // exception - the first string of text, which is at the bottom of stack
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

int TText::IsTextEnded()const
{
    return !St.size();
}

int TText::GoNext() // go to next record
{
    if (!IsTextEnded())
    {
        pCurrent = St.top(); 
        St.pop(); // if after pop() stack is empty, it means that 
        if (pCurrent != pFirst) // first string of text had been already processed
        {
            if(pCurrent->pNext != NULL)
                St.push(pCurrent->pNext);
            if(pCurrent->pDown != NULL)
                St.push(pCurrent->pDown);
        }
    }

    return IsTextEnded();
}

// copying text
PTTextLink TText::GetFirstAtom(PTTextLink pl) // searching for first atom
{
    PTTextLink tmp = pl;
    while (!tmp->IsAtom())
    {
        St.push(tmp);
        tmp = tmp->GetDown();
    }

    return tmp;
}

PTText TText::getCopy() // copying text
{
    PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
    if (pFirst != NULL)
    {
        while (!St.empty())
            St.pop(); // clean stack
        while(1)
        {
            if (pl != NULL) // go to first atom
            {
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
                if (strstr(pl1->Str, "Copy") == NULL) // first stage of making copy
                {   // making copy is pDown to already copied sublevel
                    pl2 = new TTextLink("Copy", pl1, cpl); // pNext to original
                    /// WRITE
                    St.push(pl2);
                    pl = pl1->pNext;
                    cpl = nullptr;
                }
                else // second stage of making copy
                {
                    // WRITE
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

//  printing text
void TText::Print()
{
    TextLevel = 0;
    PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
    if (ptl != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
            cout << " ";
        cout << " " << *ptl << endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}

// reading text from file
void TText::Read(char *pFileName)
{
    ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (TxtFile.is_open())
        pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(ifstream &TxtFile)
{
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while (TxtFile.eof() == 0)
    {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == '}') 
        {
            TextLevel--;
            break;
        }
        else if(StrBuf[0] == '{') //recursion
        {
            TextLevel++;
            ptl->pDown = ReadText(TxtFile);
        }
        else // concatenate next string
        {
            ptl->pNext = new TTextLink(StrBuf, NULL, NULL);
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if (pHead->pDown == NULL) // delete first string, if there is no sublevel
    {
        pHead = pHead->pNext;
        delete ptl;
    }

    return pHead;
}