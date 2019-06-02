#include "TText.h"

const int BufLength = 80;
static int TextLevel = 0;
static char StrBuf[BufLength + 1];


TText::TText(PTTextLink pl)
{
	if (pl == nullptr)
		pl = new TTextLink();

	pCurrent = pFirst = pl;
}

int TText::GoFirstLink(void)
{
	while (!Path.empty()) Path.pop();

	pCurrent = pFirst;

	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
		SetRetCode(TextOK);

	return RetCode;
}

int TText::GoDownLink(void)
{
	SetRetCode(TextError);

	if (pCurrent != nullptr)
	{
		if (pCurrent->pDown != nullptr)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			SetRetCode(TextOK);
		}
		else
			throw - 1;
	}

	return RetCode;
}

int TText::GoNextLink(void)
{
	SetRetCode(TextError);

	if (pCurrent != nullptr)
	{
		if (pCurrent->pNext != nullptr)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pNext;
			SetRetCode(TextOK);
		}
		else
			throw - 1;
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

		SetRetCode(TextOK);
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
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = tmp;
	}
}

void TText::DelDownLine(void)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
	{
		if (pCurrent->pDown != nullptr)
		{
			PTTextLink pl1 = pCurrent->pDown;
			PTTextLink pl2 = pl1->pNext;
			if (pl1->pDown == nullptr)
				pCurrent->pDown = pl2;
		}
	}
}

void TText::InsDownSection(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = tmp;
		SetRetCode(TextOK);
	}
}

void TText::DelDownSection(void)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
	{
		if (pCurrent->pDown != nullptr)
		{
			pCurrent->pDown = pCurrent->pDown->pNext;
		}
		else
		{
			SetRetCode(TextNoDown);
		}
	}
}

void TText::InsNextLine(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, pCurrent->pNext);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = tmp;
	}
}

void TText::DelNextLine(void)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
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
			SetRetCode(TextNoNext);
		}
	}
}

void TText::InsNextSection(string s)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, nullptr, pCurrent->pNext);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = tmp;
	}
}

void TText::DelNextSection(void)
{
	if (pCurrent == nullptr)
		SetRetCode(TextError);
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
			SetRetCode(TextNoNext);
		}
	}
}

int TText::IsTextEnded(void) const
{
	return !St.size();
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
		tmp = tmp->pDown;
	}
	return tmp;
}

PTText TText::GetCopy()
{
	PTTextLink pl, pl1, pl2, cpl;
	pl = pFirst;
	cpl = nullptr;
	char s[5] = "Copy";

	if (pFirst != nullptr)
	{
		while (!St.empty())
			St.pop();

		while (true)
		{
			if (pl != nullptr)
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

					if (strstr(pl1->Str, "Copy") == nullptr)
					{
						pl2 = new TTextLink(s, pl1, cpl);
						St.push(pl2);
						pl = pl1->pNext;
						cpl = nullptr;
					}
					else
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

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != nullptr)
	{
		for (int i = 0; i < TextLevel; i++)
			cout << " ";
		cout << *ptl << endl;
		TextLevel++;
		PrintText(ptl->GetDown());
		TextLevel--;
		PrintText(ptl->GetNext());
	}
}

void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
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

void TText::Read(char * pFileName)
{
	ifstream TxtFile;
	TxtFile.open(pFileName);
	TextLevel = 0;
	if (TxtFile)
		pFirst = ReadText(TxtFile);
}

void TText::wr(ofstream &txt, PTTextLink ptl)
{
	if (ptl != nullptr)
	{
		for (int i = 0; i < TextLevel; i++)
			txt << " ";
		txt << *ptl << endl;
		TextLevel++;
		wr(txt, ptl->GetDown());
		TextLevel--;
		wr(txt, ptl->GetNext());
	}
}

void TText::Write(char *pFileName)
{
	ofstream TxtFile;
	TxtFile.open(pFileName);
	TextLevel = 0;
	wr(TxtFile, pFirst);
};