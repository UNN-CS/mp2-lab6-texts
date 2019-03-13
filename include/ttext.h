#ifndef __TEXT_H__
#define __TEXT_H__

#include <fstream>
#include <stack>
#include <string>
#include "defines.h"
#include "tdatacom.h"
#include "ttextmem.h"

class TText: public TDataCom
{
private:
  TTextMem MemControl;

  PTTextLink pRoot;
  PTTextLink pFirst;
  PTTextLink pCurrent;
  std::stack<PTTextLink> Path;
  std::stack<PTTextLink> St; // for iterator
  std::string indent;

  PTTextLink GetFirstAtom(PTTextLink pl);
  void PrintText(PTTextLink ptl, std::ostream &os);
  PTTextLink ReadText(std::ifstream &TxtFile);
  PTTextLink CreateLink(
      const TStr s=NULL, PTTextLink pn=NULL, PTTextLink pd=NULL);

public:
  TText(PTTextLink pl=NULL);
  virtual ~TText();

  PTText GetCopy();

  bool GoFirstLink();
  bool GoDownLink();
  bool GoNextLink();
  bool GoPrevLink();

  std::string GetLine();
  void SetLine(std::string s);

  void InsDownLine(std::string s);
  void InsDownSection(std::string s);
  void InsNextLine(std::string s);
  void InsNextSection(std::string s);
  void DelDownLine();
  void DelDownSection();
  void DelNextLine();
  void DelNextSection();

  void Reset();
  bool IsTextEnded() const;
  bool GoNext();

  void Read(const char *pFileName);
  void Write(const char *pFileName);

  void Print();

  friend class TTextViewer;
};

#endif

