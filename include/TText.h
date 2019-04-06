#ifndef __TTEXT_H
#define __TTEXT_H

#include <stack>
#include <fstream>
#include <string>
#include "tdatacom.h"

#include "TTextLink.h"
using namespace std;
class TText : public TDataCom {
protected:
	PTTextLink pFirst;      // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	stack< PTTextLink > Path; // ���� ���������� �������� �� ������
	stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText(ifstream &TxtFile); //������ ������ �� �����
public:
	TText(PTTextLink pl = NULL);
	~TText() { pFirst = NULL; }
	PTText getCopy();
	// ���������
	int GoFirstLink(void); // ������� � ������ ������
	int GoDownLink(void);  // ������� � ��������� ������ �� Down
	int GoNextLink(void);  // ������� � ��������� ������ �� Next
	int GoPrevLink(void);  // ������� � ���������� ������� � ������
	 // ������
	string GetLine(void);   // ������ ������� ������
	void SetLine(string s); // ������ ������� ������ 
	// �����������
	int InsDownLine(string s);    // ������� ������ � ����������
	int InsDownSection(string s); // ������� ������� � ����������
	int InsNextLine(string s);    // ������� ������ � ��� �� ������
	int InsNextSection(string s); // ������� ������� � ��� �� ������
	int DelDownLine(void);        // �������� ������ � ���������
	int DelDownSection(void);     // �������� ������� � ���������
	int DelNextLine(void);        // �������� ������ � ��� �� ������
	int DelNextSection(void);     // �������� ������� � ��� �� ������
   // ��������
	int Reset(void);              // ���������� �� ������ �������
	int IsTextEnded(void) const { return !St.size(); };  // ����� ��������?
	int GoNext(void);             // ������� � ��������� ������
	//������ � �������
	void Read(char * pFileName);  // ���� ������ �� �����
	void Write(char * pFileName); // ����� ������ � ����
	//������
	void Print();             // ������ ������
};
#endif