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
  t.Read("../test/text1.txt");

  PTText pt = t.GetCopy();

  t.Print();
  pt->Print();

  cerr << t.GetLine() << endl;
  while(!t.IsTextEnded())
  {
    cerr << t.GetLine() << endl;
  }

  cerr << pt->GetLine() << endl;
  while(!pt->IsTextEnded())
  {
    cerr << pt->GetLine() << endl;
  }

  return 0;
}

