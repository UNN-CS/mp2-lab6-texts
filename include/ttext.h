#ifndef __TEXT_H__
#define __TEXT_H__

#include <stack>
#include <string>
#include <fstream>
#include <iostream>

#include "tdatacom.h"
#include "ttextlink.h"

class TText;
typedef TText* PTText;

class TText : public TDataCom {
protected:
    PTTextLink pFirst;      // ��������� ����� ������
    PTTextLink pCurrent;      // ��������� ������� ������
    std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
    std::stack< PTTextLink > St;   // ���� ��� ���������
    PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
    void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
    PTTextLink ReadText(std::ifstream& TxtFile); //������ ������ �� �����
public:
    TText(PTTextLink pl = nullptr);
    ~TText() { pFirst = nullptr; }
    PTText GetCopy();
    // ���������
    void GoFirstLink(void); // ������� � ������ ������
    void GoDownLink(void);  // ������� � ��������� ������ �� Down
    void GoNextLink(void);  // ������� � ��������� ������ �� Next
    void GoPrevLink(void);  // ������� � ���������� ������� � ������
   // ������
    std::string GetLine(void);   // ������ ������� ������
    void SetLine(std::string s); // ������ ������� ������ 
   // �����������
    void InsDownLine(std::string s);    // ������� ������ � ����������
    void InsDownSection(std::string s); // ������� ������� � ����������
    void InsNextLine(std::string s);    // ������� ������ � ��� �� ������
    void InsNextSection(std::string s); // ������� ������� � ��� �� ������
    void DelDownLine(void);        // �������� ������ � ���������
    void DelDownSection(void);     // �������� ������� � ���������
    void DelNextLine(void);        // �������� ������ � ��� �� ������
    void DelNextSection(void);     // �������� ������� � ��� �� ������
   // ��������
    int Reset(void);              // ���������� �� ������ ������
    int IsTextEnded(void) const;  // ����� ��������?
    int GoNext(void);             // ������� � ��������� ������
   //������ � �������
    void Read(char* pFileName);  // ���� ������ �� �����
    void Write(char* pFileName); // ����� ������ � ����
   //������
    void Print(void);             // ������ ������
};

#endif
