#ifndef __DEFS_H__
#define __DEFS_H__

#include <cstddef>

#define BufLength 81

#define TextLineLength 80
#define MemSize 40

#define DataOK 0
#define DataErr -1

#define TextOK DataOK

#define TextNoDown 101
#define TextNoNext 102
#define TextNoPrev 103

#define TextError -102
#define TextNoMem -101

#define TextLinkNoMemControl -201

#define DelMark "&&&"

class TTextMem;
class TTextLink;
class TTextViewer;
class TDatValue;
class TText;
class TDataCom;

typedef char TStr[TextLineLength];

typedef TTextMem *PTTextMem;
typedef TTextLink *PTTextLink;
typedef TDatValue *PTDatValue;
typedef TText *PTText;
typedef TDataCom *PTDatacom;

#endif

