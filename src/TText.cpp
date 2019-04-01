#include "TText.h"

#define BufLength 80
static char StrBuf[BufLength + 1]; // буфер для строк

int TText::TextLevel;

TText::TText(PTTextLink pl)
{
	if (pl == NULL) pl = new TTextLink();
	pFirst = pl;
}

// навигация
Data TText::GoFirstLink(void)
{
	while (!Path.empty())
		Path.pop();
	pCurrent = pFirst;
	if (pCurrent == NULL)
		SetRetCode(Data::TextError);
	else
		SetRetCode(Data::TextOk);
	return RetCode;
}


Data TText::GoDownLink(void)
{
	if (pCurrent != NULL && pCurrent->GetDown() != NULL) {
		Path.push(pCurrent);
		pCurrent = pCurrent->GetDown();
		SetRetCode(Data::TextOk);
	}
	else
		SetRetCode(Data::TextError);
	return RetCode;
}

Data TText::GoNextLink(void)
{
	if (pCurrent->GetNext() == NULL)
		SetRetCode(Data::TextNoNext);
	else {
		Path.push(pCurrent);
		pCurrent = pCurrent->GetNext();
		SetRetCode(Data::TextOk);
	}
	return RetCode;
}

Data TText::GoPrevLink(void)
{
	if (Path.empty()) SetRetCode(Data::TextNoPrev);
	else {
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(Data::TextOk);
	}
	return RetCode;
}

// доступ
string TText::GetLine(void)
{
	return string(pCurrent->Str);
}
void TText::SetLine(string s)
{
	strcpy_s(pCurrent->Str, s.c_str());
}

// модификация
void TText::InsDownLine(string s)
{
	if (pCurrent == NULL) SetRetCode(Data::TextError);
	else {
		TStr buf;
		strcpy_s(buf, s.c_str());
		pCurrent->pDown = new TTextLink(buf, pCurrent->pDown, NULL);
	}
}

void TText::InsDownSection(string s)
{
	if (pCurrent == NULL) SetRetCode(Data::TextError);
	else {
		TStr buf;
		strcpy_s(buf, s.c_str());
		pCurrent->pDown = new TTextLink(buf, NULL, pCurrent->pDown);
	}
}


void TText::InsNextLine(string s)
{
	if (pCurrent == NULL) SetRetCode(Data::TextError);
	else {
		TStr buf;
		strcpy_s(buf, s.c_str());
		pCurrent->pNext = new TTextLink(buf, pCurrent->pNext, NULL);
	}
}

void TText::InsNextSection(string s)
{
	if (pCurrent == NULL) SetRetCode(Data::TextError);
	else {
		TStr buf;
		strcpy_s(buf, s.c_str());
		pCurrent->pNext = new TTextLink(buf, NULL, pCurrent->pNext);
	}
}

void TText::DelDownLine(void)
{
	if (pCurrent == NULL)
		SetRetCode(Data::TextError);
	else if (pCurrent->pDown == NULL)
		SetRetCode(Data::TextNoDown);
	else if (pCurrent->pDown->IsAtom())
		pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelDownSection(void)
{
	if (pCurrent == NULL)
		SetRetCode(Data::TextError);
	else if (pCurrent->pDown == NULL)
		SetRetCode(Data::TextNoDown);
	else
		pCurrent->pDown = pCurrent->pDown->pNext;
}

void TText::DelNextLine(void)
{
	if (pCurrent == NULL)
		SetRetCode(Data::TextError);
	else if (pCurrent->pNext == NULL)
		SetRetCode(Data::TextNoNext);
	else if (pCurrent->pNext->IsAtom())
		pCurrent->pNext = pCurrent->pNext->pNext;
}

void TText::DelNextSection(void)
{
	if (pCurrent == NULL)
		SetRetCode(Data::TextError);
	else if (pCurrent->pNext == NULL)
		SetRetCode(Data::TextNoNext);
	else
		pCurrent->pNext = pCurrent->pNext->pNext;
}

// итератор
int TText::Reset(void)
{
	while (!St.empty()) St.pop();
	pCurrent = pFirst;
	if (pCurrent != NULL) {
		St.push(pCurrent);
		if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
		if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded(void) const
{
	return St.empty();
}

int TText::GoNext(void)
{
	if (!IsTextEnded()) {
		pCurrent = St.top();
		St.pop();
		if (pCurrent != pFirst) {
			if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
			if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) // поиск первого атома
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom()) {
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}


PTText TText::GetCopy()
{
	PTTextLink pl1, pl2 = NULL, pl = pFirst, cpl = NULL;

	if (pFirst != NULL) {
		while (!St.empty()) St.pop();
		while (true)
		{
			if (pl != NULL) {									// Переход к первому атому
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else if (St.empty()) break;
			else {
				pl1 = St.top(); St.pop();
				if (strstr(pl1->Str, "Copy") == NULL) {			// первый этап, создание копии pDown на уже скопированный подуровень
					pl2 = new TTextLink("Copy", pl1, cpl);
					St.push(pl2);
					pl = pl1->GetNext();
					cpl = NULL;
				}
				else {											// второй этап
					strcpy_s(pl1->Str, pl1->pNext->Str);
					pl1->pNext = cpl;
					cpl = pl1;
				}
			}
		}
	}

	return new TText(cpl);
}

//работа с файлами
void TText::Read(char * pFileName)  // ввод текста из файла
{
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (TxtFile) pFirst = ReadText(TxtFile);
}

void TText::Write(char * pFileName) // вывод текста в файл
{
	TextLevel = 0;
	ofstream TextFile(pFileName);
	PrintTextFile(pFirst, TextFile);
}

//печать
void TText::Print(void)  // печать текста
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)         // печать текста со звена ptl
{
	if (ptl != NULL) {
		for (int i = 0; i < TextLevel; i++) cout << "  ";
		cout << "  " << ptl->Str << endl;
		TextLevel++; 
		PrintText(ptl->GetDown());
		TextLevel--; 
		PrintText(ptl->GetNext());
	}
}

void TText::PrintTextFile(PTTextLink ptl, ofstream & TxtFile)         // печать текста со звена ptl
{
	if (ptl != NULL) {
		for (int i = 0; i < TextLevel; i++) TxtFile << "  ";
		TxtFile << "  " << ptl->Str << endl;
		TextLevel++;
		PrintTextFile(ptl->GetDown(), TxtFile);
		TextLevel--;
		PrintTextFile(ptl->GetNext(), TxtFile);
	}
}


PTTextLink TText::ReadText(ifstream& TxtFile)
{
	string buf;
	PTTextLink ptl = new TTextLink();
	PTTextLink tmp = ptl;
	while (!TxtFile.eof())
	{
		getline(TxtFile, buf);
		if (buf.front() == '}')
			break;
		else if (buf.front() == '{')
			ptl->pDown = ReadText(TxtFile);
		else
		{
			ptl->pNext = new TTextLink(buf.c_str());
			ptl = ptl->pNext;
		}
	}
	ptl = tmp;
	if (tmp->pDown == nullptr)
	{
		tmp = tmp->pNext;
		delete ptl;
	}
	return tmp;
}