// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include "TText.h"

using namespace std;

int main()
{

	TTextLink::InitMemSystem();
	TText txt;
	txt.SetLine("1 Chapter");
	txt.InsDownLine("1.1 Chapter");
	txt.GoDownLink();
	txt.InsNextLine("1.2 Chapter");
	txt.GoPrevLink();

	txt.InsNextLine("2 Chapter");
	txt.GoNextLink();

	txt.InsNextLine("3 Chapter");
	txt.GoNextLink();
	txt.InsDownLine("3.1 Chapter");
	txt.GoDownLink();
	txt.InsDownLine("3.1.1 Chapter");

	txt.Print();


	/*cout << "Yo\n";
	TTextLink::InitMemSystem();
	TText txt;
	cout << "WOW\n";
	txt.SetLine("walrus");
	cout << "Yo\n";
	txt.InsDownLine("aba");
	cout << "wOw\n";
	txt.InsDownLine("caba");
	txt.InsDownLine("lul");
	txt.InsNextLine("lul2");
	txt.InsNextLine("lul4");
	txt.Print();
	PTText txt2 = txt.GetCopy();
	txt2->Print();*/
	return 0;
}
