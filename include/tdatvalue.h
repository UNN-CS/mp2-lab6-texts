#ifndef _TDATVALUE_H_
#define _TDATVALUE_H_
#define TextLineLength 20
#define MemSize 20

enum {TextNoDown = 101, TextNoNext, TextNoPrev, TextError = -102, TextNoMem};

class TDatValue {
public:
    virtual TDatValue *GetCopy() = 0; // создание копии
    ~TDatValue() {}
};
typedef TDatValue *PTDatValue;

class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TText;
typedef TText *PTText;

#endif  // _TDATVALUE_H_
