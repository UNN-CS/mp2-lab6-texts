// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include "include/ttext.h"

using namespace std;

int main(int argc, char *argv[])
{
  TText t;

  cerr << "\n\nREADING  " << argc << endl;

  t.Read(argv[1]);

  cerr << "\n\nPRINTING  " << endl;
  t.Print();

  return 0;
}
