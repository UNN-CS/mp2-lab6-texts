#ifndef __TEXT_H
#define __TEXT_H

#include <stack>
#include <fstream.h>
#include "tdatacom.h"
#include "textlink.h"

class TText;
typedef TText * PTText;

class TText /*:public TDataCom*/
{
protected: 
	PTTextLink pFirst;
	PTTextLink pCurrent;
	std::stack<PTTextLink> Path; //стек траекториии движения по тексту
	// pCurrent в стек не включается

	std::stack<PTTextLink> St;
	PTTextLink GetFirstAtom(PTTextLink pl);
	void PrintText(PTTextLink ptl);
	PTTextLink ReadText(ifstream &TxtFile);

public:
	TText(PTTextLink pl = nullptr);
	~TText();
	PTText GetCopy();

	// навигация
	int GoFirstLink();
	int GoDownLink();
	int GoNextLink();
	int GoPrevLink();

	// доступ
	std::string GetLine();
	void SetLine(std::string s);
	
	// модификация
	void InsDownLine(std::string s);
	void InsDownSection(std::string s);
	void InsNextLine(std::string s);
	void InsNextSection(std::string s);
	void DelDownLine();
	void DelDownSection();
	void DelNextLine();
	void DelNextSection();

	//итератор
	int Reset(); // установить на первую запись
	int IsTextEnded()const; //таблица завершена?
	int GoNext(); // переход к следующей записи

	//работа с файлами
	void Read(char *pFileName); // ввод текста из файла
	void Write(char *pFileName);// вывод текста в файл

	// печать
	void Print();
};

#endif
