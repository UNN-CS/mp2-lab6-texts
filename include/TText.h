#ifndef __TTTEXT_H__
#define __TTTEXT_H__

#include <iostream>
#include <string.h>
#include <stack>

#include "tdatacom.h"
#include "TTextLink.h"

#define TextError -132
#define TextNoPrev -133
#define TextOK 0

class TText;
typedef TText *PTText;

class TText : public TDataCom {
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
	std::stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom (PTTextLink pl); // ����� ������� �����
	void PrintText (PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText (std::ifstream &TxtFile); //������ ������ �� �����
public:
	TText (PTTextLink pl = NULL);
	~TText () {pFirst = NULL;}
	PTText getCopy();
// ���������
	int GoFirstLink (void); // ������� � ������ ������
	int GoDownLink (void);  // ������� � ��������� ������ �� Down
	int GoNextLink (void);  // ������� � ��������� ������ �� Next
	int GoPrevLink (void);  // ������� � ���������� ������� � ������
// ������
	std::string GetLine(void);   // ������ ������� ������
	void SetLine ( std::string s); // ������ ������� ������ 
// �����������
	int InsDownLine (std::string s);    // ������� ������ � ����������
	int InsDownSection (std::string s); // ������� ������� � ����������
	int InsNextLine (std::string s);    // ������� ������ � ��� �� ������
	int InsNextSection (std::string s); // ������� ������� � ��� �� ������
	int DelDownLine (void);        // �������� ������ � ���������
	int DelDownSection (void);     // �������� ������� � ���������
	int DelNextLine (void);        // �������� ������ � ��� �� ������
	int DelNextSection (void);     // �������� ������� � ��� �� ������
// ��������
	int Reset (void);              // ���������� �� ������ �������
	int IsTextEnded (void) const;  // ����� ��������?
	int GoNext (void);             // ������� � ��������� ������
//������ � �������
	void Read (char * pFileName);  // ������ ������ �� �����
	void Write (char * pFileName); // ����� ������ � ����
//������
	void Print (void);             // ������ ������
};

#endif