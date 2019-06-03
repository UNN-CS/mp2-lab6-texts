#ifndef _TTEXT_H
#define _TTEXT_H

#include <stack>
#include <fstream>
#include <string>
#include "tdatacom.h"
#include"TTextLink.h"

#define TextOk 0            // нет ошибок
#define TextNoDown 101      // нет подуровня для текущей позиции
#define TextNoNext 102      // нет следующего раздела для текущего уровня
#define TextNoPrev 103      // текущая позиция в начале текста
#define TextError -102      // ошибка в тексте
#define TextNoMem -101      // нет памяти
#define TooLongString -103  // слишком длинная строка

#define BufLength  80

class TText;

typedef TText* PTText;

class TText : public TDataCom
{
protected:
	PTTextLink pFirst;        // указатель корня дерева
	PTTextLink pCurrent;      // указатель текущей строки
	stack< PTTextLink > Path; // стек траектории движения по тексту
	stack< PTTextLink > St;   // стек для итератора
	PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
	void PrintText(PTTextLink ptl);         // печать текста со звена ptl
	PTTextLink ReadText(ifstream &TxtFile); // чтение текста из файла
public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }
	PTText GetCopy();

	// навигация
	int GoFirstLink(void); // переход к первой строке
	int GoDownLink(void);  // переход к следующей строке по Down
	int GoNextLink(void);  // переход к следующей строке по Next
	int GoPrevLink(void);  // переход к предыдущей позиции в тексте

	// доступ
	string GetLine(void);   // чтение текущей строки
	void SetLine(string s); // замена текущей строки 

	// модификация
	void InsDownLine(string s);    // вставка строки в подуровень
	void InsDownSection(string s); // вставка раздела в подуровень
	void InsNextLine(string s);    // вставка строки в том же уровне
	void InsNextSection(string s); // вставка раздела в том же уровне
	void DelDownLine(void);        // удаление строки в подуровне
	void DelDownSection(void);     // удаление раздела в подуровне
	void DelNextLine(void);        // удаление строки в том же уровне
	void DelNextSection(void);     // удаление раздела в том же уровне

	// итератор
	int Reset(void);               // установить на первую звапись
	int IsTextEnded() const { return !St.size(); };  // текст завершен?
	int GoNext(void);              // переход к следующей записи

	// работа с файлами
	void Read(char * pFileName);   // ввод текста из файла
	void Write(char * pFileName);  // вывод текста в файл

    // печать
	void Print(void);              // печать текста
};

#endif