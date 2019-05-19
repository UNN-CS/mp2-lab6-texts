#ifndef __TTTEXT_H__
#define __TTTEXT_H__

#include <iostream>
#include <string.h>
#include <stack>

#include "tdatacom.h"
#include "TTextLink.h"

#define TextError -132
#define TextNoPrev -133
#define TextOK 0

class TText;
typedef TText *PTText;

class TText : public TDataCom {
protected:
	PTTextLink pFirst;      // указатель корня дерева
	PTTextLink pCurrent;      // указатель текущей строки
	std::stack< PTTextLink > Path; // стек траектории движения по тексту
	std::stack< PTTextLink > St;   // стек для итератора
	PTTextLink GetFirstAtom (PTTextLink pl); // поиск первого атома
	void PrintText (PTTextLink ptl);         // печать текста со звена ptl
	PTTextLink ReadText (std::ifstream &TxtFile); //чтение текста из файла
public:
	TText (PTTextLink pl = NULL);
	~TText () {pFirst = NULL;}
	PTText getCopy();
// навигация
	int GoFirstLink (void); // переход к первой строке
	int GoDownLink (void);  // переход к следующей строке по Down
	int GoNextLink (void);  // переход к следующей строке по Next
	int GoPrevLink (void);  // переход к предыдущей позиции в тексте
// доступ
	std::string GetLine(void);   // чтение текущей строки
	void SetLine ( std::string s); // замена текущей строки 
// модификация
	int InsDownLine (std::string s);    // вставка строки в подуровень
	int InsDownSection (std::string s); // вставка раздела в подуровень
	int InsNextLine (std::string s);    // вставка строки в том же уровне
	int InsNextSection (std::string s); // вставка раздела в том же уровне
	int DelDownLine (void);        // удаление строки в подуровне
	int DelDownSection (void);     // удаление раздела в подуровне
	int DelNextLine (void);        // удаление строки в том же уровне
	int DelNextSection (void);     // удаление раздела в том же уровне
// итератор
	int Reset (void);              // установить на первую звапись
	int IsTextEnded (void) const;  // текст завершен?
	int GoNext (void);             // переход к следующей записи
//работа с файлами
	void Read (char * pFileName);  // чтение текста из файла
	void Write (char * pFileName); // вывод текста в файл
//печать
	void Print (void);             // печать текста
};

#endif