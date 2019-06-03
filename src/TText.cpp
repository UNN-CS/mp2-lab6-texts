#include "TText.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static char StrBuf[81];
static int TextLevel;

TText::TText(PTTextLink pl)
{
	if (pl == nullptr)
		pl = new TTextLink();
	pFirst = pl;
	pCurrent = nullptr;
}
int TText::GoFirstLink(void)
{
	SetRetCode(TextError);
	while (!Path.empty())
		Path.pop();
	pCurrent = pFirst;
	if (pCurrent != nullptr)
		SetRetCode(TextOk);
	return RetCode;
}
int TText::GoDownLink(void)
{
	SetRetCode(TextError);
	if (pCurrent != nullptr && pCurrent->pDown != nullptr)
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pDown;
		SetRetCode(TextOk);
	}
	return RetCode;
}
int TText::GoNextLink(void)
{
	SetRetCode(TextError);
	if (pCurrent != nullptr  && pCurrent->pNext != nullptr)
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pNext;
		SetRetCode(TextOk);
	}
	return RetCode;
}
int TText::GoPrevLink(void)
{
	if (Path.empty())
		SetRetCode(TextNoPrev);
	else
	{
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(TextOk);
	}
	return RetCode;
}
string TText::GetLine(void)
{
	if (pCurrent == nullptr)
		return string("");
	else
		return string(pCurrent->Str);
}
void TText::SetLine(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (s.length() > TextLineLength)
		SetRetCode(TooLongString);
	else
	{
		strncpy(pCurrent->Str, s.c_str(), TextLineLength);
		pCurrent->Str[TextLineLength - 1] = '\0';
	}
}
void TText::InsDownLine(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (s.length() > TextLineLength)
		SetRetCode(TooLongString);
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", pd, nullptr);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
		SetRetCode(TextOk);
	}
}
void TText::InsDownSection(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (s.length() > TextLineLength)
		SetRetCode(TooLongString);
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", nullptr, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
		SetRetCode(TextOk);
	}
}
void TText::InsNextLine(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (s.length() > TextLineLength)
		SetRetCode(TooLongString);
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", pn, nullptr);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOk);
	}
}
void TText::InsNextSection(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (s.length() > TextLineLength)
		SetRetCode(TooLongString);
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", nullptr, pn);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOk);
	}
}
void TText::DelDownLine(void)
{
	SetRetCode(TextOk);
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else  if (pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == nullptr)
			pCurrent->pDown = pl2;
	}
}
void TText::DelDownSection(void)
{
	SetRetCode(TextOk);
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}
void TText::DelNextLine(void)
{
	SetRetCode(TextOk);
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (pCurrent->pNext != nullptr)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == nullptr)
			pCurrent->pNext = pl2;
	}
}
void TText::DelNextSection(void)
{
	SetRetCode(TextOk);
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else if (pCurrent->pNext != nullptr)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pNext = pl2;
	}

}
int TText::Reset(void)
{
	while (!St.empty())
		St.pop();
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
int TText::GoNext(void)
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();
		St.pop();
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
PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}
PTText TText::GetCopy()
{
	PTTextLink pl1, pl2, pl = pFirst, cpl = nullptr;

	if (pFirst != nullptr)
	{
		while (!St.empty())
			St.pop();
		while (1)

			if (pl != nullptr)
			{
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty())
				break;
			else
			{
				pl1 = St.top();
				St.pop();
				if (strstr(pl1->Str, "Copy") == nullptr)
				{
					pl2 = new TTextLink("Copy", pl1, cpl);
					St.push(pl2);
					pl = pl1->GetNext();
					cpl = nullptr;
				}
				else
				{
					strncpy(pl1->Str, pl1->pNext->Str, TextLineLength);
					pl1->pNext = cpl;
					cpl = pl1;
				}
			}
	}
	return new TText(cpl);
}
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
			cout << "   ";
		cout << " " << ptl->Str << endl;
		TextLevel++;
		PrintText(ptl->GetDown());
		TextLevel--;
		PrintText(ptl->GetNext());
	}
}
void TText::Read(char *pFileName)
{
	ifstream TxtFile;
	TxtFile.open(pFileName, ifstream::in);
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
		else if (StrBuf[0] == '{')
		{
			TextLevel++;
			ptl->pDown = ReadText(TxtFile);
		}
		else
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
void TText::Write(char *pFileName)
{
	ofstream TxtFile;
	TxtFile.open(pFileName);
	TextLevel = 0;
	PTTextLink pl = pFirst;
	if (pl != nullptr)
	{
		if (TxtFile.is_open())
		{
			TxtFile << "{" << endl;
			while (!St.empty())
				St.pop();
			while (1)
			{
				if (pl != nullptr)
				{
					TxtFile << pl->Str << endl;
					St.push(pl);
					pl = pl->GetDown();
					if (pl != nullptr)
						TxtFile << "{" << endl;
				}
				else if (St.empty())
					break;
				else
				{
					pl = St.top();
					St.pop();
					pl = pl->GetNext();
					if (pl == nullptr)
						TxtFile << "}" << endl;
				}
			}
		}
	}
}