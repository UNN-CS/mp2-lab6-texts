#ifndef _TTEXT_H_
#define _TTEXT_H_
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include "tdatacom.h"
#include "ttextlink.h"

class TText {
protected:
    PTTextLink pFirst;      // указатель корня дерева
    PTTextLink pCurrent;      // указатель текущей строки
    std::stack< PTTextLink > Path; // стек траектории движения по тексту
    std::stack< PTTextLink > St;   // стек для итератора
    PTTextLink GetFirstAtom (PTTextLink pl); // поиск первого атома
    void PrintText (std::ostream& out, PTTextLink ptl); // печать текста со звена ptl
    PTTextLink ReadText (std::ifstream &TxtFile); //чтение текста из файла
public:
    TText (PTTextLink pl = nullptr);
    ~TText () {}
    PTText GetCopy();

    int GoFirstLink (); // переход к первой строке
    int GoDownLink ();  // переход к следующей строке по Down
    int GoNextLink ();  // переход к следующей строке по Next
    int GoPrevLink ();  // переход к предыдущей позиции в тексте

    std::string GetLine();   // чтение текущей строки
    void SetLine ( std::string s); // замена текущей строки

    void InsDownLine (std::string s);    // вставка строки в подуровень
    void InsDownSection (std::string s); // вставка раздела в подуровень
    void InsNextLine (std::string s);    // вставка строки в том же уровне
    void InsNextSection (std::string s); // вставка раздела в том же уровне
    void DelDownLine ();        // удаление строки в подуровне
    void DelDownSection ();     // удаление раздела в подуровне
    void DelNextLine ();        // удаление строки в том же уровне
    void DelNextSection ();     // удаление раздела в том же уровне

    int Reset ();              // установить на первую звапись
    int IsTextEnded () const;  // текст завершен?
    int GoNext ();             // переход к следующей записи

    void Read (char *pFileName);  // ввод текста из файла
    void Write (char *pFileName); // вывод текста в файл

    void Print (std::ostream& out);         // печать текста
};

#endif  // _TTEXT_H_
