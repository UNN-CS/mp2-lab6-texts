#ifndef __DATVALUE_H
#define __DATVALUE_H
#define MemSize 20
#define TextLineLength 20
class TDatValue
{
public:
    virtual TDatValue * GetCopy() = 0;
    ~TDatValue() {}
};

typedef TDatValue *PTDatValue;

class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TText;
typedef TText *PTText;
#endif
