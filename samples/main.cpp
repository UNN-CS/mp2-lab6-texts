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
	TTextLink::InitMemSystem();
	TText txt;

	txt.SetLine("Lable 1");
	txt.InsDownLine("txt 1");
	txt.GoDownLink();
	txt.InsNextLine("txt 2");

	txt.GoFirstLink();

	txt.InsNextLine("Lable 2");
	txt.GoNextLink();
	txt.InsDownLine("txt 1");
	txt.GoDownLink();
	txt.InsNextLine("txt 2");

	txt.Print();

	PTText txt2 = txt.GetCopy();
	txt2->Print();
	return 0;
}
