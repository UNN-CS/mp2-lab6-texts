// Тексты - иерархическа структура представления

#define BufLength 80
#include "TText.h"
#include "TTextLink.h"
#include <fstream>
//#include <conio.h>

static char StrBuf[BufLength + 1]; //буфер для ввода строк
static int TextLevel;              //номер текущего уровня текста

TText::TText(PTTextLink pl)
{
	if (pl == nullptr) pl = new TTextLink();
	pFirst = pl;
}
//навигация
void TText::GoFirstLink(void) //переход к первой строке
{
	while (!Path.empty()) Path.pop(); //очистка стека
	pCurrent = pFirst;
	if (pCurrent == nullptr) throw TextError;//SetRetCode(TextError);
	/*else SetRetCode(TextOK);
	return RetCode;*/
}

void TText::GoDownLink(void) // переход к следующей строке по Down
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

void TText::GoNextLink(void) // переход к следующей строке по  Next
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

void TText::GoPrevLink(void) // переход к предыдущей позиции в тексте
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

// доступ
std::string TText::GetLine(void) // чтение текущей строки
{
	if (pCurrent == nullptr) return std::string("");
	else return std::string(pCurrent->Str);
}

void TText::SetLine(std::string s) //замена текущей строки
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

// модификация
void TText::InsDownLine(std::string s) //вставка строки в подуровень
{
	if (pCurrent == nullptr) throw TextError;//SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0'; // установка, если s длиннее Str
		pCurrent->pDown = tmp;               // установка указателя на новую строку
	}
}



void TText::InsDownSection(std::string s) //вставка раздела в подуровень
{
	if (pCurrent == nullptr)
		throw TextError;//SetRetCode(TextError);
	else
	{
		PTTextLink tmp = new TTextLink(nullptr, nullptr, pCurrent->pDown);
		strncpy(tmp->Str, s.c_str(), TextLineLength);
		tmp->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = tmp;       // установка указателя на новую строку
		//SetRetCode(TextOK);
	}
}

void TText::InsNextLine(std::string s) //вставка строки в  том же уровне

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

void TText::InsNextSection(std::string s) // вставка раздела в том же уровне

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

void TText::DelDownLine(void) // удаление строки в подуровне
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
				pCurrent->pDown = pl2; // только для атома
		}
	}
}

void TText::DelDownSection(void) // удаление раздела в подуровне
{
	//SetRetCode(TextOK);
	if (pCurrent == nullptr) throw TextError; //SetRetCode(TextError);
	else if (pCurrent->pDown != nullptr) {
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine(void) // удаление строки в том же уровне
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

void TText::DelNextSection(void) //удаление раздела в том же уровне
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

// итератор
int TText::Reset(void) //установить на первую запись
{
	while (!St.empty()) St.pop(); //очистка стека
	//текущая строка  стеке не хранится
	//исключение - первая строка текста, которая на дне стека
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

int TText::IsTextEnded(void) const  //таблица завершена?
{
	return !St.size();
}

int TText::GoNext(void) // переход к следующей записи
{
	if (!IsTextEnded())
	{
		pCurrent = St.top(); St.pop(); // если после выборки стек пуст, значит первая строка уже была обработана

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

PTTextLink TText::GetFirstAtom(PTTextLink pl) //поиск первого атома
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->pDown;
	}
	return tmp;
}

PTText TText::GetCopy() // копирование текста
{
	PTTextLink pl=pFirst, pl1, pl2, cpl = nullptr;

	if (pFirst != nullptr)
	{
		while (!St.empty()) St.pop(); //очистка стека

		while (true)
		{
			if (pl != nullptr) // переход к первому атому
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

					if (strstr(pl1->Str, "Copy") == nullptr) // первый этап создания копии
					{//создание копии - pDown на уже скопированный подуровень
						pl2 = new TTextLink ("Copy", pl1, cpl); //pNext на оригинал
						St.push(pl2);
						pl = pl1->pNext;
						cpl = nullptr;
					}
					else // второй этап создания копии
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

//печать текста
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

//чтение текста из файла
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
		else if (StrBuf[0] == '{')// рекурсия
		{
			TextLevel++;
			ptl->pDown = ReadText(TxtFile);
		}
		else //присиединение следующей строки
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



