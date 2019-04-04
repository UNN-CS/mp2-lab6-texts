#ifndef _TTEXT_H_
#define _TTEXT_H_
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include "tdatacom.h"
#include "ttextlink.h"

class TText {
protected:
    PTTextLink pFirst;      // ��������� ����� ������
    PTTextLink pCurrent;      // ��������� ������� ������
    std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
    std::stack< PTTextLink > St;   // ���� ��� ���������
    PTTextLink GetFirstAtom (PTTextLink pl); // ����� ������� �����
    void PrintText (std::ostream& out, PTTextLink ptl); // ������ ������ �� ����� ptl
    PTTextLink ReadText (std::ifstream &TxtFile); //������ ������ �� �����
public:
    TText (PTTextLink pl = nullptr);
    ~TText () {}
    PTText GetCopy();

    int GoFirstLink (); // ������� � ������ ������
    int GoDownLink ();  // ������� � ��������� ������ �� Down
    int GoNextLink ();  // ������� � ��������� ������ �� Next
    int GoPrevLink ();  // ������� � ���������� ������� � ������

    std::string GetLine();   // ������ ������� ������
    void SetLine ( std::string s); // ������ ������� ������

    void InsDownLine (std::string s);    // ������� ������ � ����������
    void InsDownSection (std::string s); // ������� ������� � ����������
    void InsNextLine (std::string s);    // ������� ������ � ��� �� ������
    void InsNextSection (std::string s); // ������� ������� � ��� �� ������
    void DelDownLine ();        // �������� ������ � ���������
    void DelDownSection ();     // �������� ������� � ���������
    void DelNextLine ();        // �������� ������ � ��� �� ������
    void DelNextSection ();     // �������� ������� � ��� �� ������

    int Reset ();              // ���������� �� ������ �������
    int IsTextEnded () const;  // ����� ��������?
    int GoNext ();             // ������� � ��������� ������

    void Read (char *pFileName);  // ���� ������ �� �����
    void Write (char *pFileName); // ����� ������ � ����

    void Print (std::ostream& out);         // ������ ������
};

#endif  // _TTEXT_H_
