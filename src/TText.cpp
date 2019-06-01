// ������ - ������������ ��������� �������������

#define BufLength 80
#include "TText.h"
#include "TTextLink.h"
#include <fstream>
//#include <conio.h>

static char StrBuf[BufLength + 1]; //����� ��� ����� �����
static int TextLevel;              //����� �������� ������ ������

TText::TText(PTTextLink pl)
{
	if (pl == nullptr) pl = new TTextLink();
	pFirst = pl;
}
//���������
void TText::GoFirstLink(void) //������� � ������ ������
{
	while (!Path.empty()) Path.pop(); //������� �����
	pCurrent = pFirst;
	if (pCurrent == nullptr) throw TextError;//SetRetCode(TextError);
	/*else SetRetCode(TextOK);
	return RetCode;*/
}

void TText::GoDownLink(void) // ������� � ��������� ������ �� Down
{
	if (pCurrent != nullptr)
	{
		if (pCurrent->pDown != nullptr)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			//SetRetCode(TextOK);
		}
		else
			throw TextError;
	}
	else throw TextError;

}

void TText::GoNextLink(void) // ������� � ��������� ������ ��  Next
{
	//SetRetCode(TextError);
	if (pCurrent != nullptr)
	{
		if (pCurrent->pNext != nullptr)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pNext;
			//SetRetCode(TextOK);
		}
		else
			throw TextError;
	}
	else throw TextError;

	//return RetCode;
}

void TText::GoPrevLink(void) // ������� � ���������� ������� � ������
{
	if (Path.empty()) throw TextNoPrev;//SetRetCode(TextNoPrev);
	else
	{
		pCurrent = Path.top();
		Path.pop();
		//SetRetCode(TextOK);
	}
	//return RetCode;
}

// ������
std::string TText::GetLine(void) // ������ ������� ������
{
	if (pCurrent == nullptr) return std::string("");
	else return std::string(pCurrent->Str);
}

void TText::SetLine(std::string s) //������ ������� ������
{
	if (pCurrent == nullptr) {
		throw TextError;//SetRetCode(TextError); 
	}
	else
	{
		strncpy(pCurrent->Str, s.c_str(), TextLineLength);
		pCurrent->Str[TextLineLength - 1] = '\0';
	}
}

// �����������
void TText::InsDownLine(std::string s) //������� ������ � ����������
{
	if (pCurrent == nullptr) throw TextError;//SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0'; // ���������, ���� s ������� Str
		pCurrent->pDown = tmp;               // ��������� ��������� �� ����� ������
	}
}



void TText::InsDownSection(std::string s) //������� ������� � ����������
{
	if (pCurrent == nullptr)
		throw TextError;//SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = tmp;       // ��������� ��������� �� ����� ������
		//SetRetCode(TextOK);
	}
}

void TText::InsNextLine(std::string s) //������� ������ �  ��� �� ������

{
	if (pCurrent == nullptr)
		throw TextError;//SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, pCurrent->pNext);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = tmp;
	}
}

void TText::InsNextSection(std::string s) // ������� ������� � ��� �� ������

{
	if (pCurrent == nullptr)
		throw TextError; //SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, nullptr, pCurrent->pNext);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = tmp;
	}
}

void TText::DelDownLine(void) // �������� ������ � ���������
{
	if (pCurrent == nullptr)
		throw TextError; //SetRetCode(TextError);
	else
	{
		if (pCurrent->pDown != nullptr)
		{
			PTTextLink pl1 = pCurrent->pDown;
			PTTextLink pl2 = pl1->pNext;
			if (pl1->pDown == nullptr)
				pCurrent->pDown = pl2; // ������ ��� �����
		}
	}
}

