#ifndef __TEXTVIEWER_H__
#define __TEXTVIEWER_H__

#include "defines.h"
#include <iostream>

#define FP_NUM 1
#define FP_PTR 2

class TTextViewer
{
private:
  PTText pText;

  void print_n(std::ostream&);
  void print_p(std::ostream&);
  void print_pn(std::ostream&);

public:
  TTextViewer(PTText pt);

  void FPrint(int mode=0);
};

#endif

