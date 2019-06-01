// ������ - ������������� ��������� �������������
#ifndef __TTEXT_H
#define __TTEXT_H


#include <iostream>
#include <stack>
#include <cstring>
#include "TTextLink.h"

class TText;
typedef TText * PTText;

class TText /*: public TDataCom */{
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
								// ����� pCurrent � ���� �� ����������
	// ���� � ������ ����������
	std::stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText(std::ifstream &TxtFile); //������ ������ �� �����
public:
	TText(PTTextLink pl = NULL);
	~TText() { pFirst = NULL; }
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
	int Reset(void);              // ���������� �� ������ �������
	int IsTextEnded(void) const;  // ����� ��������?
	int GoNext(void);             // ������� � ��������� ������
   //������ � �������
	void Read(const char * pFileName);  // ���� ������ �� �����
	void Write(char * pFileName); // ����� ������ � ����
   //������
	void Print(void);             // ������ ������

	//void wr(ofstream &txt, PTTextLink ptl);
};

#endif