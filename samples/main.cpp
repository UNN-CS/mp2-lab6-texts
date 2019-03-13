// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include <cstdio>
#include <limits>
#include "include/ttext.h"

using namespace std;

typedef void __proc();
typedef __proc *procedure;

procedure CLEAR;
void PAUSE();
void __uniCLEAR();
void __winCLEAR();

void insert();
void remove();
void setl();

int main()
{
  CLEAR = __uniCLEAR;
  PTText pt = NULL;
  char choice;
  bool quit = false;

  while(true)
  {
    CLEAR();
    cout
        << "1. Enter path\n"
        << "2. Show text\n"
        << "3. Insert line\n"
        << "4. Set line\n"
        << "5. Delete line\n"
        << "0. Exit\n"
        << flush;

    cin >> choice;
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cin.clear();

    switch(choice)
    {
    case '1':
      char pth[256];
      CLEAR();
      cout << "Enter path" << endl;
      cin.getline(pth, 256);
      try
      {
        if(pt == NULL)
          pt = new TText;
        pt->Read(pth);
      }
      catch(...)
      {
        delete pt;
        pt = NULL;
        cout
            << "Invalid path\n"
            << "Press enter...\n"
            << flush;
        PAUSE();
      }
      break;

    case '2':
      CLEAR();
      if(pt == NULL)
        cout << "Select file\n";
      else
        pt->Print();
      cout << "\nPress enter...\n";
      PAUSE();
      break;

    case '3':
      insert();
      break;

    case '4':
      break;

    case '5':
      break;

    case '0':
      quit = true;
      break;

    default:
      break;
    };

    if(quit)
      break;
  }

  return 0;
}



void __winCLEAR()
{
  system("cls");
}

void __uniCLEAR()
{
  system("clear");
}

void PAUSE()
{
  char ch;
  while((ch = getchar()) != '\n');
}

void insert()
{
}

void remove()
{
}

void setl()
{
}

