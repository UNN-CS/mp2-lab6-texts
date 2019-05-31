#ifndef __T_TEXT_H__
#define __T_TEXT_H__

#include "textlink.h"
#include <stack>
#include <iostream>
#include <cstring>

class TText;
typedef TText * PTText;

class TText {
protected:
	PTTextLink pFirst;      // указатель корня дерева
	PTTextLink pCurrent;      // указатель текущей строки
	std::stack< PTTextLink > Path; // стек траектории движения по тексту
	std::stack< PTTextLink > St;   // стек для итератора
	PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
	void PrintText(PTTextLink ptl);         // печать текста со звена ptl
	PTTextLink ReadText(std::ifstream &TxtFile); //чтение текста из файла
public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }
	PTText GetCopy();
	// навигация
	void GoFirstLink(); // переход к первой строке
	void GoDownLink();  // переход к следующей строке по Down
	void GoNextLink();  // переход к следующей строке по Next
	void GoPrevLink();  // переход к предыдущей позиции в тексте
						// доступ
	std::string GetLine();   // чтение текущей строки
	void SetLine(std::string s); // замена текущей строки
								 // модификация
	void InsDownLine(std::string s);    // вставка строки в подуровень
	void InsDownSection(std::string s); // вставка раздела в подуровень
	void InsNextLine(std::string s);    // вставка строки в том же уровне
	void InsNextSection(std::string s); // вставка раздела в том же уровне
	void DelDownLine();        // удаление строки в подуровне
	void DelDownSection();     // удаление раздела в подуровне
	void DelNextLine();        // удаление строки в том же уровне
	void DelNextSection();     // удаление раздела в том же уровне
							   // итератор
	int Reset();              // установить на первую звапись
	int IsTextEnded() const;  // текст завершен?
	int GoNext();             // переход к следующей записи
							  //работа с файлами
	void Read(const char * pFileName);  // ввод текста из файла
	void Write(char * pFileName); // вывод текста в файл
								  //печать
	void Print();             // печать текста
};

#endif // __T_TEXT_H__
