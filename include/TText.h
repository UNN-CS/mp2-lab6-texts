#pragma once

#include "tdatacom.h"
#include "TTextLink.h"
#include <stack>
#include <string>
#include <fstream>

class TText;
typedef TText *PTText;

class TText : public TDataCom {
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	stack< PTTextLink > Path; // ���� ���������� �������� �� ������
	stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	void PrintTextFile(PTTextLink ptl, ofstream & TxtFile);		// ������ ������ � ����
	PTTextLink ReadText(ifstream &TxtFile); //������ ������ �� �����
	static int TextLevel;
public:
	TText(PTTextLink pl = NULL);
	~TText() { pFirst = NULL; }
	PTText GetCopy();
	// ���������
	Data GoFirstLink(void); // ������� � ������ ������
	Data GoDownLink(void);  // ������� � ��������� ������ �� Down
	Data GoNextLink(void);  // ������� � ��������� ������ �� Next
	Data GoPrevLink(void);  // ������� � ���������� ������� � ������
	// ������
	string GetLine(void);   // ������ ������� ������
	void SetLine(string s); // ������ ������� ������ 
	// �����������
	void InsDownLine(string s);    // ������� ������ � ����������
	void InsDownSection(string s); // ������� ������� � ����������
	void InsNextLine(string s);    // ������� ������ � ��� �� ������
	void InsNextSection(string s); // ������� ������� � ��� �� ������
	void DelDownLine(void);        // �������� ������ � ���������
	void DelDownSection(void);     // �������� ������� � ���������
	void DelNextLine(void);        // �������� ������ � ��� �� ������
	void DelNextSection(void);     // �������� ������� � ��� �� ������
	// ��������
	int Reset(void);              // ���������� �� ������ �������
	int IsTextEnded(void) const;  // ����� ��������?
	int GoNext(void);             // ������� � ��������� ������
	//������ � �������
	void Read(char * pFileName);  // ���� ������ �� �����
	void Write(char * pFileName); // ����� ������ � ����
	//������
	void Print(void);             // ������ ������
};