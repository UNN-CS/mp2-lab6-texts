#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>
#include "TText.h"
#define ESC 27

class TTextViewer
{
public:
  static void StartInterface(PTText);
private:
  static void Insertion(PTText pText);
  static void Navigation(PTText pText);
  static void Deleting(PTText pText);
};
