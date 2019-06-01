#ifndef __DATVALUE_H__
#define __DATVALUE_H__
#define TextLineLength 20
#define MemSize 20

#include <iostream>

class TDatValue {
public:
    virtual TDatValue* GetCopy() = 0;
    ~TDatValue() {}
};

typedef TDatValue* PTDatValue;

class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TText;
typedef TText *PTText;
#endif // __DATVALUE_H__