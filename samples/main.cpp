// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include "text.h"
#include "textlink.h"
using namespace std;

int main()
{
    cout<<"Yo\n";
    TTextLink::InitMemSystem();
    TText txt;
    cout<<"WOW\n";
    txt.SetLine("walrus");
    txt.InsDownLine("aba");
    cout<<"wOw\n";
    txt.InsDownLine("caba");
    txt.InsDownLine("lul");
    txt.InsNextLine("lul2");
    txt.InsNextLine("lul4");
    txt.Print();
    PTText txt2 = txt.GetCopy();
    txt2->Print();
    return 0;
}
