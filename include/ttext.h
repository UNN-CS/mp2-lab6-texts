#ifndef __TEXT_H
#define __TEXT_H

#include <stack>
#include <fstream>
#include <string>
#include "tdatacom.h"
#include "textlink.h"

class TText;
typedef TText *PTText;

class TText :public TDataCom
{
protected:
    PTTextLink pFirst;
    PTTextLink pCurrent;
    std::stack<PTTextLink> Path; 
    std::stack<PTTextLink> St;
    PTTextLink GetFirstAtom(PTTextLink pl);
    void PrintText(PTTextLink ptl);
    PTTextLink ReadText(std::ifstream &TxtFile);

public:
    TText(PTTextLink pl = nullptr);
    ~TText() { pFirst = nullptr; }
    PTText GetCopy();

    void GoFirstLink();
    void GoDownLink();
    void GoNextLink();
    void GoPrevLink();

    std::string GetLine();
    void SetLine(std::string s);

    void InsDownLine(std::string s);
    void InsDownSection(std::string s);
    void InsNextLine(std::string s);
    void InsNextSection(std::string s);
    void DelDownLine();
    void DelDownSection();
    void DelNextLine();
    void DelNextSection();

    int Reset(); 
    int IsTextEnded()const; 
    int GoNext(); 

    void Read(const char *pFileName); 
    void Write(char *pFileName);

    void Print();
};
#endif