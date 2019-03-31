#define BufLength 80
#include <conio.h>
#include "ttext.h"

using namespace std;

static char StrBuf[BufLength + 1];
static int TextLevel;

TText::TText(PTTextLink pl) 
{
	if (pl == nullptr) 
		pl = new TTextLink();
	pFirst = pl;
}

// навигация

void TText::GoFirstLink()
{
	while (!Path.empty())
		Path.pop(); //очистка стека
	pCurrent = pFirst;
	if (pCurrent == nullptr)
		throw "Text error";
}

void TText::GoDownLink()
{
	if ((pCurrent != nullptr) && (pCurrent->pDown != nullptr))
	{
		Path.push(pCurrent);
		pCurrent = pDown;
	}
	else
		throw "Text error";
}

void TText::GoNextLink()
{
	if ((pCurrent != nullptr) && (pCurrent->pNext != nullptr))
	{
		//здесь должен быть какой-то код....
		//
		//
		//
	}
	else
		throw "text error";
}

void TText::GoPrevLink()
{
	if (Path.empty())
		throw "text no prev";
	else
	{
		pCurrent = Path.top();
		Path.pop();
	}
}

//доступ
string TText::GetLine()
{
	if (pCurrent = nullptr)
		return string("");
	else 
		return string(pCurrent->Str);
}

void TText::SetLine(string s)
{
	if (pCurrent == nullptr)
		throw "text error";
	else
		strncpy(pCurrent->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = '\0';
}

// модификация
void TText::InsDownLine(string s)
{
	if (pCurrent == nullptr)
		throw "text error";
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", pd, nullptr);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsDownSection(string s)
{
	if (pCurrent = nullptr)
		throw "text error";
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", nullptr, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsNextLine(string s)
{
	//тут должен быть код...
	//
	//
	//
}

void TText::InsNextSection(string s)
{
	//тут должен быть код...
	//
	//
	//
}

void TText::DelDownLine()
{
	if (pCurrent = nullptr)
		throw "text error";
	else if(pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == nullptr)
			pCurrent->pDown = pl2;
	}
}

void TText::DelDownSection()
{
	if (pCurrent == nullptr)
		throw "text error";
	else if (pCurrent->pDown != nullptr)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine() 
{
	//тут должен быть код...
	//
	//
	//
}

void TText::DelNextSection
{
	//тут должен быть код...
	//
	//
	//
}

int TText::Reset()
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

int TText::IsTextEnded()const
{
	return !St.size();
}

int TText::GoNext()
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();
		St.pop();
		if (pCurrent->Next != nullptr)
			St.push(pCurrent->pNext);
		if (pCurrent->Down != nullptr)
			St.push(pCurrent->pDown);
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
		{
			if (pl != nullptr)
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty())
				break;
			else
			{
				pl1 = St.top(); St.pop();
				if (strstr(pl1->Str, "Copy") == nullptr)
				{
					pl2 = new TTextLink("Copy", pl1, cpl);
					//тут должен быть код...
					//
					//
					//
				}
				else 
				{
					//тут должен быть код...
					//
					//
					//
				}
			}
		}
	}
	return new TText(cpl);
}

// печать текста
void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink pt1)
{
	if (ptl != nullptr)
	{
		for (int i = 0; i < TextLevel; i++)
			cout << "  ";
		cout << " " << *ptl << endl;
		++TextLevel; PrintText(ptl->GetDown());
		--TextLevel; Printtext(ptl->GetNext());
	}
}

//чтение текста из файла
void TText::Read(char *pFileName)
{
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (TxtFile != nullptr)
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
			--TextLevel; 
			break;
		}
		else if (StrBuf[0] == '{')
		{
			++TextLevel;
			ptl->Down = ReadText(TxtFile);
		}
		else
		{
			ptl->Next = new TTextLink(StrBuf, nullptr, nullptr);
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
