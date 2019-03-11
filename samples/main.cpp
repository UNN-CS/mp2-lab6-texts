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

  t.Read(argv[1]);

  t.Print();

  TText t1;

  TText &t2 = *t.GetCopy();

  t2.Print();

  for(t2.Reset(); !t2.IsTextEnded(); t2.GoNext())
    cout << t2.GetLine() << endl;

  ::delete &t2;

  return 0;
}

