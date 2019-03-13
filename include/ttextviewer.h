#ifndef __TEXTVIEWER_H__
#define __TEXTVIEWER_H__

#include "defines.h"
#include <iostream>

#define FP_NUM 1
#define FP_PTR 2

class TTextViewer
{
public:
  PTText pText;

  class fpnum_ostream: public std::ostream
  {
  protected:
    int counter;

  public:
    fpnum_ostream(int ctr=1):counter(ctr){}
    void zero()
    { counter = 1; }
    friend fpnum_ostream& operator<<(fpnum_ostream &os, const char *s);
    
    friend fpnum_ostream& operator<<(fpnum_ostream &os, char c)
    {
      if(c == '\n')
      {
        std::cout << std::endl;
        os.counter++;
      }
      else
        std::cout << c;
      return os;
    }
  };

  class fpptr_ostream: public fpnum_ostream
  {
  protected:
    int pos;

  public:
    fpptr_ostream(int p, int ctr=1):fpnum_ostream(ctr), pos(p){}
    friend fpptr_ostream& operator<<(fpptr_ostream& os, const char *s)
    {
      std::cout << ((os.counter == os.pos) ? "=>" : "  ")
          << s;
      return os;
    }
    friend fpptr_ostream& operator<<(fpptr_ostream& os, char c)
    {
      if(c == '\n')
      {
        std::cout << std::endl;
        os.counter++;
      }
      else
        std::cout << c;
      return os;
    }
  };

  class fppn_ostream: public fpptr_ostream
  {
  public:
    fppn_ostream(int p, int ctr=1):fpptr_ostream(p, ctr){}
    friend fppn_ostream& operator<<(fppn_ostream &os, const char *s)
    {
      std::cout << ((os.counter == os.pos) ? "=>" : "  ")
          << os.counter << ": " << s;
      return os;
    }
    friend fppn_ostream& operator<<(fppn_ostream &os, char c)
    {
      if(c == '\n')
      {
        std::cout << std::endl;
        os.counter++;
      }
      else
        std::cout << c;
      return os;
    }
  };

public:
  TTextViewer(PTText pt);
  ~TTextViewer();

  void FPrint(int mode=0);
};

#endif

