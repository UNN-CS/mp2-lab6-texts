// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include "include/ttext.h"

using namespace std;

int main()
{
  TText t;
  t.Read("../test/text2.txt");
  t.Print();

  t.Reset();
  t.DelNextSection();

  return 0;
}

