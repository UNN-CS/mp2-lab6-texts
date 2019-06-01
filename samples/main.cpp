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

	return 0;
}
