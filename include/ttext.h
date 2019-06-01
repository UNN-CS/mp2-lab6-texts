#ifndef __T_TEXT_H__
#define __T_TEXT_H__


#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include "ttextlink.h"

#define TextNoMem  -101  
#define NoPrev   -102

class TText;
typedef TText * PTText;

class TText {
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
	std::stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText(std::ifstream &TxtFile); //������ ������ �� �����
public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }
	PTText GetCopy();
	// ���������
	void GoFirstLink(); // ������� � ������ ������
	void GoDownLink();  // ������� � ��������� ������ �� Down
	void GoNextLink();  // ������� � ��������� ������ �� Next
	void GoPrevLink();  // ������� � ���������� ������� � ������
						// ������
	std::string GetLine();   // ������ ������� ������
	void SetLine(std::string s); // ������ ������� ������
								 // �����������
	void InsDownLine(std::string s);    // ������� ������ � ����������
	void InsDownSection(std::string s); // ������� ������� � ����������
	void InsNextLine(std::string s);    // ������� ������ � ��� �� ������
	void InsNextSection(std::string s); // ������� ������� � ��� �� ������
	void DelDownLine();        // �������� ������ � ���������
	void DelDownSection();     // �������� ������� � ���������
	void DelNextLine();        // �������� ������ � ��� �� ������
	void DelNextSection();     // �������� ������� � ��� �� ������
							   // ��������
	int Reset();              // ���������� �� ������ �������
	int IsTextEnded() const;  // ����� ��������?
	int GoNext();             // ������� � ��������� ������
							  //������ � �������
	void Read(const char * pFileName);  // ���� ������ �� �����
	void Write(char * pFileName); // ����� ������ � ����
								  //������
	void Print();             // ������ ������
};

#endif // __T_TEXT_H__