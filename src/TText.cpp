#define BufLength 80
#include <conio.h>
#include <iostream>
#include "stdio.h"
#include <string.h>
#include "TText.h"

static char StrBuf[BufLength + 1];
static int TextLevel; 
using namespace std;
TText::TText(PTTextLink pl)
{
	if (pl == NULL) pl = new TTextLink();
	pFirst =pCurrent= pl;
}

//навигация
int TText::GoFirstLink() // переход к первой строке
{
	while (!Path.empty())
	{
		Path.pop();  // очистка стека
	}
	pCurrent = pFirst;
	if (pCurrent == NULL) SetRetCode(TextError);
	else SetRetCode(TextOK);
	return RetCode;
}

int TText::GoDownLink() //переход к следующей строке по Down
{
	SetRetCode(TextError);
	if (pCurrent != NULL)
	{
		if (pCurrent->pDown != NULL)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			SetRetCode(TextOK);
		}
	}
	return RetCode;
}

int TText::GoNextLink() //переход к следующей строке по Next
{
	SetRetCode(TextError);
	if (pCurrent != NULL)
	{
		if (pCurrent->pNext != NULL)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pNext;
			SetRetCode(TextOK);
		}
	}
	return RetCode;
}

int TText::GoPrevLink() // переход к предыдущей позиции в тексте
{
	if (Path.empty()) SetRetCode(TextNoPrev);
	else
	{
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(TextOK);
	}
	return RetCode;
}

// доступ 
string TText::GetLine() //чтение текущей строки 
{
	if (pCurrent != NULL) return string(pCurrent->Str);
	else string("");
}

void TText::SetLine(string s) // замена текущей строки 
{
	if (pCurrent == NULL) SetRetCode(TextError);
	else
	{
		strncpy(pCurrent->Str, s.c_str(),TextLineLength);
	}
	pCurrent->Str[TextLineLength - 1] = '\0';
}

int TText::InsDownLine(string s) // вставка строки в подуровень
{
	if (pCurrent == NULL) SetRetCode(TextError);
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", pd, NULL);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';  // установка если s длиннее str
		pCurrent->pDown = pl;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int TText::InsDownSection(string s)  // вставка раздела в подуровень
{
	if (pCurrent == NULL) SetRetCode(TextError);
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int TText::InsNextLine(string s)  // вставка строки в том же уровне
{
	if (pCurrent == NULL) SetRetCode(TextError);
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", pn, NULL);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int  TText::InsNextSection(string s) // вставка раздела в тот же уровень
{
	if (pCurrent == NULL) SetRetCode(TextError);
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", NULL, pn);
		strncpy(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int TText::DelDownLine() // удаление строки в подуровне
{
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pDown!=NULL)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == NULL) // проверка на то, что pl1 это не раздел, а строка 
		{
			pCurrent->pDown = pl2;
		}
	}
	return RetCode;
}

int  TText::DelDownSection() // удаление раздела в подуровне
{
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pDown != NULL)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
	return RetCode;
}

int  TText::DelNextLine() // удаление строки в том же уровне
{
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pNext != NULL)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == NULL) pCurrent->pNext = pl2; // проверка на атомарность
	}
	return RetCode;
}

int TText::DelNextSection() // удаление раздела в том же уровне
{
	SetRetCode(TextOK);
	if (pCurrent == NULL) SetRetCode(TextError);
	else if (pCurrent->pNext != NULL)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pNext;
	    pCurrent->pNext = pl2; 
	}
	return RetCode;
}

// итератор 
int TText::Reset() // установить на первую запись
{
	while (!St.empty()) St.pop(); // очистка  стека
	// текущая строка в стеке не хранится 
	// исключение - первая строка текста, которая на дне стека
	pCurrent = pFirst;
	if (pCurrent != NULL)
	{
		St.push(pCurrent);
		if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
		if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::GoNext() // переход к следующей записи
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();
		St.pop();
		if (pCurrent != pFirst)
		{
			if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
			if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

//копирование текста
PTTextLink TText::GetFirstAtom(PTTextLink pl) // поиск первого атома
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}
//печать текста
void TText::Print()
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != NULL)
	{
		TextLevel++; PrintText(ptl->GetDown());
		TextLevel--; PrintText(ptl->GetNext());
		for (int i = 0; i < TextLevel; ++i)
			cout << " ";
		cout << " ";
		ptl->Print(cout);
		cout << endl;
	}
}

// чтение текста из файла
void TText::Read(char * pFileName)
{
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (pFileName != NULL ) pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(ifstream& TxtFile)
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
			ptl->pNext = new TTextLink(StrBuf, NULL, NULL);
			ptl = ptl->pNext;
		}
	}
	ptl = pHead;
	if (pHead->pDown == NULL)
	{
		// удаление первой строки, если нет подуровня
		pHead = pHead->pNext;
		delete ptl;
	}
	return pHead;
}

PTText TText::getCopy()
{
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
	if (pFirst != NULL)
	{
		while (!St.empty()) St.pop(); // очистка стека
		while (1)
		{
			if (pl != NULL) // переход к первому атому
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty()) break;
			else
			{
				pl1 = St.top();
				St.pop();
				if (strstr(pl1->Str, "Copy") == NULL) // первый этап 
				{
					pl2 = new TTextLink("Copy", pl1, cpl);
					St.push(pl2);
					pl = pl1->pNext;
					cpl = NULL;
				}
				else
				{
					pl2 = pl1->GetNext();
					strcpy(pl1->Str, pl2->Str);
					pl1->pNext = cpl;
					cpl = pl1;
				}
			}
		}
	}
	return new TText(cpl);
}