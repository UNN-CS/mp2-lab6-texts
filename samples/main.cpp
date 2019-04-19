// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>
#include "include/ttext.h"
#include "include/ttextviewer.h"

using namespace std;

void CLEAR();
void PAUSE();
void FLUSH();

int main()
{
  PTText pt = NULL;
  char choice;
  bool quit = false;

  while(true)
  {
    CLEAR();
    cout
        << "1.   Enter path\n"
        << "2.   Show text\n"
        << "3.   Select line\n"
        << "idl. Insert down line\n"
        << "inl. Insert next line\n"
        << "ids. Insert down section\n"
        << "ins. Insert next section\n"
        << "dd.  Delete down\n"
        << "dn.  Delete next\n"
        << "r.   Replace line\n"
        << "9.   Delete text\n"
        << "0.   Exit\n"
        << flush;

    cin >> choice;

    switch(choice)
    {
    case '1':
      FLUSH();
      char pth[256];
      CLEAR();
      cout << "Enter path" << endl;
      cin.getline(pth, 256);
      try
      {
        if(pt == NULL)
          pt = new TText;
        pt->Read(pth);
        pt->Reset();
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
      FLUSH();
      if(pt == NULL)
        cout << "Select file\n";
      else
      {
        TTextViewer tv(pt);
        tv.FPrint(FP_NUM | FP_PTR);
      }
      cout << "\nPress enter...\n";
      PAUSE();
      break;
    case '3':
      CLEAR();
      FLUSH();
      if(pt == NULL)
      {
        cout << "Select file\n"
            << "Press enter...\n";
        PAUSE();
      }
      else
      {
        size_t ln;
        cout << "Enter line number\n";
        cin >> ln;
        FLUSH();
        pt->Reset();
        for(size_t i = 1; i < ln; ++i)
        {
          if(pt->IsTextEnded())
            break;
          else
            pt->GoNext();
        }
      }
      break;

    case 'i':
      {
        CLEAR();
        if(pt == NULL)
        {
          cout << "Select file\nPress enter...\n";
          PAUSE();
          break;
        }
        char pch[3] = {'\0'};
        cin >> pch[0] >> pch[1];
        FLUSH();

        char buff[TextLineLength];
        cout << "Enter line:\n";
        cin.getline(buff, TextLineLength);
        string s(buff);

        if(strcmp("dl", pch) == 0)
          pt->InsDownLine(s);
        else if(strcmp("ds", pch) == 0)
          pt->InsDownSection(s);
        else if(strcmp("nl", pch) == 0)
          pt->InsNextLine(s);
        else if(strcmp("ns", pch) == 0)
          pt->InsNextSection(s);
        else
        {
          cout << "Invalid input\nPress enter...\n";
          PAUSE();
        }
      }
      break;

    case 'd':
      {
        CLEAR();
        if(pt == NULL)
        {
          cout << "Select file\nPress enter...\n";
          PAUSE();
          break;
        }
        char ch;
        cin >> ch;
        FLUSH();
        if(ch == 'd')
        {
          try { pt->DelDownSection(); }
          catch(...) {}
        }
        else if(ch == 'n')
        {
          try { pt->DelNextSection(); }
          catch(...) {}
        }
        else
        {
          cout << "Invalid input\nPress enter...\n";
          PAUSE();
        }
      }
      break;

    case 'r':
      {
        CLEAR();
        if(pt == NULL)
        {
          cout << "Select file\nPress enter...\n";
          PAUSE();
          break;
        }
        cout << "Enter new line:\n";
        char buff[TextLineLength];
        FLUSH();
        cin.getline(buff, TextLineLength);
        pt->SetLine(string(buff));
      }
      break;

    case '0':
      quit = true;
      break;

    case '9':
      delete pt;
      pt = NULL;
      break;

    default:
      break;
    };

    if(quit)
      break;
  }
return 0;
}


void CLEAR()
{
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#else
  system("clear");
#endif
}

void PAUSE()
{
  char ch;
  while((ch = cin.get()) != '\n');
}

void FLUSH()
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.clear();
}

