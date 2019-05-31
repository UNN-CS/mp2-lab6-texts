#include "ttext.h"

static int TextLevel = 0;
const int BuffLen = 20;
char StrBuff[BuffLen];

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

void TText::PrintText(PTTextLink pl)
{
	if (pl)
	{
		for (int i = 0; i < TextLevel; i++)
			std::cout << " ";
		std::cout << " " << *pl << std::endl;
		TextLevel++;
		PrintText(pl->GetDown());
		TextLevel--;
		PrintText(pl->GetNext());
	}
}

PTTextLink TText::ReadText(std::ifstream & TxtFile)
{
	PTTextLink pHead, pl;
	pHead = pl = new TTextLink();
	while (!TxtFile.eof())
	{
		TxtFile.getline(StrBuff, BuffLen, '\n');
		if (StrBuff[0] == '}')
		{
			TextLevel--;
			break;
		}
		if (StrBuff[0] == '{')
		{
			TextLevel++;
			pl->pDown = ReadText(TxtFile);
		}
		else
		{
			pl->pNext = new TTextLink(StrBuff, NULL, NULL);
			pl = pl->pNext;
		}
	}
	pl = pHead;
	if (!pHead->pDown)
	{
		pHead = pHead->pNext;
		delete pl;
	}
	return pHead;
}

TText::TText(PTTextLink pl)
{
	if (!pl) pl = new TTextLink();
	pFirst = pCurrent = pl;
}

PTText TText::GetCopy()
{
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
	if (pFirst)
	{
		while (St.size()) St.pop();
		while (1)
		{
			if (pl)
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (!St.size())
			{
				break;
			}
			else
			{
				pl1 = St.top();
				St.pop();
				if (!strstr(pl1->Str, "Copy"))
				{
					pl2 = new TTextLink("Copy", pl1, cpl);
					St.push(pl2);
					pl = pl1->pNext;
					cpl = NULL;
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

int TText::GoFirstLink()
{
	while (Path.size())
		Path.pop();
	pCurrent = pFirst;
	if (!pCurrent) throw - 1;
	return 0;
}

int TText::GoDownLink()
{
	if (pCurrent)
	{
		if (pCurrent->pDown)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
		}
		else throw - 1;
	}
	else throw - 1;
	return 0;
}

int TText::GoNextLink()
{
	if (pCurrent)
	{
		if (pCurrent->pNext)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pNext;
		}
		else throw - 1;
	}
	else throw - 1;
	return 0;
}

int TText::GoPrevLink()
{
	if (Path.empty())
		throw - 1;
	pCurrent = Path.top();
	Path.pop();
	return 0;
}

std::string TText::GetLine()
{
	if (pCurrent)
		return pCurrent->Str;
	return "";
}

void TText::SetLine(std::string s)
{
	if (!pCurrent)
		throw - 1;
	strncpy(pCurrent->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = 0;
}

void TText::InsDownLine(std::string s)
{
	if (!pCurrent) throw - 1;
	PTTextLink pl = new TTextLink("", pCurrent->pDown, NULL);
	strncpy(pl->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = 0;
	pCurrent->pDown = pl;
}

void TText::InsDownSection(std::string s)
{
	if (!pCurrent) throw - 1;
	PTTextLink pl = new TTextLink("", NULL, pCurrent->pDown);
	strncpy(pl->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = 0;
	pCurrent->pDown = pl;
}

void TText::InsNextLine(std::string s)
{
	if (!pCurrent) throw - 1;
	PTTextLink pl = new TTextLink("", pCurrent->pNext, NULL);
	strncpy(pl->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = 0;
	pCurrent->pNext = pl;
}

void TText::InsNextSection(std::string s)
{
	if (!pCurrent) throw - 1;
	PTTextLink pl = new TTextLink("", NULL, pCurrent->pNext);
	strncpy(pl->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = 0;
	pCurrent->pNext = pl;
}

void TText::DelDownLine()
{
	if (!pCurrent) throw - 1;
	if (!pCurrent->pDown) throw - 1;
	pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelDownSection()
{
	if (!pCurrent) throw - 1;
	if (!pCurrent->pDown) throw - 1;
	pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelNextLine()
{
	if (!pCurrent) throw - 1;
	if (!pCurrent->pNext) throw - 1;
	pCurrent->pNext = pCurrent->pNext->pNext;
}

void TText::DelNextSection()
{
	if (!pCurrent) throw - 1;
	if (!pCurrent->pNext) throw - 1;
	pCurrent->pNext = pCurrent->pNext->pNext;
}

int TText::Reset()
{
	while (St.size())
		St.pop();
	pCurrent = pFirst;
	if (pCurrent)
	{
		St.push(pCurrent);
		if (pCurrent->pNext)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded() const
{
	return St.empty();
}

int TText::GoNext()
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();
		St.pop();
		if (pCurrent != pFirst)
		{
			if (pCurrent->pNext)
				St.push(pCurrent->pNext);
			if (pCurrent->pDown)
				St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

void TText::Read(char * pFileName)
{
	std::ifstream TxtFile;
	TxtFile.open(pFileName);
	TextLevel = 0;
	if (TxtFile)
		pFirst = ReadText(TxtFile);
}

void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
}