void TText::DelDownSection(void) // �������� ������� � ���������
{
	//SetRetCode(TextOK);
	if (pCurrent == nullptr) throw TextError; //SetRetCode(TextError);
	else if (pCurrent->pDown != nullptr) {
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine(void) // �������� ������ � ��� �� ������
{
	if (pCurrent == nullptr)
		throw TextError;//SetRetCode(TextError);
	else
	{
		if (pCurrent->pNext != nullptr)
		{
			PTTextLink pl1 = pCurrent->pNext;
			PTTextLink pl2 = pl1->pNext;

			if (pl1->pDown == nullptr)
				pCurrent->pNext = pl2;
		}
		else
		{
			//throw TextNoNext; //SetRetCode(TextNoNext);
		}
	}
}

void TText::DelNextSection(void) //�������� ������� � ��� �� ������
{
	if (pCurrent == nullptr)
		throw TextError; //SetRetCode(TextError);
	else
	{
		if (pCurrent->pNext != nullptr)
		{
			PTTextLink pl1 = pCurrent->pNext;
			PTTextLink pl2 = pl1->pNext;
			pCurrent->pNext = pl2;
		}
		else
		{
			//throw TextNoNext; SetRetCode(TextNoNext);
		}
	}
}

// ��������
int TText::Reset(void) //���������� �� ������ ������
{
	while (!St.empty()) St.pop(); //������� �����
	//������� ������  ����� �� ��������
	//���������� - ������ ������ ������, ������� �� ��� �����
	pCurrent = pFirst;
	if (pCurrent != nullptr)
	{
		St.push(pCurrent);
		if (pCurrent->pNext != nullptr)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown != nullptr)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded(void) const  //������� ���������?
{
	return !St.size();
}

int TText::GoNext(void) // ������� � ��������� ������
{
	if (!IsTextEnded())
	{
		pCurrent = St.top(); St.pop(); // ���� ����� ������� ���� ����, ������ ������ ������ ��� ���� ����������

		if (pCurrent != pFirst)
		{
			if (pCurrent->pNext != nullptr)
				St.push(pCurrent->pNext);
			if (pCurrent->pDown != nullptr)
				St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) //����� ������� �����
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->pDown;
	}
	return tmp;
}

PTText TText::GetCopy() // ����������� ������
{
	PTTextLink pl=pFirst, pl1, pl2, cpl = nullptr;

	if (pFirst != nullptr)
	{
		while (!St.empty()) St.pop(); //������� �����

		while (true)
		{
			if (pl != nullptr) // ������� � ������� �����
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->pDown;
			}
			else
				if (St.empty()) break;
				else
				{
					pl1 = St.top();
					St.pop();

					if (strstr(pl1->Str, "Copy") == nullptr) // ������ ���� �������� �����
					{//�������� ����� - pDown �� ��� ������������� ����������
						pl2 = new TTextLink ("Copy", pl1, cpl); //pNext �� ��������
						St.push(pl2);
						pl = pl1->pNext;
						cpl = nullptr;
					}
					else // ������ ���� �������� �����
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

//������ ������
void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != nullptr)
	{
		for (int i = 0; i < TextLevel; i++)
			std::cout << " ";
		//cout << *ptl << endl;
		ptl->Print(std::cout);
		std::cout << std::endl;
		TextLevel++;
		PrintText(ptl->GetDown());
		TextLevel--;
		PrintText(ptl->GetNext());
	}
}

//������ ������ �� �����
void TText::Read(const char * pFileName)
{
	std::ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (!TxtFile.is_open())
		throw TextError;
	pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(std::ifstream &TxtFile)
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
		else if (StrBuf[0] == '{')// ��������
		{
			TextLevel++;
			ptl->pDown = ReadText(TxtFile);
		}
		else //������������� ��������� ������
		{
			ptl->pNext = new TTextLink(StrBuf, nullptr, nullptr);
			ptl = ptl->pNext;
		}
	}
	ptl = pHead;
	if (pHead->pDown == nullptr)
	{
		pHead = pHead->pNext;
		delete ptl;
	}
	return pHead;
}



